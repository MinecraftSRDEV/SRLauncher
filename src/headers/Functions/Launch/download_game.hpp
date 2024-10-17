void prelaunch_tasks(std::string game_runpath);
void reset_play_button_text();

struct depotProsp
{
    std::string appid;
    std::string depotid;
    std::string manifestid;
    std::string username;
    std::string password;
    std::string path;
    std::string runpath;
};

void runDownloader(const depotProsp& depot)
{
    std::string command = downloader_path.string() + "/DepotDownloader.exe -app "
    + depot.appid + " -depot " + depot.depotid + " -manifest " + depot.manifestid + " -username " + depot.username + " -password " + depot.password + " -dir " + downloader_path.string() + "/output";
    std::cout << "running : " << command << std::endl;
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

bool comunicate = false;

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

                if (type == LOG_TYPES::LOG_ERROR)
                {
                    CloseHandle(hPipe);
                    log_message("Comunication stopped", LOG_TYPES::LOG_INFO);
                    comunicate = false;
                    game_downloading = false;
                    return;
                }

                recieved.erase();
            }
            else if (type == "DownloadProgress")
            {
                display_download_progress = true;
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();

                int progress = std::stoi(msg);
                downloading_progress_text.setString(std::to_string(progress) + " %");
                downloading_progress_text.setPosition(640 - (downloading_progress_text.getLocalBounds().width / 2), progress_bg.getPosition().y);

                if (progress == 100)
                {
                    display_download_progress = false;
                }
            }
            else if (type == "SHD")
            {
                std::string msg = json.getObject().at("msg").getString();
                int type = json.getObject().at("logType").getNumber();
                CloseHandle(hPipe);
                log_message(msg, type);
                log_message("Comunication stopped", LOG_TYPES::LOG_INFO);
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
                game_downloading = false;
                recieved.erase();

                steam_game_dir = SlimeRancher_steam_path_textbox.getText();
                fs::path steam_dir = steam_game_dir;
                fs::path outputDir = downloader_path / "output"; 
                if (fs::exists(outputDir) && fs::is_directory(outputDir))
                {
                    move_directory(outputDir, steam_dir / "Slime Rancher");
                    log_message("Game download success", LOG_TYPES::LOG_INFO);
                    game_downloading = false;
                    if (autolaunch_instances == true)
                    {
                        prelaunch_tasks(depot.runpath);
                    }
                }

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

                do
                {
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

                do
                {
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

                MessageBoxA(NULL, "Mobile authentication is required", "Info", MB_ICONINFORMATION | MB_OK);
            }
            else
            {
                recieved.erase();
            }

        }
    }
}

void downloaderPipe(depotProsp& depot)
{
    game_downloading = true;
    launch_last_instance_button.setText("Downloading");
    std::thread animThread(downloading_animation);
    animThread.detach();

    std::thread dt(runDownloader, depot);
    dt.detach();

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
        std::cerr << "Błąd tworzenia potoku: " << GetLastError() << std::endl;
        return;
    }

    std::cout << "Czekam na połączenie z DepotDownloader..." << std::endl;
    BOOL connected = ConnectNamedPipe(hPipe, NULL);
    if (!connected) {
        std::cerr << "Nie udało się połączyć: " << GetLastError() << std::endl;
        CloseHandle(hPipe);
        return;
    }

    std::cout << "Połączono z DepotDownloader!" << std::endl;

    comunicate = true;

    std::thread rcv(recieveMessage, hPipe, depot);
    rcv.detach();

    
    // const char* args = "arguments";
    // DWORD bytesWritten;
    // WriteFile(hPipe, args, strlen(args) + 1, &bytesWritten, NULL);
}

void download_game2(std::string gamerun_path)
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
        std::string steamcmdPath = cmdpath.string() + "/steamcmd.exe";

        std::string command = "+login " + decryptor(steam_profile_name) + " +download_depot 433340 433342 " + versions_map[instances_list[mounted_instance].getVer()].manifest + " +quit";
        log_message("Running steamCMD command: " + command, LOG_TYPES::LOG_INFO);

        std::string fullCommand = steamcmdPath + " " + command;

        int result = system(fullCommand.c_str());

        if (result == 0)
        {
            log_message("Command executed successfully", LOG_TYPES::LOG_INFO);
            fs::path outputDir = cmdpath / "steamapps" / "content" / "app_433340" / "depot_433342"; 
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

void download_game(std::string gamerun_path)
{
    depotProsp depot;

    fs::path destPath = fs::path(steam_game_dir) / "Slime Rancher";
    depot.path = destPath.string();

    depot.manifestid = versions_map[instances_list[mounted_instance].getVer()].manifest;
    depot.username = decryptor(steam_profile_name);
    depot.password = decryptor(steam_profile_passwd);
    depot.appid = "433340";
    depot.depotid = "433342";
    depot.runpath = gamerun_path;

    if (downloader_selected == depotdownloader)
    {
        if (!depot.username.empty())
        {
            if (!depot.password.empty())
            {
                downloaderPipe(depot);
            }
            else
            {
                std::string msg = "Cannot download game: No steam password configured!";
                log_message(msg, LOG_TYPES::LOG_ERROR);
                MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR | MB_OK);
            }
        }
        else
        {
            std::string msg = "Cannot download game: No steam username configured!";
            log_message(msg, LOG_TYPES::LOG_ERROR);
            MessageBoxA(NULL, msg.c_str(), "Error", MB_ICONERROR | MB_OK);
        }
    }
    else if (downloader_selected == steamcmd)
    {
        download_game2(gamerun_path);
    }
}