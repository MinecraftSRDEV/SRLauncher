void run_game(std::string path)
{
    HWND launcherWindow = window.getSystemHandle();
    launch_last_instance_button.setText("Running");
    ShowWindow(launcherWindow, SW_MINIMIZE);
    game_running = true;
    system(formatPathForSystem(path).c_str());
    ShowWindow(launcherWindow, SW_RESTORE);
    game_running = false;
    reset_play_button_text();
}

std::string compile_current_date()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    int year = (now->tm_year + 1900);
    int month = (now->tm_mon + 1);
    int day = now->tm_mday;
    int hour = now->tm_hour;
    int minute = now->tm_min;
    int sec = now->tm_sec;

    std::string output = std::to_string(year) + "_" + std::to_string(month) + "_" + std::to_string(day) + "_" + std::to_string(hour) + "_" + std::to_string(minute) + "_" + std::to_string(sec);
    return output;
}

void reset_play_button_text()
{
    launch_last_instance_button.setText("Launch mounted instance");
}

bool create_achivements_backup()
{
    try
    {
        fs::path destination = fs::path(steam_game_dir) / "Slime Rancher" / "data" / "gamedata" / fs::path("achivments_and_settings_backup_" + compile_current_date() + ".prf");

        fs::copy_file(local_save_path / "slimerancher.prf", destination);
        log_message("Backup completed", LOG_TYPES::LOG_INFO);
        return true;
    }
    catch (fs::filesystem_error& e)
    {
        std::string errmsg = e.what();
        log_message("Error creating backup: " + errmsg, LOG_TYPES::LOG_ERROR);
    }
    return false;
}

bool backup_yes()
{
    if (create_achivements_backup() == true)
    {
        return true;
    }
    else
    {
        int result = MessageBoxA(NULL, "Cannot create backup!", "Error", MB_ICONERROR | MB_ABORTRETRYIGNORE);
        switch(result)
        {
            case IDABORT:
            {
                return false;
                break;
            }
            case IDRETRY:
            {
                backup_yes();
                break;
            }
            case IDIGNORE:
            {
                return true;
                break;
            }
        }
    }
    return false;
}


void prelaunch_tasks(std::string game_runpath)
{
    bool launch_game = true;
    launch_last_instance_button.setText("Launching game");
    if (show_warnings == true)
    {
        if (versions_map[instances_list[mounted_instance].getVer()].version_type == "pre-release")
        {
            // configuration warning
            int result = MessageBoxA(NULL, "Launching pre-release version you can loose saved settings and achivements! Backup this data now?", "Warning", MB_ICONEXCLAMATION | MB_YESNOCANCEL);
            switch (result)
            {
                case IDYES:
                {
                    launch_game = backup_yes();
                    break;
                }
                case IDNO:
                {
                    launch_game = true;
                    break;
                }
                case IDCANCEL:
                {
                    launch_game = false;
                    break;
                }
            }
        }
        else if (versions_map[instances_list[mounted_instance].getVer()].version_name != "1.4.4")
        {
            // achivments warning
            int result = MessageBoxA(NULL, "Launching older version you can loose saved achivements data! Backup this now?", "Warning", MB_ICONEXCLAMATION | MB_YESNOCANCEL);
            switch (result)
            {
                case IDYES:
                {
                    launch_game = backup_yes();
                    break;
                }
                case IDNO:
                {
                    launch_game = true;
                    break;
                }
                case IDCANCEL:
                {
                    launch_game = false;
                    break;
                }
            }
        }
        else
        {
            launch_game == true;
        }    
    }
    

    if (launch_game == true)
    {
        std::thread gameThread(run_game, game_runpath);
        gameThread.detach();    
    }
    else
    {
        log_message("Launching task stopped", LOG_TYPES::LOG_INFO);
        reset_play_button_text();
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

            // log_message("Running game" + gamerun_path, LOG_TYPES::LOG_INFO);
            // prelaunch_tasks(gamerun_path);
        executableCheck.close();    
    }
    else
    {
        log_message("Game is now downloading", LOG_TYPES::LOG_INFO);
        MessageBoxA(NULL, "Game is now downloading", "Info", MB_ICONINFORMATION | MB_OK);
    }
}

void hanglefunction()
{
    if (game_running == false)
    {
        if (mounted_instance.empty() or mounted_instance == "Unmounted")
        {
            log_message("no slime rancher instance mounted", LOG_TYPES::LOG_ERROR);
            MessageBoxA(NULL, "no slime rancher instance mounted", "Error", MB_ICONERROR | MB_OK);
        }
        else
        {
            log_message("Launching instance: " + mounted_instance, LOG_TYPES::LOG_INFO);
            launch_game(mounted_instance);
        }    
    }
    else
    {
        log_message("Game allready running", LOG_TYPES::LOG_ERROR);
        MessageBoxA(NULL, "Game allready running", "Error", MB_ICONERROR | MB_OK);
    }
}