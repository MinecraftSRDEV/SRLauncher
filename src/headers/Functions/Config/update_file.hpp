void update_config_file()
{
    JSONEncoder::JSONObject config;

    config.add("steam_game_dir", new JSONEncoder::JSONString(steam_game_dir));
    config.add("mounted_instance", new JSONEncoder::JSONString(mounted_instance));
    config.add("instances_dir", new JSONEncoder::JSONString(instances_dir));
    config.add("spn", new JSONEncoder::JSONString(steam_profile_name));
    config.add("spp", new JSONEncoder::JSONString(steam_profile_passwd));
    
    std::string jsonConfig =  config.stringify();
    std::ofstream configfile;
    configfile.open(configuration_path / "config.json");
    configfile << jsonConfig;
    configfile.close();
}