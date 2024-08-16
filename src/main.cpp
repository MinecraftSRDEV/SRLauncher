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

#include <curl/curl.h>

namespace fs = std::filesystem;

#include <SFMLGUI/Gui.hpp>

#include "includes.hpp"

void save_profiles()
{
    log_message("output Name: " + encryptor(SteamProfile_name_textbox.getText()), LOG_TYPES::LOG_INFO);
    log_message("output Pass: " + encryptor(SteamProfile_password_textbox.getText()), LOG_TYPES::LOG_INFO);
}

int main()
{
    std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);

    run_YEAR = (now->tm_year + 1900);
    run_MONTH = (now->tm_mon + 1);
    run_DAY = now->tm_mday;
    run_H = now->tm_hour;
    run_M = now->tm_min;
    run_S = now->tm_sec;

    create_window(1280, 800);

    loadElements();

    Mounted_instance_info_text.setFont(font);
    Mounted_instance_info_text.setCharacterSize(36);
    Mounted_instance_info_text.setFillColor(sf::Color::Black);
    Mounted_instance_info_text.setPosition(10, 725);

    Launcher_version_text.setFont(font);
    Launcher_version_text.setCharacterSize(36);
    Launcher_version_text.setFillColor(sf::Color::Black);
    Launcher_version_text.setString(launcher_version);
    Launcher_version_text.setPosition((window.getSize().x - 10) - Launcher_version_text.getLocalBounds().width, 725);

    progress_bg.setSize(sf::Vector2f(1280, 20));
    progress_bg.setPosition(sf::Vector2f(0, 780));
    progress_bg.setFillColor(sf::Color::White);
    progress_moveing.setSize(sf::Vector2f(70, 20));
    progress_moveing.setPosition(sf::Vector2f(-70, 780));
    progress_moveing.setFillColor(sf::Color::Blue);

    load_versions_list();
    
    setTextures();

    setButtons();

    for (const auto& pair : versions_map)
    {
        std::map <std::string, std::string>tempmap;
        tempmap[pair.first] = pair.first;
        versions_list.add_options(tempmap);
    }

    setFunctions();

    defaultDir = fs::path(getUserProfile()) / "AppData" / "Roaming" / "SRLauncher";

    instances_path = defaultDir / "instances";
    backups_path = defaultDir / "backups";
    configuration_path = defaultDir / "config";
    temp_path = defaultDir / "temp";
    cmd_path = defaultDir / "SteamCMD";
    logs_path = defaultDir / "logs";

    if (check_directory_exists(defaultDir) == true)
    {
        directory_auto(instances_path);
        directory_auto(backups_path);
        directory_auto(configuration_path);
        directory_auto(temp_path);
        directory_auto(cmd_path);
        directory_auto(logs_path);

        load_config_file(configuration_path.string() + "/config.json");
        SlimeRancher_steam_path_textbox.setText(reduceBackslashes(steam_game_dir));
        SlimeRancher_instances_path_textbox.setText(reduceBackslashes(instances_dir));

        SteamProfile_name_textbox.setText(steam_profile_name);
        SteamProfile_password_textbox.setText(steam_profile_passwd);
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

        if (!fs::exists(cmd_path.string() + "\\steamcmd.exe"))
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
            close_launcher();
        }

        steam_game_dir = get_steam_default_path();
        instances_dir = instances_path.string();
        mounted_instance = "";

        steam_profile_name = "";
        steam_profile_passwd = "";
        update_config_file();

        SlimeRancher_steam_path_textbox.setText(steam_game_dir);
        SlimeRancher_instances_path_textbox.setText(instances_dir);

        SteamProfile_name_textbox.setText(steam_profile_name);
        SteamProfile_password_textbox.setText(steam_profile_passwd);
    }

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