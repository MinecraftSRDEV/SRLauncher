void prelaunch_tasks(std::string game_runpath);
void reset_play_button_text();

void download_game(std::string gamerun_path)
{
    if (SteamCMDCheck() == true)
    {
        steam_game_dir = SlimeRancher_steam_path_textbox.getText();
        fs::path steam_dir = steam_game_dir;
        fs::path game_dir = steam_dir / "Slime Rancher";

        game_downloading = true;
        launch_last_instance_button.setText("Downloading");
        std::thread animThread(downloading_animation);
        animThread.detach();
        fs::path cmdpath = fs::path(steamcmd_dir);
        std::string steamcmdPath = cmdpath.string();

        std::string command = "+login " + decryptor(steam_profile_name) + " +download_depot 433340 433342 " + versions_map[instances_list[mounted_instance].getVer()].manifest + " +quit";
        log_message("Running steamCMD command: " + command, LOG_TYPES::LOG_INFO);

        std::string fullCommand = steamcmdPath + " " + command;

        int result = system(fullCommand.c_str());

        if (result == 0)
        {
            log_message("Command executed successfully", LOG_TYPES::LOG_INFO);
            fs::path outputDir = defaultDir / "SteamCMD" / "steamapps" / "content" / "app_433340" / "depot_433342"; 
            if (fs::exists(outputDir) && fs::is_directory(outputDir))
            {
                move_directory(outputDir, steam_dir / "Slime Rancher");
                log_message("Game download success", LOG_TYPES::LOG_INFO);
                game_downloading = false;
                if (autolaunch_instances == true)
                {
                    prelaunch_tasks(gamerun_path);    
                }
            }
            else
            {
                log_message("Game download falied", LOG_TYPES::LOG_ERROR);
                game_downloading = false;
            }
        }
        else
        {
            log_message("Command cannot be executed", LOG_TYPES::LOG_ERROR);
            game_downloading = false;
        }
    }
    else
    {
        MessageBoxA(NULL, "Cannot download game: SteamCMD is not installed!", "Error", MB_ICONERROR | MB_OK);
    }
    
    reset_play_button_text();
}