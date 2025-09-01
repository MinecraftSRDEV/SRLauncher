bool renamedSteam = false;

/**
 * Resets the text of the game launch button to the default label.
 */
void reset_play_button_text()
{
    launch_game_button.setText(PLAY_BUTTON_DEF);
}

/**
 * Updates the playtime for a game instance.
 * 
 * @param instance_id The ID of the game instance.
 * @param path The file path where playtime data is stored.
 * @param time The current session playtime in sf::Time format.
 * 
 * This function calculates the total playtime by adding the session time to the stored playtime,
 * then writes the updated playtime to the instance's info.json file.
 */
void updatePlayTime(const std::string& instance_id, const std::string& path, sf::Time time)
{
    sf::Int64 total = time.asMilliseconds() + std::stoll(instances_list[instance_id].getPlaytime());
    editJsonFile(path + "/info.json", {{{"playtime"},{JSON::String},{std::to_string(total)}}});
}

/**
 * Restores the Steam executable file if it has been renamed.
 * 
 * @return True if the Steam executable was renamed and successfully restored, otherwise false.
 * 
 * This function checks if Steam was previously renamed and, if so, attempts to restore it to its original name.
 * It sets the `renamedSteam` flag to false if the restoration is successful.
 */
bool restoreSteam()
{
    if (renamedSteam == true)
    {
        if (steamRestore())
        {
            renamedSteam = false;    
        }   
    }
    return false;
}

/**
 * Launches the game executable.
 * 
 * @param path The full file path of the game executable.
 * @param gamepath The directory path where game data is stored.
 * 
 * This function handles game launch tasks such as updating the play button status, setting the framerate,
 * and tracking playtime. After the game closes, it updates the total playtime, resets the play button,
 * and restores the Steam executable if it was renamed.
 */
void run_game(std::string path, std::string gamepath)
{
    HWND launcherWindow = window.getSystemHandle();
    launch_game_button.setText("Running");
    log_message("Game running", LogTypes::LOG_INFO);
    if (DebugSettingsUI::debuggingEnabledCheckbox.getState() == false)
    {
        ShowWindow(launcherWindow, SW_MINIMIZE);
    }
    game_running = true;
    
    sf::Clock playTime;
    playTime.restart();
    system(formatPathForSystem(path).c_str());
    window.setFramerateLimit(15);
    ShowWindow(launcherWindow, SW_RESTORE);
    game_running = false;
    log_message("Game closed", LogTypes::LOG_INFO);

    sf::Time session = playTime.getElapsedTime();
    Playtime time = calcPlaytime(session.asMilliseconds());

    log_message("Session play time: " + std::to_string(time.hours) + " H " + std::to_string(time.minutes) + " M " + std::to_string(time.seconds) + " S", LogTypes::LOG_INFO);
    updatePlayTime(mounted_instance, gamepath, session);
    reset_play_button_text();

    restoreSteam();
    clearSessionFile();
}

/**
 * Checks if Steam is currently running.
 * 
 * @return True if the Steam process is running, otherwise false.
 * 
 * This function opens a command pipeline to list system processes and checks if "steam.exe" is in the list.
 */
bool IsSteamRunning()
{
    // Otwarcie potoku dla komendy tasklist
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("tasklist", "r"), pclose);
    if (!pipe) {
        std::cerr << "Nie udało się otworzyć potoku do tasklist.\n";
        return false;
    }

    // Wczytanie wyjścia tasklist do wektora
    std::vector<std::string> processList;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        processList.emplace_back(buffer);
    }

    // Sprawdzanie, czy w procesList znajduje się wpis "Steam.exe"
    for (const auto& line : processList) {
        if (line.find("steam.exe") != std::string::npos) {
            return true; // Znaleziono Steam.exe
        }
    }

    return false; // Nie znaleziono Steam.exe
}

enum steamCheckResults {
    STC_NOTINSTALLED,
    STC_INSTALLED,
    STC_ABBORT,
    STC_TRY,
    STC_SUCCESS,
    STC_EXCEPTION
};

/**
 * Prompts the user to close Steam if it is running.
 * 
 * @return An enum value representing the user's response:
 * - STC_SUCCESS if Steam was closed successfully,
 * - STC_TRY if the user opted to try launching the game without closing Steam,
 * - STC_ABORT if the user chose not to proceed.
 * 
 * If Steam is running, a prompt is displayed to ask the user whether to close it.
 * If unsuccessful, a warning allows the user to continue or abort the launch.
 */
int closeSteamPrompt()
{
    if (IsSteamRunning() == true)
    {
        int result = MessageBoxA(NULL, "Steam allready running\nIf you continue will be automatically closed!", "Warning", MB_ICONEXCLAMATION | MB_YESNO);
        switch(result)
        {
            case IDYES:
            {
                system("taskkill /f /im Steam.exe");    
                if (IsSteamRunning() == true)
                {
                    int result2 = MessageBoxA(NULL, "Steam can't be closed!\n\nYou can try to run game without it, but its not recommended!", "Error", MB_ICONERROR | MB_YESNO);
                    switch(result2)
                    {
                        case IDYES:
                        {
                            return STC_TRY;
                            break;
                        }
                        case IDNO:
                        {
                            return STC_ABBORT;
                            break;
                        }
                    }
                }
                else
                {
                    return STC_SUCCESS;
                }
                break;
            }
            case IDNO:
            {
                return STC_ABBORT;
                break;
            }
        }
    }
    return STC_SUCCESS;
}

/**
 * Performs a Steam installation check and renames the Steam executable if necessary.
 * 
 * @return An enum value indicating the result of the Steam check:
 * - STC_SUCCESS if Steam was renamed successfully,
 * - STC_NOTINSTALLED if Steam is not found,
 * - STC_EXCEPTION if an error occurs,
 * - STC_TRY or STC_ABORT based on the result of closeSteamPrompt.
 * 
 * This function checks if Steam is installed, and if so, renames the executable to prevent updates.
 */
int steamCheck()
{
    switch (closeSteamPrompt())
    {
        case STC_SUCCESS:
        {
            try
            {
                if (fs::exists(steam_default_path / "steam.exe") && fs::is_regular_file(steam_default_path / "steam.exe"))
                {
                    fs::rename(steam_default_path / "steam.exe", steam_default_path / "_steam.exe");    
                    renamedSteam = true;
                    return STC_SUCCESS;
                }
                else
                {
                    return STC_NOTINSTALLED;
                }
            }
            catch (std::exception e)
            {
                return STC_EXCEPTION;
            }           
            break;
        }
        case STC_TRY:
        {
            return STC_TRY;
        }
        case STC_ABBORT:
        {
            return STC_ABBORT;
        }
    }
    return STC_ABBORT;
}

/**
 * Executes necessary tasks before launching the game.
 * 
 * @param game_runpath The path to the game executable.
 * @param gamepath The directory path of the game instance.
 * 
 * This function refreshes the instance list, performs a Steam check, and prompts the user
 * about any potential Steam issues. If conditions are met, it starts the game in a separate thread.
 * Otherwise, it logs a message and resets the play button.
 */
void prelaunch_tasks(std::string game_runpath, std::string gamepath)
{
    if (instances_list.empty())
    {
        refresh_instances_list();
    }

    std::string versionType;
    std::string versionName;

    while (true)
    {
        versionType = versionsData_map[instances_list[mounted_instance].getVer()].version_type;
        versionName = versionsData_map[instances_list[mounted_instance].getVer()].version_name;

        if (instancesListLoading == false)
        {
            break;
        }

        sf::sleep(sf::milliseconds(10));
    }
    int steamCheckResult;

    if (versionType == "pre-release" or versionName != "1.4.4")
    {
        steamCheckResult = steamCheck();    
    }
    else
    {
        steamCheckResult = STC_SUCCESS;
    }

    bool launch_game = true;
    launch_game_button.setText("Launching game");

    if (steamCheckResult == STC_SUCCESS or steamCheckResult == STC_NOTINSTALLED)
    {
        launch_game = true;
    }
    else if (steamCheckResult == STC_TRY)
    {
        if (show_warnings == true)
        {
            getSteamAccountStats();

            if (versionType == "pre-release" or versionName != "1.4.4")
            {
                if (user_offline_mode == result_online)
                {
                    int result = MessageBoxA(NULL, "To avoid Steam auto update to lastes version change your account to OFFLINE MODE.\n\n Still you want to continue?", "Warning", MB_ICONEXCLAMATION | MB_YESNO);
                    switch (result)
                    {
                        case IDYES:
                        {
                            break;
                        }
                        case IDNO:
                        {
                            launch_game = false;
                            break;
                        }
                    }
                }
                else if (user_offline_mode == result_fail)
                {
                    int result = MessageBoxA(NULL, "Make sure if you are in OFFLINE MODE on Steam to avoid auto update to lastes version!\n\n Do you want to continue?", "Warning", MB_ICONEXCLAMATION | MB_YESNO);
                    switch (result)
                    {
                        case IDYES:
                        {
                            launch_game = true;
                            break;
                        }
                        case IDNO:
                        {
                            launch_game = false;
                            break;
                        }
                    }
                }    
            }
        }
    }
    else
    {
        launch_game = false;
    }

    if (launch_game == true)
    {
        createSessionFile({launcher_version, renamedSteam, versionName, mounted_instance, enableDebugging});

        if (DebugSettingsUI::debuggingEnabledCheckbox.getState() == false)
        {
            window.setFramerateLimit(5);
        }
        else
        {
            window.setFramerateLimit(60);
            log_message("Launcher window refresh rate was changed to: 60", LOG_INFO);
        }
        
        std::thread gameThread(run_game, game_runpath, gamepath);
        gameThread.detach();

        if (DebugSettingsUI::debuggingEnabledCheckbox.getState() == true)
        {
            std::thread debugThread(DebugBridge::TryToConnect);
            debugThread.detach();    
        }        
    }
    else
    {
        log_message("Launching task stopped", LogTypes::LOG_INFO);
        reset_play_button_text();
        restoreSteam();
    }
}

/**
 * Prepares a game instance for launching by checking for necessary files and initiating pre-launch tasks.
 * 
 * @param instance_id The ID of the game instance.
 * 
 * This function verifies the existence of the game executable, and if found, calls prelaunch_tasks.
 * If the executable is missing, it attempts to download the game.
 */
void prepareInstance(std::string instance_id)
{
    if (game_downloading == false)
    {
        // fs::path game_dir = defaultDir / "instances" / instance_id;
        steam_game_dir = steam_path_textbox.getText();
        fs::path steam_dir = steam_game_dir;
        fs::path game_dir = steam_dir / "Slime Rancher";
        if (mountOnlyData == true)
        {
            game_dir = fs::path(instances_dir) / fs::path(instance_id);
        }

        std::ifstream executableCheck;
        std::string gamepath = game_dir.string();
        std::string gamerun_path = gamepath + "/SlimeRancher.exe";
        executableCheck.open(gamerun_path.c_str());
        log_message("Preparing to run game...", LogTypes::LOG_INFO);
        if (executableCheck)
        {
            log_message("Executable found", LogTypes::LOG_INFO);
            prelaunch_tasks(gamerun_path, gamepath);
        }
        else
        {
            log_message("Trying to download game", LogTypes::LOG_INFO);
            std::thread downloadThread(download_game, gamerun_path);
            downloadThread.detach();
        }
        executableCheck.close();    
    }
    else
    {
        log_message("Game is now downloading", LogTypes::LOG_INFO);
        MessageBoxA(NULL, "Game is now downloading", "Info", MB_ICONINFORMATION | MB_OK);
    }
}

/**
 * Initiates the process of launching the game, checking if the instance is mounted and not already running.
 * 
 * This function logs errors if there is no instance mounted or if the game is already running.
 * If conditions are met, it proceeds to prepare the instance.
 */
void runGameInitial()
{
    const std::string NO_INSTANCE_MOUNTED = "no slime rancher instance mounted";
    const std::string GAME_RUNNING_ERR = "Game allready running";

    if (game_running == false)
    {
        if (mounted_instance.empty() or mounted_instance == UNMOUNTED_INSTANCE)
        {
            log_message(NO_INSTANCE_MOUNTED, LogTypes::LOG_ERROR);
            MessageBoxA(NULL, NO_INSTANCE_MOUNTED.c_str(), "Error", MB_ICONERROR | MB_OK);
        }
        else
        {
            log_message("Checking instance: " + mounted_instance, LogTypes::LOG_INFO);
            prepareInstance(mounted_instance);
        }// sprawdzenie czy istnieje instancja predlauncherem
    }
    else
    {
        log_message(GAME_RUNNING_ERR, LogTypes::LOG_ERROR);
        MessageBoxA(NULL, GAME_RUNNING_ERR.c_str(), "Error", MB_ICONERROR | MB_OK);
    }
}