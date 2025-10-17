void create_mods_directories(const SRVersion& prsp)
{
    if (prsp.version_type == "pre-release")
    {
        directory_auto(SMTFolder_path.string() + "/" + prsp.version_name);
        if (prsp.version_name == "0.2.6")
        {
            try
            {
                if (!fs::exists(SMTFolder_path / "0.2.6/SRMultimod.dll"))
                {
                    fs::copy_file(fs::path("./assets/components/mods/SRMultimod.dll"), SMTFolder_path / "0.2.6/SRMultimod.dll");
                }
                else
                {
                    MD5 ModHash;
                    std::string installedMD5 = ModHash.calculateFromFile(fs::path(SMTFolder_path / "0.2.6/SRMultimod.dll").string());
                    std::string includedMD5 = ModHash.calculateFromFile("./assets/components/mods/SRMultimod.dll");

                    if (installedMD5 != includedMD5)
                    {
                        fs::remove(SMTFolder_path / "0.2.6/SRMultimod.dll");
                        fs::copy_file(fs::path("./assets/components/mods/SRMultimod.dll"), SMTFolder_path / "0.2.6/SRMultimod.dll");
                        log_message("Included MultiMod MD5 wrong", LogTypes::LOG_WARN);
                    }
                }
            }
            catch (fs::filesystem_error e)
            {
                return;
            }
            catch (std::runtime_error e)
            {

            }

            try
            {
                if (!fs::exists(SMTFolder_path / "0.2.6/SRDebugBridge.dll"))
                {
                    fs::copy_file(fs::path("./assets/components/mods/SRDebugBridge.dll"), SMTFolder_path / "0.2.6/SRDebugBridge.dll");
                }
                else
                {
                    MD5 ModHash;
                    std::string installedMD5 = ModHash.calculateFromFile(fs::path(SMTFolder_path / "0.2.6/SRDebugBridge.dll").string());
                    std::string includedMD5 = ModHash.calculateFromFile("./assets/components/mods/SRDebugBridge.dll");

                    if (installedMD5 != includedMD5)
                    {
                        fs::remove(SMTFolder_path / "0.2.6/SRDebugBridge.dll");
                        fs::copy_file(fs::path("./assets/components/mods/SRDebugBridge.dll"), SMTFolder_path / "0.2.6/SRDebugBridge.dll");
                        log_message("Included SRDebugBridge MD5 wrong", LogTypes::LOG_WARN);
                    }
                }
            }
            catch (fs::filesystem_error e)
            {
                return;
            }
            catch (std::runtime_error e)
            {

            }
        }
    }
    else
    {
        directory_auto(UMFmodsFolder_path.string() + "/" + prsp.version_name);
        directory_auto(SRMLmodsFolder_path.string() + "/" + prsp.version_name);
        directory_auto(SMLFolder_path.string() + "/" + prsp.version_name);
    }
}

bool load_versions_list()
{
    try
    {
        JSON json = JSON::parseFromFile("./assets/config/versions.json");

        for (auto it = json.getObject().begin(); it != json.getObject().end(); ++it)
        {
            const std::string& name = it->first;
            const JSON& versionObject = it->second;

            SRVersion output;

            output.version_name = name;
            output.version_marker = versionObject.getObject().at("version_marker").getString();
            output.version_type = versionObject.getObject().at("type").getString();
            output.release_date = versionObject.getObject().at("date").getString();
            output.manifest = versionObject.getObject().at("manifest").getString();
            output.itr = versionObject.getObject().at("iteration").getNumber();
            output.executable_hash = versionObject.getObject().at("SH").getString();
            output.assembly_hash = versionObject.getObject().at("AH").getString();

            output.savegame_info.readable_version = versionObject.getObject().at("gamesaves").getObject().at("readable_version").getBool();
            output.savegame_info.format = versionObject.getObject().at("gamesaves").getObject().at("format").getNumber();
            output.savegame_info.single_file = versionObject.getObject().at("gamesaves").getObject().at("single_file").getBool();

            output.debugCompatybile = versionObject.getObject().at("debugCompatybile").getString();

            loadVersionPachnotes(name, output.itr);
            create_mods_directories(output);
            versionsData_map[output.version_name] = output;
        }    
    }
    catch (std::runtime_error re)
    {
        std::string errmsg = re.what();
        log_message("Json error: " + errmsg, LogTypes::LOG_ERROR);
        return false;
    }
    catch (std::out_of_range pe)
    {
        std::string errmsg = pe.what();
        log_message("Parse error: " + errmsg, LogTypes::LOG_ERROR);
        return false;
    }
    return true;
}

typedef void (*FunctionType)();
void loadConfigKeyStr(const JSON& json, std::string& value, const std::string& key, const std::string& message, FunctionType defaultFunction)
{
    try
    {
        value = reduceBackslashes(json.getObject().at(key).getString());
        if (!message.empty())
        {
            log_message(message + value, LogTypes::LOG_INFO);       
        }
    }
    catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LogTypes::LOG_ERROR);if(defaultFunction != nullptr){defaultFunction();}}
    catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LogTypes::LOG_ERROR);if(defaultFunction != nullptr){defaultFunction();}}    
}

void loadConfigKeyInt(const JSON& json, int& value, const std::string& key, const std::string& message, FunctionType defaultFunction)
{
    try
    {
        value = json.getObject().at(key).getNumber();
        if (!message.empty())
        {
            log_message(message + std::to_string(value), LogTypes::LOG_INFO);       
        }    
    }
    catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LogTypes::LOG_ERROR);if(defaultFunction != nullptr){defaultFunction();}}
    catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LogTypes::LOG_ERROR);if(defaultFunction != nullptr){defaultFunction();}}  
}

void loadConfigKeyBool(const JSON& json, bool& value, const std::string& key, const std::string& message, FunctionType defaultFunction)
{
    try
    {
        value = json.getObject().at(key).getBool();
        if (!message.empty())
        {
            log_message(message + std::to_string(value), LogTypes::LOG_INFO);       
        }    
    }
    catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LogTypes::LOG_ERROR);if(defaultFunction != nullptr){defaultFunction();}}
    catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LogTypes::LOG_ERROR);if(defaultFunction != nullptr){defaultFunction();}}  
}

bool load_config_file(std::string path_to_config)
{
    try
    {
        JSON json = JSON::parseFromFile(path_to_config);

        loadConfigKeyStr(json, launcher_language, "launcher_language", "SRL language: ", settings_defaults::language_def);

        loadConfigKeyStr(json, steam_game_dir, "steam_game_dir", "Steam game dir: ", settings_defaults::steam_gamedir_def);
        SettingsElemets::subcats::general::steam_path_textbox.setText(steam_game_dir);

        loadConfigKeyStr(json, mounted_instance, "mounted_instance", "Mounted instance: ", nullptr);

        loadConfigKeyStr(json, instances_dir, "instances_dir", "Instances dir: ", settings_defaults::instances_dir_def);
        SettingsElemets::subcats::general::instances_path_textbox.setText(instances_dir);

        loadConfigKeyStr(json, steamcmd_dir, "steamcmd_dir", "SteamCMD dir: ", settings_defaults::steamcmd_dir_def);
        SettingsElemets::subcats::downloading::steamcmd_path_textbox.setText(steamcmd_dir);

        loadConfigKeyStr(json, steam_profile_name, "spn", "", nullptr);
        loadConfigKeyStr(json, steam_profile_passwd, "spp", "", nullptr);
        loadConfigKeyStr(json, saved_version, "saved_version", "Saved version: ", nullptr);

        loadConfigKeyBool(json, save_log_files, "save_logs", "Log file autosave: ", settings_defaults::save_logs_def);
        SettingsElemets::subcats::general::Save_logs_files_checkbox.setState(save_log_files);

        loadConfigKeyBool(json, display_log_colors, "colored_logs", "Colored logs: ", settings_defaults::logs_color_def);
        SettingsElemets::subcats::general::Colored_logs_checkbox.setState(display_log_colors);

        loadConfigKeyBool(json, show_prerelease_version, "show_prereleases", "Show pre-release game versions: ", settings_defaults::show_prerelease_def);
        SettingsElemets::subcats::general::Show_prereleases_checkbox.setState(show_prerelease_version);

        loadConfigKeyBool(json, autolaunch_instances, "auto_launch", "autolaunch instances: ", settings_defaults::autolaunch_instances_def);
        SettingsElemets::subcats::downloading::automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);
        
        loadConfigKeyBool(json, show_warnings, "show_warnings", "show_warnings: ", settings_defaults::show_warns_def);
        SettingsElemets::subcats::general::do_not_show_warnings_checkbox.setState(show_warnings);

        loadConfigKeyBool(json, check_updates_when_start, "auto_update_check", "update check: ", settings_defaults::autocheck_updates_def);
        SettingsElemets::subcats::updates::autocheck_for_update_checkbox.setState(check_updates_when_start);

        loadConfigKeyBool(json, use_secure_ipc, "use_secure_ipc", "secure ipc: ", settings_defaults::use_secure_ipc_def);
        SettingsElemets::subcats::general::use_secure_ipc_checkbox.setState(use_secure_ipc);

        loadConfigKeyBool(json, mountOnlyData, "mount_only_data", "only data: ", settings_defaults::mount_only_data_def);
        SettingsElemets::subcats::general::mount_only_data_checkbox.setState(mountOnlyData);

        loadConfigKeyInt(json, theme_selected, "theme", "theme: ", settings_defaults::theme_def);

        loadConfigKeyInt(json, downloader_selected, "downloader", "downloader: ", settings_defaults::downloader_def);

        loadConfigKeyBool(json, enableDebugging, "debugging_enabled", "debugging: ", settings_defaults::debugging_enable_def);
        SettingsElemets::subcats::debug::debuggingEnabledCheckbox.setState(enableDebugging);

        loadConfigKeyBool(json, saveDebugLogsToOtherFile, "debug_save_logs_to_other_file", "debug save logs to other file: ", settings_defaults::debug_savelogs_def);
        SettingsElemets::subcats::debug::saveDebugLogsToOtherFileCheckbox.setState(saveDebugLogsToOtherFile);

        loadConfigKeyBool(json, printDebugLogs, "debug_print_logs", "debug print logs: ", settings_defaults::debug_print_all_def);
        SettingsElemets::subcats::debug::printDebugLogsCheckbox.setState(printDebugLogs);

        loadConfigKeyInt(json, communicationDelay, "debug_com_delay", "debug com delay: ", settings_defaults::debug_com_delay_def);
        SettingsElemets::subcats::debug::comunicationDelayTextbox.setText(std::to_string(communicationDelay));

        loadConfigKeyInt(json, comunicationPipeBufferSize, "debug_com_buffer_size", "debug com buffer size: ", settings_defaults::debug_com_buffersize_def);
        SettingsElemets::subcats::debug::comunicationPipeBufferSizeTextbox.setText(std::to_string(comunicationPipeBufferSize));

        loadConfigKeyBool(json, acceptInfoLogs, "debug_accept_info_logs", "", settings_defaults::debug_acc_info_def);
        SettingsElemets::subcats::debug::acceptInfoCheckbox.setState(acceptInfoLogs);

        loadConfigKeyBool(json, acceptWarningLogs, "debug_accept_warning_logs", "", settings_defaults::debug_acc_warn_def);
        SettingsElemets::subcats::debug::acceptWarningCheckbox.setState(acceptWarningLogs);

        loadConfigKeyBool(json, acceptErrorLogs, "debug_accept_error_logs", "", settings_defaults::debug_acc_err_def);
        SettingsElemets::subcats::debug::acceptErrorCheckbox.setState(acceptErrorLogs);

        loadConfigKeyBool(json, acceptExceptionLogs, "debug_accept_exception_logs", "", settings_defaults::debug_acc_excp_def);
        SettingsElemets::subcats::debug::acceptExceptionCheckbox.setState(acceptExceptionLogs);

        loadConfigKeyStr(json, srlBackgroundPath, "background_path", "backgroundPath: ", settings_defaults::background_path_def);
        SettingsElemets::subcats::general::SRL_background_img_path_textbox.setText(srlBackgroundPath);
        reloadLauncherBackground();
    }
    catch (std::runtime_error re)
    {
        std::string errmsg = re.what();
        log_message("Json error: " + errmsg, LogTypes::LOG_ERROR);
        return false;
    }
    catch (std::out_of_range pe)
    {
        std::string errmsg = pe.what();
        log_message("Parse error: " + errmsg, LogTypes::LOG_ERROR);
        return false;
    }
    return true;
}