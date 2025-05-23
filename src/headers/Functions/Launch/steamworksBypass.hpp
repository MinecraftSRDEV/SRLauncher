SessionData loadSessionData()
{
    std::string filename = "sessionData.tmp";
    fs::path filePath = configuration_path / fs::path(filename);

    SessionData data;
    
    if (check_file_exists(filePath, false))
    {
        try
        {
            JSON json = JSON::parseFromFile(filePath.string());

            loadConfigKeyStr(json, data.usedLauncherVer, "launcherVer", "", nullptr);
            loadConfigKeyStr(json, data.gameVersion, "gameVersion", "", nullptr);
            loadConfigKeyStr(json, data.instanceName, "instanceName", "", nullptr);
            loadConfigKeyBool(json, data.steamRenamed, "steamRenamed", "", nullptr);
            loadConfigKeyBool(json, data.debuggingEnabled, "debuggingEnabled", "", nullptr);

            data.loaded = true;    
        }
        catch (std::exception e) {}
    }

    return data;
}

void createSessionFile(SessionData data)
{
    JSONEncoder::JSONObject sessionInfo;

    sessionInfo.add("launcherVer", new JSONEncoder::JSONString(data.usedLauncherVer));
    sessionInfo.add("gameVersion", new JSONEncoder::JSONString(data.gameVersion));
    sessionInfo.add("instanceName", new JSONEncoder::JSONString(data.instanceName));
    sessionInfo.add("steamRenamed", new JSONEncoder::JSONBool(data.steamRenamed));
    sessionInfo.add("debuggingEnabled", new JSONEncoder::JSONBool(data.debuggingEnabled));

    std::string output = JSONEncoder::formatJson(sessionInfo.stringify());

    std::ofstream save(fs::path(configuration_path.string() / fs::path("sessionData.tmp")));
    save << output;
    save.close();
}

void clearSessionFile()
{
    std::ofstream clearFile(fs::path(configuration_path.string() / fs::path("sessionData.tmp")));
    clearFile << "";
    clearFile.close();
}

bool steamRestore()
{
    try
    {
        fs::rename(steam_default_path / "_steam.exe", steam_default_path / "steam.exe");
        return true;
    }
    catch (fs::filesystem_error e)
    {
        log_message("Can't unlock Steam client! : " + std::string(e.what()), LOG_EXCEPTION);
    }
    catch (std::exception e) {}
    return false;
}

void checkSession()
{
    SessionData thisData = loadSessionData();
    if (thisData.loaded)
    {
        if (thisData.steamRenamed)
        {
            int result = MessageBoxA(NULL, "It appears that the session on the older version of the game has been started, but has not ended properly, which has caused the Steam client to be blocked in order to launch this version of the game.\n\nDo you want to unlock Steam client now? (recommended)", 
            "Info", MB_ICONQUESTION | MB_YESNO);

            switch (result)
            {
                case IDYES:
                {
                    if (steamRestore())
                    {
                        clearSessionFile();
                        log_message("Steam client was unlocked successfully", LOG_INFO);
                    }
                    break;
                }
                case IDNO:
                {
                    MessageBoxA(NULL, "Remember: To manualy unlock Steam client go to your Steam instalation folder and rename \"_Steam.exe\" to \"Steam.exe\"", "Info", MB_ICONINFORMATION | MB_OK);
                    break;
                }
            }
        }
    }
}