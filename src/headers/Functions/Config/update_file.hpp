bool update_config_file()
{
    const std::string FAIL_TEXT = "Cannot save config file: ";

    JSONEncoder::JSONObject config;

    config.add("steam_game_dir", new JSONEncoder::JSONString(steam_game_dir));
    config.add("mounted_instance", new JSONEncoder::JSONString(mounted_instance));
    config.add("instances_dir", new JSONEncoder::JSONString(instances_dir));
    config.add("steamcmd_dir", new JSONEncoder::JSONString(steamcmd_dir));
    config.add("spn", new JSONEncoder::JSONString(steam_profile_name));
    config.add("spp", new JSONEncoder::JSONString(steam_profile_passwd));
    config.add("saved_version", new JSONEncoder::JSONString(saved_version));
    config.add("show_prereleases", new JSONEncoder::JSONBool(show_prerelease_version));
    config.add("save_logs", new JSONEncoder::JSONBool(save_log_files));
    config.add("colored_logs", new JSONEncoder::JSONBool(display_log_colors));
    config.add("auto_launch", new JSONEncoder::JSONBool(autolaunch_instances));
    config.add("show_warnings", new JSONEncoder::JSONBool(show_warnings));
    config.add("auto_update_check", new JSONEncoder::JSONBool(check_updates_when_start));
    config.add("use_secure_ipc", new JSONEncoder::JSONBool(use_secure_ipc));
    config.add("theme", new JSONEncoder::JSONNumber(theme_selected));
    config.add("downloader", new JSONEncoder::JSONNumber(downloader_selected));
    config.add("debugging_enabled", new JSONEncoder::JSONBool(enableDebugging));
    config.add("debug_save_logs_to_other_file", new JSONEncoder::JSONBool(saveDebugLogsToOtherFile));
    config.add("debug_print_logs", new JSONEncoder::JSONBool(printDebugLogs));
    config.add("debug_com_delay", new JSONEncoder::JSONNumber(communicationDelay));
    config.add("debug_com_buffer_size", new JSONEncoder::JSONNumber(comunicationPipeBufferSize));
    
    std::string jsonConfig =  config.stringify();

    if (!jsonConfig.empty())
    {
        std::ofstream configfile;
        configfile.open(configuration_path / "config.json");
        if (configfile.is_open())
        {
            configfile << JSONEncoder::formatJson(jsonConfig);
            configfile.close();
            return true;
        }
        configfile.close();
        log_message(FAIL_TEXT + "cannot open file", LogTypes::LOG_ERROR);
        return false;
    }
    else
    {
        log_message(FAIL_TEXT + "json is empty", LogTypes::LOG_ERROR);
        return false;
    }

    return false;
}