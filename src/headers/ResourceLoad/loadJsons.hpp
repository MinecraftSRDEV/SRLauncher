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
            output.version_type = versionObject.getObject().at("type").getString();
            output.mod_support = versionObject.getObject().at("mod_support").getBool();
            output.release_date = versionObject.getObject().at("date").getString();
            output.manifest = versionObject.getObject().at("manifest").getString();

            versions_map[output.version_name] = output;
        }    
    }
    catch (std::runtime_error re)
    {
        std::string errmsg = re.what();
        log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);
        return false;
    }
    catch (std::out_of_range pe)
    {
        std::string errmsg = pe.what();
        log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);
        return false;
    }
    return true;
}

bool load_config_file(std::string path_to_config)
{
    try
    {
        JSON json = JSON::parseFromFile(path_to_config);

        steam_game_dir = reduceBackslashes(json.getObject().at("steam_game_dir").getString());
        log_message("Steam game dir: " + steam_game_dir, LOG_TYPES::LOG_INFO);

        mounted_instance = json.getObject().at("mounted_instance").getString();
        log_message("Mounted instance: " + mounted_instance, LOG_TYPES::LOG_INFO);

        instances_dir = reduceBackslashes(json.getObject().at("instances_dir").getString());
        log_message("Instances dir: " + instances_dir, LOG_TYPES::LOG_INFO);

        steam_profile_name = json.getObject().at("spn").getString();
        steam_profile_passwd = json.getObject().at("spp").getString();

        saved_version = json.getObject().at("saved_version").getString();
        log_message("Saved version: " + saved_version, LOG_TYPES::LOG_INFO);

        save_log_files = json.getObject().at("save_logs").getBool();
        log_message("Log file autosave: " + std::to_string(save_log_files), LOG_TYPES::LOG_INFO);

        show_prerelease_version = json.getObject().at("show_prereleases").getBool();
        log_message("Show pre-release game versions: " + std::to_string(show_prerelease_version), LOG_TYPES::LOG_INFO);

        loging_manualy = json.getObject().at("login_manually").getBool();
        log_message("Login manually: " + std::to_string(loging_manualy), LOG_TYPES::LOG_INFO);
    }
    catch (std::runtime_error re)
    {
        std::string errmsg = re.what();
        log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);
        return false;
    }
    catch (std::out_of_range pe)
    {
        std::string errmsg = pe.what();
        log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);
        return false;
    }
    return true;
}