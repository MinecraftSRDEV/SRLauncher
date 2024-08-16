void prelaunch_tasks(std::string game_runpath);

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
    log_message("Running steamCMD command: " + command, LOG_TYPES::LOG_INFO);

    // Składamy pełne polecenie
    std::string fullCommand = steamcmdPath + " " + command;

    // Wykonujemy polecenie
    int result = system(fullCommand.c_str());
    // int result = 0;

    // Sprawdzamy wynik
    if (result == 0) {
        log_message("Command executed successfully", LOG_TYPES::LOG_INFO);
        fs::path outputDir = defaultDir / "SteamCMD" / "steamapps" / "content" / "app_433340" / "depot_433342"; 
        if (fs::exists(outputDir) && fs::is_directory(outputDir))
        {
            move_directory(outputDir, steam_dir / "Slime Rancher");
            log_message("Game download success", LOG_TYPES::LOG_INFO);
            game_downloading = false;
            prelaunch_tasks(gamerun_path);
        }
        else
        {
            log_message("Game download falied", LOG_TYPES::LOG_ERROR);
            game_downloading = false;
        }
    } else {
        log_message("Command cannot be executed", LOG_TYPES::LOG_ERROR);
        game_downloading = false;
    }
}