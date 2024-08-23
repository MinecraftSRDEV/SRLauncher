#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <regex>
#include <thread>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <windows.h>
#include <shlobj.h>

#include <curl/curl.h>

namespace fs = std::filesystem;

#include <SFMLGUI/Gui.hpp>

#include "includes.hpp"

std::string BrowseFolder()
{
    char szFolderPath[MAX_PATH] = { 0 };
    
    BROWSEINFOA bi = { 0 };
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);

    if (pidl != NULL)
    {
        if (SHGetPathFromIDListA(pidl, szFolderPath))
        {
            CoTaskMemFree(pidl);
            return std::string(szFolderPath);
        }
        CoTaskMemFree(pidl);
    }

    return std::string();
}

void setDefault_paths()
{
    steam_game_dir = get_steam_default_path();
    instances_dir = instances_path.string();

    SlimeRancher_steam_path_textbox.setText(steam_game_dir);
    SlimeRancher_instances_path_textbox.setText(instances_dir);
}

void setSettingsDefault()
{
    int result = MessageBoxA(NULL, "Are you sure you want to restore default settings?", "Warning", MB_ICONEXCLAMATION | MB_YESNO);
    switch (result)
    {
        case IDYES:
        {
            setDefault_paths();
            break;
        }
        case IDNO:
        {
            break;
        }
    }
}

void getfolder_steamdir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        steam_game_dir = input_path;
        SlimeRancher_steam_path_textbox.setText(steam_game_dir);
    }
}

void getfolder_instnacesdir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        instances_dir = input_path;
        SlimeRancher_instances_path_textbox.setText(instances_dir);    
    }
}

void getfolder_instancesdir()
{

}

void rundate_get()
{
    std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);

    run_YEAR = (now->tm_year + 1900);
    run_MONTH = (now->tm_mon + 1);
    run_DAY = now->tm_mday;
    run_H = now->tm_hour;
    run_M = now->tm_min;
    run_S = now->tm_sec;
}

void setRuntimeTexts()
{
    Mounted_instance_info_text.setFont(font);
    Mounted_instance_info_text.setCharacterSize(36);
    Mounted_instance_info_text.setFillColor(sf::Color::Black);
    Mounted_instance_info_text.setPosition(10, 725);

    Launcher_version_text.setFont(font);
    Launcher_version_text.setCharacterSize(36);
    Launcher_version_text.setFillColor(sf::Color::Black);
    Launcher_version_text.setString(launcher_version);
    Launcher_version_text.setPosition((window.getSize().x - 10) - Launcher_version_text.getLocalBounds().width, 725);
}

void setShapesAttributes()
{
    progress_bg.setSize(sf::Vector2f(1280, 20));
    progress_bg.setPosition(sf::Vector2f(0, 780));
    progress_bg.setFillColor(sf::Color::White);

    progress_moveing.setSize(sf::Vector2f(70, 20));
    progress_moveing.setPosition(sf::Vector2f(-70, 780));
    progress_moveing.setFillColor(sf::Color::Blue);
}

void createDDListFromVersionsMap()
{
    for (const auto& pair : versions_map)
    {
        std::map <std::string, std::string>tempmap;
        tempmap[pair.first] = pair.first;
        versions_list.add_options(tempmap); /* send versions list to add_option function in DropDownList class */
        tempmap.clear();
    }
}

/**
 * Function used for construct paths to every directories used by Launcher.
 * First use getUserDir funtion to get user %AppData% path.
 * Finaly results are saved to all paths declareted in "varriables.hpp" as "Launcher".  
 * 
 * This is onetime use function. 
 */
void construct_paths()
{
    fs::path userDir = fs::path(getUserProfile());
    defaultDir = userDir / "AppData" / "Roaming" / "SRLauncher";
    local_save_path = userDir / "AppData" / "LocalLow" / "Monomi Park" / "Slime Rancher";

    instances_path = defaultDir / "instances";
    backups_path = defaultDir / "backups";
    autobackup_path = backups_path / "PreLauncherInstalled";
    configuration_path = defaultDir / "config";
    temp_path = defaultDir / "temp";
    cmd_path = defaultDir / "SteamCMD";
    logs_path = defaultDir / "logs";
}

/**
 * This function check if Main Launcher directory exists.
 * 
 * TRUE:
 * - AutoCheck for other Launcher directories.
 * - Load configuration files.
 * - Set UI elements.
 * - Check for orginal game dir.
 * - Load Mounted instance.
 * - Check for SteamCMD installed.
 * 
 * FALSE:
 * - Create default config files.
 * - Set default config.
 * 
 * This is onetime use function 
 */
void runtime_check()
{
    restart_runtime:
    {
        if (check_directory_exists(defaultDir) == true)
        {
            directory_auto(instances_path);
            directory_auto(backups_path);
            directory_auto(autobackup_path);
            directory_auto(configuration_path);
            directory_auto(temp_path);
            directory_auto(cmd_path);
            directory_auto(logs_path);

            load_config_file(configuration_path.string() + "/config.json");
            SlimeRancher_steam_path_textbox.setText(reduceBackslashes(steam_game_dir));
            SlimeRancher_instances_path_textbox.setText(reduceBackslashes(instances_dir));

            SteamProfile_name_textbox.setText(decryptor(steam_profile_name));
            SteamProfile_password_textbox.setText(decryptor(steam_profile_passwd));
            load_versions_list();

            if (mounted_instance.empty())
            {
                rename_orginal_dir();
                log_message("No instance mounted", LOG_TYPES::LOG_INFO);
                mounted_instance = "Unmounted";
                Mounted_instance_info_text.setString("No instance mounted");
            }
            else
            {
                if (mounted_instance == "Unmounted")
                {
                    Mounted_instance_info_text.setString("No instance mounted");
                }
                else
                {
                    Mounted_instance_info_text.setString(mounted_instance);
                }
                log_message("Mounted instance: " + mounted_instance, LOG_TYPES::LOG_INFO);
            }

            refresh_instances_list();

            if (SteamCMDCheck() == true)
            {
                log_message("SteamCMD is not installed", LOG_TYPES::LOG_WARN);
            }
        }
        else
        {
            if (create_dir(defaultDir) == true)
            {
                log_message("Launcher directory created in: " + defaultDir.string(), LOG_TYPES::LOG_INFO);
            }
            else
            {
                log_message("Cannot create launcher directory", LOG_TYPES::LOG_ERROR);
                MessageBoxA(NULL, "Cannot create launcher directory", "Error", MB_ICONERROR | MB_OK);
                close_launcher();
            }

            setDefault_paths();
            mounted_instance = "";

            steam_profile_name = "";
            steam_profile_passwd = "";
            update_config_file();

            SteamProfile_name_textbox.setText(steam_profile_name);
            SteamProfile_password_textbox.setText(steam_profile_passwd);

            goto restart_runtime;
        }    
    }
    
}

/* Main load sequence function. Contains a list of functions responsible for loading the launcher */
void load_sequence() 
{
    ///// Get run time date and save to local varriabless /////
    rundate_get();

    ///// Construct all "Launcher" paths /////
    construct_paths();

    ///// Load required resources /////
    loadElements();

    ///// Set SFML text attributes onetime /////
    setRuntimeTexts();

    ///// Set SFML Rectangle shapes attributes onetime /////
    setShapesAttributes();

    ///// Set loaded resources to SFML elements /////
    setTextures();

    ///// Set SFML-GUI Buttons attributes onetime /////
    setButtons();

    ///// Set functions to buttons from SFML-GUI onetime /////
    setFunctions();

    ///// Check run functions /////
    runtime_check();
    
    ///// Create DropDownList from all "versions_map" contents /////
    createDDListFromVersionsMap(); 

}

int main()
{
    create_window(1280, 800);

    load_sequence();

    if (window_actived == true)
    {
        while(window.isOpen())
        {	
            events_loop();

            mouse_left();

            window_draw();
            display_window();
        }

        close_launcher();
    }
}