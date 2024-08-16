void run_game(std::string path)
{
    system(formatPathForSystem(path).c_str());
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
        executableCheck.open(gamerun_path.c_str());
        if (executableCheck)
        {
            log_message("Running game" + gamerun_path, LOG_TYPES::LOG_INFO);
            prelaunch_tasks(gamerun_path);
        }
        else
        {
            log_message("Downloading started", LOG_TYPES::LOG_INFO);
            std::thread downloadThread(download_game, gamerun_path);
            downloadThread.detach();
        }
        executableCheck.close();    
    }
    else
    {
        log_message("Game is now downloading", LOG_TYPES::LOG_INFO);
    }
}

void hanglefunction()
{
    if (mounted_instance.empty() or mounted_instance == "Unmounted")
    {
        log_message("no slime rancher instance mounted", LOG_TYPES::LOG_ERROR);
    }
    else
    {
        log_message("Launching instance: " + mounted_instance, LOG_TYPES::LOG_INFO);
        launch_game(mounted_instance);
    }
}