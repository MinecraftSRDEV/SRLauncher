void positionListElements()
{
    int ver_last_x = 113;
    int ver_last_y = 85;
    for (const auto& pair : versions_pachnotes_list)
    {
        if (show_prerelease_version == false)
        {
            if (versionsData_map[versions_pachnotes_list[pair.first].getVersion()].version_type == "pre-release")
            {
                continue;
            }    
        }
        
        versions_pachnotes_list[pair.first].reposition(ver_last_x, ver_last_y);
        ver_last_x += 266;
        if (ver_last_x > 940)
        {
            ver_last_x = 113;
            ver_last_y += 190;
        }
    }
}

void loadVersionPachnotes(const std::string& name, int iteration)
{
    std::string path_toNotes = "./assets/resources/pachNotes/" + name + ".txt";
    std::string path_toImg = "./assets/resources/pachNotes/" + name + ".png";
    std::ifstream file;
    file.open(path_toNotes.c_str());
    if (file)
    {
        std::string full;
        full.erase();
        std::string line;
        while(getline(file, line))
        {
            std::vector <std::string> lines;
            while (line.length() > 100)
            {
                std::string output = line.substr(0, 89);
                lines.emplace_back(output);
                line = line.substr(89);
            }
            lines.emplace_back(line);

            for (auto& it : lines)
            {
                full += it;
                full += "\n";
            }
            lines.clear();
            
        }

        sf::Texture imageTx;
        if (fs::exists(fs::path(path_toImg)))
        {
            imageTx.loadFromFile(path_toImg.c_str());
        }
        else
        {
            imageTx.loadFromFile("./assets/resources/pachNotes/noImage.png");
        }
        
        versions_pachnotes_list[iteration].create(0, 0, font, imageTx, name, full, theme_selected);
    }
    file.close();
    positionListElements();
}

void create_mods_directories(const SRVersion& prsp)
{
    if (prsp.mod_support == true)
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
            }
        }
        else
        {
            directory_auto(UMFmodsFolder_path.string() + "/" + prsp.version_name);
            directory_auto(SRMLmodsFolder_path.string() + "/" + prsp.version_name);
            directory_auto(SMLFolder_path.string() + "/" + prsp.version_name);
        }
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
            output.version_type = versionObject.getObject().at("type").getString();
            output.mod_support = versionObject.getObject().at("mod_support").getBool();
            output.release_date = versionObject.getObject().at("date").getString();
            output.manifest = versionObject.getObject().at("manifest").getString();
            output.itr = versionObject.getObject().at("iteration").getNumber();
            output.executable_hash = versionObject.getObject().at("SH").getString();
            output.assembly_hash = versionObject.getObject().at("AH").getString();

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
std::string get_steam_default_path();

void steam_gamedir_def()
{
    steam_game_dir = get_steam_default_path();
    SlimeRancher_steam_path_textbox.setText(steam_game_dir);
}
void instances_dir_def()
{
    instances_dir = instances_path.string();
    SlimeRancher_instances_path_textbox.setText(instances_dir);
}
void steamcmd_dir_def()
{
    steamcmd_dir = cmd_path.string();
    steamcmd_path_textbox.setText(steamcmd_dir);
}
void show_prerelease_def()
{
    show_prerelease_version = true;
    Show_prereleases_checkbox.setState(show_prerelease_version);
}
void save_logs_def()
{
    save_log_files = true;
    Save_logs_files_checkbox.setState(save_log_files);
}
void logs_color_def()
{
    display_log_colors = true;
    Colored_logs_checkbox.setState(display_log_colors);
}
void autolaunch_instances_def()
{
    autolaunch_instances = true;
    automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);
}
void show_warns_def()
{
    show_warnings = true;
    do_not_show_warnings_checkbox.setState(show_warnings);
}
void autocheck_updates_def()
{
    check_updates_when_start = true;
    autocheck_for_update_checkbox.setState(check_updates_when_start);
}

void theme_def()
{
    theme_selected = ColorPalete::Bright;
}

void downloader_def()
{
    downloader_selected = depotdownloader;
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

        loadConfigKeyStr(json, steam_game_dir, "steam_game_dir", "Steam game dir: ", steam_gamedir_def);
        SlimeRancher_steam_path_textbox.setText(steam_game_dir);

        loadConfigKeyStr(json, mounted_instance, "mounted_instance", "Mounted instance: ", nullptr);

        loadConfigKeyStr(json, instances_dir, "instances_dir", "Instances dir: ", instances_dir_def);
        SlimeRancher_instances_path_textbox.setText(instances_dir);

        loadConfigKeyStr(json, steamcmd_dir, "steamcmd_dir", "SteamCMD dir: ", steamcmd_dir_def);
        steamcmd_path_textbox.setText(steamcmd_dir);

        loadConfigKeyStr(json, steam_profile_name, "spn", "", nullptr);
        loadConfigKeyStr(json, steam_profile_passwd, "spp", "", nullptr);
        loadConfigKeyStr(json, saved_version, "saved_version", "Saved version: ", nullptr);

        loadConfigKeyBool(json, save_log_files, "save_logs", "Log file autosave: ", save_logs_def);
        Save_logs_files_checkbox.setState(save_log_files);

        loadConfigKeyBool(json, display_log_colors, "colored_logs", "Colored logs: ", logs_color_def);
        Colored_logs_checkbox.setState(display_log_colors);

        loadConfigKeyBool(json, show_prerelease_version, "show_prereleases", "Show pre-release game versions: ", show_prerelease_def);
        Show_prereleases_checkbox.setState(show_prerelease_version);

        loadConfigKeyBool(json, autolaunch_instances, "auto_launch", "autolaunch instances: ", autolaunch_instances_def);
        automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);
        
        loadConfigKeyBool(json, show_warnings, "show_warnings", "show_warnings: ", show_warns_def);
        do_not_show_warnings_checkbox.setState(show_warnings);

        loadConfigKeyBool(json, check_updates_when_start, "auto_update_check", "update check: ", autocheck_updates_def);
        autocheck_for_update_checkbox.setState(check_updates_when_start);

        loadConfigKeyInt(json, theme_selected, "theme", "theme: ", theme_def);

        loadConfigKeyInt(json, downloader_selected, "downloader", "downloader: ", downloader_def);
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