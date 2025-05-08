class DebugBridge {
    public:

    static void TryToConnect()
    {
        log_message("Preparing comunication pipe", LogTypes::LOG_INFO);

        const char* pipeName = R"(\\.\pipe\DebugBridge)";
        HANDLE debPipe = CreateNamedPipeA(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1, comunicationPipeBufferSize, comunicationPipeBufferSize, 0, NULL);

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

    static void Comunicate(const HANDLE& hPipe)
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
                    debugWorking.setFillColor(sf::Color::Red);
                    ind_state = 1;
                    break;
                }
                case 1:
                {
                    debugWorking.setFillColor(sf::Color::Green);
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

            debugIpcElapsedText.setString("IPC delayed: " + std::to_string(delayed.asMilliseconds()) + " MS | buffer size: " + std::to_string(sizeof(buffer)) + " bytes, Allocated: " + std::to_string(bytesAllocated) + " bytes | Logs queue: " + std::to_string(logsCount) + " entries");
            sf::sleep(sf::milliseconds(communicationDelay));
        }

        stopDebugging(hPipe);
    }

    static void stopDebugging(const HANDLE& hPipe)
    {
        CloseHandle(hPipe);
        log_message("Debugging stopped", LogTypes::LOG_INFO);
    }

    private:

    struct LogEntry
    {
        int type;
        std::string message;
    };

    static LogEntry getLog(const std::string& str)
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

    enum
    {
        noDisplayLog = 23748348
    };
};