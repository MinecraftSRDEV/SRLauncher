void update_config_file()
{
    JSONEncoder::JSONObject config;

    config.add("steam_game_dir", new JSONEncoder::JSONString(steam_game_dir));
    config.add("mounted_instance", new JSONEncoder::JSONString(mounted_instance));
    config.add("instances_dir", new JSONEncoder::JSONString(instances_dir));
    config.add("steamcmd_dir", new JSONEncoder::JSONString(steamcmd_dir));
    config.add("spn", new JSONEncoder::JSONString(steam_profile_name));
    // config.add("spp", new JSONEncoder::JSONString(steam_profile_passwd));
    config.add("saved_version", new JSONEncoder::JSONString(saved_version));
    config.add("login_manually", new JSONEncoder::JSONBool(loging_manualy));
    config.add("show_prereleases", new JSONEncoder::JSONBool(show_prerelease_version));
    config.add("save_logs", new JSONEncoder::JSONBool(save_log_files));
    config.add("colored_logs", new JSONEncoder::JSONBool(display_log_colors));
    config.add("auto_launch", new JSONEncoder::JSONBool(autolaunch_instances));
    config.add("show_warnings", new JSONEncoder::JSONBool(show_warnings));
    
    std::string jsonConfig =  config.stringify();
    std::ofstream configfile;
    configfile.open(configuration_path / "config.json");
    configfile << JSONEncoder::formatJson(jsonConfig);;
    configfile.close();
}