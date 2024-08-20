void load_versions_list()
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
    }
    catch (std::out_of_range pe)
    {
        std::string errmsg = pe.what();
        log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);
    }
}

void load_config_file(std::string path_to_config)
{
    try
    {
        JSON json = JSON::parseFromFile(path_to_config);

        steam_game_dir = reduceBackslashes(json.getObject().at("steam_game_dir").getString());
        mounted_instance = json.getObject().at("mounted_instance").getString();
        instances_dir = reduceBackslashes(json.getObject().at("instances_dir").getString());
        steam_profile_name = json.getObject().at("spn").getString();
        steam_profile_passwd = json.getObject().at("spp").getString();    
    }
    catch (std::runtime_error re)
    {
        std::string errmsg = re.what();
        log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);
    }
    catch (std::out_of_range pe)
    {
        std::string errmsg = pe.what();
        log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);
    }
}