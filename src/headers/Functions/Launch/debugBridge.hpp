namespace DebugBridge {
    HANDLE debPipe;

    struct LogEntry
    {
        int type;
        std::string message;
    };

    enum
    {
        noDisplayLog = 23748348
    };

    LogEntry getLog(const std::string& str)
    {
        LogEntry output;
        try
        {
            output.message = str.substr(1);
            output.type = noDisplayLog;

            if (str[0] == '0')
            {
                if (acceptInfoLogs)
                output.type = LOG_INFO;
            }
            if (str[0] == '1')
            {
                if (acceptWarningLogs)
                output.type = LOG_WARN;
            }
            if (str[0] == '2')
            {
                if (acceptErrorLogs)
                output.type = LOG_ERROR;
            }
            if (str[0] == '3')
            {
                if (acceptExceptionLogs)
                output.type = LOG_EXCEPTION;
            }
        }
        catch (std::exception e) {}
        
        return output;
    }

    void stopDebugging(const HANDLE& hPipe)
    {
        CloseHandle(hPipe);
        log_message("Debugging stopped", LogTypes::LOG_INFO);
    }

    void Comunicate(const HANDLE& hPipe)
    {
        bool debComunicate = true;

        int ind_state = 0;

        DWORD bytesReaded = 0;
        DWORD totalBytesAvailable = 0;
        DWORD bytesLeft = 0;

        sf::Clock IPCDelayed;

        while (true)
        {
            sf::Time delayed = IPCDelayed.getElapsedTime();
            IPCDelayed.restart();
            
            switch (ind_state)
            {
                case 0:
                {
                    MainpageElements::debuger::working.setFillColor(sf::Color::Red);
                    ind_state = 1;
                    break;
                }
                case 1:
                {
                    MainpageElements::debuger::working.setFillColor(sf::Color::Green);
                    ind_state = 0;
                    break;
                }
            }

            if (debComunicate == false)
            {
                break;
            }

            char buffer[comunicationPipeBufferSize];

            if (PeekNamedPipe(hPipe, buffer, sizeof(buffer), &bytesReaded, &totalBytesAvailable, &bytesLeft))
            {}
            else
            {
                DWORD error = GetLastError();
                if (error == ERROR_BROKEN_PIPE)
                {
                    debComunicate = false;
                    break;
                }
            }

            DWORD bytesRead;
            ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL);

            int logsCount = 0;

            std::string recieved(buffer, bytesRead);
            int bytesAllocated = recieved.length();
            if (!recieved.empty())
            {
                LogEntry newLog = getLog(recieved);
                if (newLog.type != noDisplayLog)
                {
                    log_message(newLog.message, newLog.type);    
                }
                
                recieved.erase();
                logs.clear();
            }

            MainpageElements::debuger::ipcElapsedText.setString("IPC delayed: " + std::to_string(delayed.asMilliseconds()) + " MS | buffer size: " + std::to_string(sizeof(buffer)) + " bytes, Allocated: " + std::to_string(bytesAllocated) + " bytes | Logs queue: " + std::to_string(logsCount) + " entries");
            sf::sleep(sf::milliseconds(communicationDelay));
        }

        stopDebugging(hPipe);
    }

    void TryToConnect()
    {
        log_message("Preparing comunication pipe", LogTypes::LOG_INFO);

        const char* pipeName = R"(\\.\pipe\DebugBridge)";
        debPipe = CreateNamedPipeA(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1, comunicationPipeBufferSize, comunicationPipeBufferSize, 0, NULL);

        if (debPipe == INVALID_HANDLE_VALUE) {
            log_message("Cannot create pipe: " + GetLastError(), LogTypes::LOG_ERROR);
            return;
        }

        log_message("Waiting for SR connection", LogTypes::LOG_INFO);
        BOOL debConnected = ConnectNamedPipe(debPipe, NULL);
        if (!debConnected) {
            log_message("Problem with comunication with SR: " + GetLastError(), LogTypes::LOG_ERROR);
            CloseHandle(debPipe);
            return;
        }

        log_message("Slime Rancher Connected", LogTypes::LOG_INFO);
        Comunicate(debPipe);
    }

    void forceClose()
    {
        if (CloseHandle(debPipe) == true)
        {
            log_message("Forced pipe close", LogTypes::LOG_INFO);
        }
        else
        {
            log_message("Pipe can't be closed!", LogTypes::LOG_ERROR);
        }
        
    }

    void killInstance()
    {
        system("taskkill /f /im SlimeRancher.exe");
    }

    void applyDebugPathToInstance()
    {
        SRL_DP_DEF_PATH = runtime_directory / "assets" / "components" / "debug_patcher" / "SRDebugPatcher" / "bin" / "Release" / "net8.0" / "SRDebugPatcher.exe";
        SRL_DB40_DEF_PATH = runtime_directory / "assets" / "components" / "debug_patcher" / "DebugBridge" / "bin" / "Release" / "net40" / "DebugBridge.dll";
        SRL_DB48_DEF_PATH = runtime_directory / "assets" / "components" / "debug_patcher" / "DebugBridge" / "bin" / "Release" / "net48" / "DebugBridge.dll";

        int result = MessageBoxA(NULL, "This will install patch to currently mounted instance. If instance is modded, may by incompatybile with some loaders.\n\nRequire .NET runtime 8 to apply patch.\n\nDo you want to continue?", "info", MB_ICONQUESTION | MB_YESNO);

        if (result == IDYES)
        {
            std::string command = SRL_DP_DEF_PATH.string();
            command += " \"";
            command += steam_game_dir;
            command += "/Slime Rancher/SlimeRancher_Data/Managed/Assembly-CSharp.dll\"";
            command += " ";
            command += steam_game_dir;
            command += "/Slime Rancher/SlimeRancher_Data/Managed/DebugBridge.dll";

            fs::path bridgePath;

            if (versionsData_map[mounted_instance].debugCompatybile == "net40")
            {
                command += SRL_DB40_DEF_PATH.string();
                bridgePath = fs::path(SRL_DB40_DEF_PATH);
            }
            else
            {
                command += SRL_DB48_DEF_PATH.string();
                bridgePath = fs::path(SRL_DB48_DEF_PATH);
            }

            try
            {
                fs::copy_file(bridgePath, fs::path(steam_game_dir + "/Slime Rancher/SlimeRancher_Data/Managed/DebugBridge.dll"));
            }
            catch (fs::filesystem_error e)
            {
                std::string message = "Cannot apply debug patch: " + std::string(e.what());
                log_message(message, LOG_ERROR);
                MessageBoxA(NULL, message.c_str(), "Error", MB_ICONERROR | MB_OK);
                return;
            }

            log_message("Applying debug patch", LOG_INFO);
            system(command.c_str());

            if (fs::exists(fs::path(steam_game_dir + "/Slime Rancher/SlimeRancher_Data/Managed/Assembly-CSharp.dll_patched")))
            {
                try
                {
                    fs::rename(fs::path(steam_game_dir + "/Slime Rancher/SlimeRancher_Data/Managed/Assembly-CSharp.dll"), fs::path(steam_game_dir + "/Slime Rancher/SlimeRancher_Data/Managed/Assembly-CSharp.dll_prepatch"));
                    fs::rename(fs::path(steam_game_dir + "/Slime Rancher/SlimeRancher_Data/Managed/Assembly-CSharp.dll_patched"), fs::path(steam_game_dir + "/Slime Rancher/SlimeRancher_Data/Managed/Assembly-CSharp.dll"));
                }
                catch (fs::filesystem_error e)
                {
                    std::string message = "Cannot apply debug patch: " + std::string(e.what());
                    log_message(message, LOG_ERROR);
                    MessageBoxA(NULL, message.c_str(), "Error", MB_ICONERROR | MB_OK);
                    return;
                }
            }
            else
            {
                std::string message = "Failed to apply debug patch";
                log_message(message, LOG_ERROR);
                MessageBoxA(NULL, message.c_str(), "Error", MB_ICONERROR | MB_OK);
                return;
            }    

            log_message("Patch applied successfully", LOG_ERROR);
            MessageBoxA(NULL, "Patch applied successfully", "Error", MB_ICONERROR | MB_OK);
        }
    }

    void saveLogs()
    {
        std::string file_name = "debug_log_" + std::to_string(run_YEAR) + "_" + std::to_string(run_DAY) + "_" + std::to_string(run_MONTH) + "_" + std::to_string(run_H) + "_" + std::to_string(run_M) + "_" + std::to_string(run_S) + ".txt";

        std::ofstream log_file;
        log_file.open(logs_path.string() + "/" + file_name);

        for (const auto& pair : logs)
        {
            log_file << pair.second << std::endl;
        }
        log_file.close();  
    }
};