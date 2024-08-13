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

void move_directory(fs::path source, fs::path destination) {
    try {
        // Sprawdź, czy folder źródłowy istnieje
        if (!fs::exists(source) || !fs::is_directory(source)) {
            throw std::runtime_error("Source directory does not exist or is not a directory.");
        }

        // Sprawdź, czy folder docelowy istnieje, jeśli nie, to go utwórz
        if (!fs::exists(destination)) {
            fs::create_directories(destination);
        }

        // Iteruj przez wszystkie elementy w folderze źródłowym
        for (const auto& entry : fs::directory_iterator(source)) {
            // Ścieżka do pliku lub folderu źródłowego
            auto source_path = entry.path();
            // Ścieżka docelowa
            auto destination_path = destination / source_path.filename();

            // Jeśli element jest folderem, wywołaj funkcję rekurencyjnie
            if (fs::is_directory(source_path)) {
                move_directory(source_path, destination_path);
            } else {
                // Jeśli element jest plikiem, przenieś go
                fs::rename(source_path, destination_path);
            }
        }

        // Po przeniesieniu wszystkich plików i folderów usuń folder źródłowy
        fs::remove(source);

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

void save_profiles()
{
    std::cout << "output Name: " << encryptor(SteamProfile_name_textbox.getText()) << std::endl;
    std::cout << "output Pass: " << encryptor(SteamProfile_password_textbox.getText()) << std::endl;
}

void rename_orginal_dir()
{
    steam_game_dir = SlimeRancher_steam_path_textbox.getText();
    fs::path steam_dir = steam_game_dir;
    fs::path orginal_game_dir = steam_dir / "Slime Rancher";
    fs::path renamed_game_dir = steam_dir / "Slime Rancher_orginal";

    std::cout << orginal_game_dir.string() << std::endl;
    std::cout << renamed_game_dir.string() << std::endl;

    if (fs::exists(orginal_game_dir) && fs::is_directory(orginal_game_dir))
    {
        // fs::rename(orginal_game_dir, renamed_game_dir);
    }
    else
    {
        std::cout << "no slime rancher instalation detected!" << std::endl;
    }
}

std::string formatPathForSystem(std::string path) {
    // Sprawdź, czy w ścieżce są spacje
    if (path.find(' ') != std::string::npos) {
        // Jeśli są spacje, dodaj cudzysłowy
        return "\"" + path + "\"";
    }
    // Jeśli nie ma spacji, zwróć ścieżkę bez zmian
    return path;
}

void run_game(std::string path)
{
    system(formatPathForSystem(path).c_str());
}

void downloading_animation()
{
    progress_moveing.setPosition(-70, progress_moveing.getPosition().y);

    sf::Clock cooldown;
    cooldown.restart();

    while (true)
    {
        if (game_downloading == false)
        {
            break;
        }

        if (cooldown.getElapsedTime() > sf::milliseconds(100))
        {
            cooldown.restart();

            if (progress_moveing.getPosition().x > 1280)
            {
                progress_moveing.setPosition(-70, progress_moveing.getPosition().y);
            }
            else
            {
                progress_moveing.setPosition(progress_moveing.getPosition().x + 20, progress_moveing.getPosition().y);
            }
        }
    }
}

void prelaunch_tasks(std::string game_runpath)
{
    if (versions_map[instances_list[mounted_instance].getVer()].version_type == "pre-release")
    {
        // configuration warning
    }
    if (mounted_instance != "1.4.4")
    {
        // achivments warning
    }
    std::thread gameThread(run_game, game_runpath);
    gameThread.detach();
}

void download_game(std::string gamerun_path)
{
    steam_game_dir = SlimeRancher_steam_path_textbox.getText();
    fs::path steam_dir = steam_game_dir;
    fs::path game_dir = steam_dir / "Slime Rancher";

    game_downloading = true;
    std::thread animThread(downloading_animation);
    animThread.detach();
    fs::path cmdpath = defaultDir / "SteamCMD" / "steamcmd.exe";
    std::string steamcmdPath = cmdpath.string();

    // Polecenie, które chcemy wykonać w SteamCMD
    // std::string command = "+login anonymous +force_install_dir ./csgo_ds +app_update 740 validate +quit";
    std::string command = "+login " + steam_profile_name + " +password " + steam_profile_passwd + " +download_depot 433340 433342 " + versions_map[instances_list[mounted_instance].getVer()].manifest + " +quit";
    std::cout << "command: " << command << std::endl;

    // Składamy pełne polecenie
    std::string fullCommand = steamcmdPath + " " + command;

    // Wykonujemy polecenie
    int result = system(fullCommand.c_str());
    // int result = 0;

    // Sprawdzamy wynik
    if (result == 0) {
        std::cout << "Polecenie wykonane pomyślnie." << std::endl;
        fs::path outputDir = defaultDir / "SteamCMD" / "steamapps" / "content" / "app_433340" / "depot_433342"; 
        if (fs::exists(outputDir) && fs::is_directory(outputDir))
        {
            move_directory(outputDir, steam_dir / "Slime Rancher");
            std::cout << "download success" << std::endl;
            game_downloading = false;
            prelaunch_tasks(gamerun_path);
        }
        else
        {
            std::cout << "download fail" << std::endl;
            game_downloading = false;
        }
    } else {
        std::cout << "Wystąpił błąd podczas wykonywania polecenia." << std::endl;
        game_downloading = false;
    }
}

void launch_game(std::string instance_id)
{
    if (game_downloading == false)
    {
        // fs::path game_dir = defaultDir / "instances" / instance_id;
        steam_game_dir = SlimeRancher_steam_path_textbox.getText();
        fs::path steam_dir = steam_game_dir;
        fs::path game_dir = steam_dir / "Slime Rancher";

        std::ifstream executableCheck;
        std::string gamepath = game_dir.string();
        std::string gamerun_path = gamepath + "/SlimeRancher.exe";
        std::cout << "running game: " << gamerun_path << std::endl;
        executableCheck.open(gamerun_path.c_str());
        if (executableCheck)
        {
            prelaunch_tasks(gamerun_path);
        }
        else
        {
            std::thread downloadThread(download_game, gamerun_path);
            downloadThread.detach();
        }
        executableCheck.close();    
    }
    else
    {
        std::cout << "Game is now downloading" << std::endl;
    }
}

void hanglefunction()
{
    std::cout << "Mounted instance: " << mounted_instance << std::endl;
    if (mounted_instance.empty())
    {
        std::cout << "no slime rancher instance mounted" << std::endl;
    }
    else if (mounted_instance == "Unmounted")
    {
        std::cout << "no slime rancher instance mounted" << std::endl;
    }
    else
    {
        launch_game(mounted_instance);
    }
}

void get_textbox_settings_values_and_save()
{
    steam_game_dir = SlimeRancher_steam_path_textbox.getText();
    instances_dir = SlimeRancher_instances_path_textbox.getText();

    steam_profile_name = SteamProfile_name_textbox.getText();
    steam_profile_passwd = SteamProfile_password_textbox.getText();
    update_config_file();
}

int main()
{
    create_window(1280, 800);

    loadElements();

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

    if (fs::exists(defaultDir) && fs::is_directory(defaultDir))
    {
        load_config_file(configuration_path.string() + "/config.json");
        SlimeRancher_steam_path_textbox.setText(steam_game_dir);
        SlimeRancher_instances_path_textbox.setText(instances_dir);

        SteamProfile_name_textbox.setText(steam_profile_name);
        SteamProfile_password_textbox.setText(steam_profile_passwd);
        load_versions_list();

        if (mounted_instance.empty())
        {
            rename_orginal_dir();
            mounted_instance = "Unmounted";
        }

        refresh_instances_list();
    }
    else
    {
        fs::create_directory(defaultDir);

        fs::create_directory(instances_path);
        fs::create_directory(backups_path);
        fs::create_directory(configuration_path);
        fs::create_directory(temp_path);
        fs::create_directory(cmd_path);

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
    }
}