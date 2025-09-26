void prelaunch_tasks(std::string game_runpath, std::string gamepath);
void reset_play_button_text();

struct depotProsp
{
    std::string appid  = "";
    std::string depotid  = "";
    std::string manifestid  = "";
    std::string username  = "";
    std::string password  = "";
    std::string path  = "";
    std::string runpath  = "";
};

void runDownloader(const depotProsp& depot)
{
    log_message("Sending task to DepotDownloader", LogTypes::LOG_INFO);
    std::string command = downloader_path.string() + "/DepotDownloader.exe -app "
    + depot.appid + " -depot " + depot.depotid + " -manifest " + depot.manifestid + " -username " + depot.username + " -password " + depot.password + " -dir " + downloader_path.string() + "/output";
    system(command.c_str());
    game_downloading = false;


    // STARTUPINFO si;
    // PROCESS_INFORMATION pi;
    // ZeroMemory(&si, sizeof(si));
    // si.cb = sizeof(si);
    // ZeroMemory(&pi, sizeof(pi));

    // // Ścieżka do aplikacji, którą chcesz uruchomić
    // LPCSTR appPath = "C:\\path\\to\\your\\application.exe";

    // // Uruchomienie nowego procesu
    // if (!CreateProcessA(NULL, const_cast<LPSTR>(appPath), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
    //     std::cerr << "Błąd uruchamiania procesu: " << GetLastError() << std::endl;
    //     game_downloading = false;
    // }

    // std::cout << "Proces uruchomiony!" << std::endl;


    // // Wymuszenie zakończenia procesu
    // if (!TerminateProcess(pi.hProcess, 0)) {
    //     std::cerr << "Błąd zatrzymywania procesu: " << GetLastError() << std::endl;
    // } else {
    //     std::cout << "Proces zatrzymany!" << std::endl;
    // }

    // // Zamknięcie uchwytów
    // CloseHandle(pi.hProcess);
    // CloseHandle(pi.hThread);
}

void createMD5Files(fs::path steam_dir)
{
    savemd5File(fs::path(steam_dir / "Slime Rancher" / "data").string(), fs::path(steam_dir / "Slime Rancher" / "SlimeRancher.exe").string());
    savemd5File(fs::path(steam_dir / "Slime Rancher" / "data").string(), fs::path(steam_dir / "Slime Rancher" / "SlimeRancher_Data" / "Managed" / "Assembly-CSharp.dll").string());
}

bool comunicate = false;

void steamGuardTimeout(sf::Time elapsed)
{
    if (use_secure_ipc == true)
    {
        if (elapsed > sf::seconds(25))
        {
            system("taskkill /f /im DepotDownloader.exe");
            log_message("Guard authentication time out!", LOG_ERROR);
            log_message("Comunication stopped", LogTypes::LOG_INFO);
            comunicate = false;
            game_downloading = false;
        }    
    }
}

void recieveMessage(const HANDLE& hPipe, const depotProsp depot)
{
    while (true)
    {
        if (comunicate == false)
        {
            break;
        }

        char buffer[1024];
        DWORD bytesRead;
        ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL);

        std::string recieved(buffer, bytesRead);
        if (!recieved.empty())
        {
            auto json = JSON::parse(recieved);

            std::string type = json.getObject().at("type").getString();
            if (type == "LOG")
            {
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();

                log_message(msg, type);

                if (type == LogTypes::LOG_ERROR)
                {
                    CloseHandle(hPipe);
                    log_message("Comunication stopped", LogTypes::LOG_INFO);
                    comunicate = false;
                    game_downloading = false;
                    return;
                }

                recieved.erase();
            }
            else if (type == "DownloadProgress")
            {
                display_download_progress = true;
                downloadInitializing = false;
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();

                int progress = std::stoi(msg);
                MainpageElements::playbar::downloadingProgressText.setString(std::to_string(progress) + " %");
                MainpageElements::playbar::downloadingProgressText.setPosition(640 - (MainpageElements::playbar::downloadingProgressText.getLocalBounds().width / 2), MainpageElements::playbar::progress_bg.getPosition().y);
                float progressbar = progress;
                MainpageElements::playbar::downloadingProgress.setProgress(progressbar / 100.0f);
 
                if (progress == 100)
                {
                    display_download_progress = false;
                    downloadInitializing = true;
                }
            }
            else if (type == "SHD")
            {
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();
                CloseHandle(hPipe);
                log_message(msg, type);
                log_message("Comunication stopped", LogTypes::LOG_INFO);
                comunicate = false;
                game_downloading = false;
                recieved.erase();
                return;
            }
            else if (type == "SUMMARY")
            {
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();
                log_message(msg, type);
                recieved.erase();

                steam_game_dir = SettingsElemets::subcats::general::steam_path_textbox.getText();
                fs::path steam_dir = steam_game_dir;
                fs::path alternate_output_dir = fs::path(instances_dir);
                fs::path outputDir = downloader_path / "output";
                downloadInitializing = true;
                if (fs::exists(outputDir) && fs::is_directory(outputDir))
                {
                    if (mountOnlyData == true)
                    {
                        move_directory(outputDir, alternate_output_dir / fs::path(mounted_instance));
                    }
                    else 
                    {
                        move_directory(outputDir, steam_dir / "Slime Rancher");    
                    }
                    log_message("Game download success", LogTypes::LOG_INFO);
                    game_downloading = false;

                    if (mountOnlyData == true)
                    {
                       createMD5Files(alternate_output_dir);  
                    }
                    else 
                    {
                        createMD5Files(steam_dir);    
                    }
                    
                    if (autolaunch_instances == true)
                    {
                        if (mountOnlyData == true)
                        {
                            prelaunch_tasks(depot.runpath, fs::path(alternate_output_dir / fs::path(mounted_instance)).string());  
                        }
                        else
                        {
                            prelaunch_tasks(depot.runpath, fs::path(steam_dir / "Slime Rancher").string());    
                        }
                    }
                }
                else
                {
                    game_downloading = false;
                    log_message("Game downloading failed!", LogTypes::LOG_ERROR);
                    MessageBoxA(NULL, tr("IDS_MSG_GAMEDOWNLOAD_FAILED").c_str(), "Error", MB_ICONERROR | MB_OK);
                }

                game_downloading = false;
                reset_play_button_text();
            }
            else if (type == "GUARD-appauth-ask")
            {
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();
                log_message(msg, type);
                recieved.erase();

                display_guard_window = true;
                send_guard_code = false;

                sf::Clock timeout;
                do
                {
                    steamGuardTimeout(timeout.getElapsedTime());
                    if (send_guard_code == true)
                    {
                        DWORD bytesWritten;
                        WriteFile(hPipe, guard_code.c_str(), strlen(guard_code.c_str()) + 1, &bytesWritten, NULL);
                    }
                }
                while(send_guard_code != true);
            }
            else if (type == "GUARD-mailauth-ask")
            {
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();
                log_message(msg, type);
                recieved.erase();

                display_guard_window = true;
                send_guard_code = false;

                sf::Clock timeout;
                do
                {
                    steamGuardTimeout(timeout.getElapsedTime());
                    if (send_guard_code == true)
                    {
                        DWORD bytesWritten;
                        WriteFile(hPipe, guard_code.c_str(), strlen(guard_code.c_str()) + 1, &bytesWritten, NULL);
                    }
                }
                while(send_guard_code != true);
            }
            else if (type == "GUARD-mobileConfirm")
            {
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();
                log_message(msg, type);
                recieved.erase();

                MessageBoxA(NULL, tr("IDS_MSG_GAMEDOWNLOAD_MOBILEAUTHREQ").c_str(), "Info", MB_ICONINFORMATION | MB_OK);
            }
            else
            {
                recieved.erase();
            }

        }
    }
}

void downloaderChecker()
{
    sf::Clock checkDelay;

    while(true)
    {
        sf::sleep(sf::milliseconds(500));

        if (comunicate == false)
        {
            break;
        }

        if (checkDelay.getElapsedTime() > sf::seconds(5))
        {
            checkDelay.restart();

            std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("tasklist", "r"), pclose);
            if (!pipe) {
            }

            std::vector<std::string> processList;
            char buffer[128];
            while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
                processList.emplace_back(buffer);
            }

            for (const auto& line : processList) {
                if (line.find("DepotDownloader.exe") != std::string::npos) {
                    log_message("Detected unexpected downloader shutdown!", LOG_WARN);
                    // CloseHandle(hPipe);
                    log_message("Comunication stopped", LogTypes::LOG_INFO);
                    comunicate = false;
                    game_downloading = false;
                }
            }

        }
    }
}

void downloaderPipe(depotProsp& depot)
{
    game_downloading = true;
    downloadInitializing = true;
    
    std::thread animThread(downloading_animation);
    animThread.detach();
    std::thread dt(runDownloader, depot);
    dt.detach();

    if (use_secure_ipc == true)
    {
        std::thread secureIpcThr(downloaderChecker);
        secureIpcThr.detach(); 
    }

    log_message("Preparing comunication pipe", LogTypes::LOG_INFO);

    const char* pipeName = R"(\\.\pipe\DepotDownloaderPipe)";
    HANDLE hPipe = CreateNamedPipeA(
        pipeName,               // Nazwa potoku
        PIPE_ACCESS_DUPLEX,     // Dostęp dwukierunkowy
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  // Tryb komunikatów
        1,                      // Maksymalna liczba instancji
        1024,                   // Rozmiar bufora wyjściowego
        1024,                   // Rozmiar bufora wejściowego
        0,                      // Timeout
        NULL                    // Atrybuty zabezpieczeń
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        log_message("Cannot create pipe: " + GetLastError(), LogTypes::LOG_ERROR);
        return;
    }

    log_message("Waiting for DepotDownloader connection", LogTypes::LOG_INFO);
    BOOL connected = ConnectNamedPipe(hPipe, NULL);
    if (!connected) {
        log_message("Problem with comunication with DepotDownloader: " + GetLastError(), LogTypes::LOG_ERROR);
        CloseHandle(hPipe);
        return;
    }

    log_message("DepotDownloader connected", LogTypes::LOG_INFO);
    MainpageElements::playbar::launchGameButton.setText("Downloading");

    comunicate = true;

    std::thread rcv(recieveMessage, hPipe, depot);
    rcv.detach();
}

//Legacy downloader
void download_game2(std::string gamerun_path)
{
    if (SteamCMDCheck() == true)
    {
        steam_game_dir = SettingsElemets::subcats::general::steam_path_textbox.getText();
        fs::path steam_dir = steam_game_dir;
        fs::path game_dir = steam_dir / "Slime Rancher";
        if (mountOnlyData == true)
        {
            game_dir = fs::path(instances_dir) / fs::path(mounted_instance);
        }

        game_downloading = true;
        MainpageElements::playbar::launchGameButton.setText("Downloading");
        std::thread animThread(downloading_animation);
        animThread.detach();
        fs::path cmdpath = fs::path(steamcmd_dir);
        std::string steamcmdPath = cmdpath.string() + "/steamcmd.exe";

        std::string command = "+login " + decryptor(steam_profile_name) + " +download_depot 433340 433342 " + versionsData_map[instances_list[mounted_instance].getVer()].manifest + " +quit";
        log_message("Running steamCMD command: " + command, LogTypes::LOG_INFO);

        std::string fullCommand = steamcmdPath + " " + command;

        int result = system(fullCommand.c_str());

        if (result == 0)
        {
            log_message("Command executed successfully", LogTypes::LOG_INFO);
            fs::path outputDir = cmdpath / "steamapps" / "content" / "app_433340" / "depot_433342"; 
            if (fs::exists(outputDir) && fs::is_directory(outputDir))
            {
                move_directory(outputDir, steam_dir / "Slime Rancher");
                log_message("Game download success", LogTypes::LOG_INFO);
                game_downloading = false;
                downloadInitializing = true;

                createMD5Files(steam_dir);

                if (autolaunch_instances == true)
                {
                    prelaunch_tasks(gamerun_path, fs::path(steam_dir / "Slime Rancher").string());    
                }
            }
            else
            {
                log_message("Game download falied", LogTypes::LOG_ERROR);
                game_downloading = false;
            }
        }
        else
        {
            log_message("Command cannot be executed", LogTypes::LOG_ERROR);
            game_downloading = false;
        }
    }
    else
    {
        MessageBoxA(NULL, std::string(tr("IDS_MSG_GAMEDOWNLOAD_FAIL") + tr("IDS_MSG_GAMEDOWNLOAD_FAILNOSTEAMCMD")).c_str(), "Error", MB_ICONERROR | MB_OK);
    }
    
    reset_play_button_text();
}

void download_game(std::string gamerun_path)
{
    depotProsp depot;

    fs::path destPath = fs::path(steam_game_dir) / "Slime Rancher";
    if (mountOnlyData == true)
    {
        destPath = fs::path(instances_dir) / fs::path(mounted_instance);
    }
    depot.path = destPath.string();

    log_message("Preparing downloading script", LogTypes::LOG_INFO);
    depot.manifestid = versionsData_map[instances_list[mounted_instance].getVer()].manifest;
    depot.username = decryptor(steam_profile_name);
    depot.password = decryptor(steam_profile_passwd);
    depot.appid = "433340";
    depot.depotid = "433342";
    depot.runpath = gamerun_path;

    if (downloader_selected == depotdownloader)
    {
        log_message("Downloader: DepotDownloader", LogTypes::LOG_INFO);
        if (!depot.username.empty())
        {
            if (!depot.password.empty())
            {
                downloaderPipe(depot);
            }
            else
            {
                std::string msg = tr("IDS_MSG_GAMEDOWNLOAD_FAIL") + tr("IDS_MSG_GAMEDOWNLOAD_FAILNOPASSWORD");
                log_message(msg, LogTypes::LOG_ERROR);
                MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR | MB_OK);
            }
        }
        else
        {
            std::string msg = tr("IDS_MSG_GAMEDOWNLOAD_FAIL") + tr("IDS_MSG_GAMEDOWNLOAD_FAILNOUSERNAME");
            log_message(msg, LogTypes::LOG_ERROR);
            MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR | MB_OK);
        }
    }
    else if (downloader_selected == steamcmd)
    {
        log_message("Downloader: SteamCMD", LogTypes::LOG_INFO);
        download_game2(gamerun_path);
    }
}