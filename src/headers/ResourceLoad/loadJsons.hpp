void positionListElements()
{
    int ver_last_x = 100;
    int ver_last_y = 85;
    for (const auto& pair : versions_pachnotes_list)
    {
        if (Show_older_instances_checkbox.getState() == true and versions_map[versions_pachnotes_list[pair.first].getVersion()].version_type != "pre_release")
        {
            versions_pachnotes_list[pair.first].reposition(ver_last_x, ver_last_y);
            ver_last_x += 266;
            if (ver_last_x > 940)
            {
                ver_last_x = 100;
                ver_last_y += 190;
            }
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
                            log_message("Included MultiMod MD5 wrong", LOG_TYPES::LOG_WARN);
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

            loadVersionPachnotes(name, output.itr);
            create_mods_directories(output);
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
    Show_older_instances_checkbox.setState(show_prerelease_version);
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

bool load_config_file(std::string path_to_config)
{
    try
    {
        JSON json = JSON::parseFromFile(path_to_config);

        try
        {
            steam_game_dir = reduceBackslashes(json.getObject().at("steam_game_dir").getString());
            log_message("Steam game dir: " + steam_game_dir, LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);steam_gamedir_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);steam_gamedir_def();}

        try
        {
            mounted_instance = json.getObject().at("mounted_instance").getString();
            log_message("Mounted instance: " + mounted_instance, LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);}

        try
        {
            instances_dir = reduceBackslashes(json.getObject().at("instances_dir").getString());
            log_message("Instances dir: " + instances_dir, LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);instances_dir_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);instances_dir_def();}

        try
        {
            steamcmd_dir = reduceBackslashes(json.getObject().at("steamcmd_dir").getString());
            log_message("SteamCMD dir: " + steamcmd_dir, LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);steamcmd_dir_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);steamcmd_dir_def();}

        try
        {
            steam_profile_name = json.getObject().at("spn").getString();
            steam_profile_passwd = json.getObject().at("spp").getString();
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);}

        try
        {
            saved_version = json.getObject().at("saved_version").getString();
            log_message("Saved version: " + saved_version, LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);}

        try
        {
            save_log_files = json.getObject().at("save_logs").getBool();
            log_message("Log file autosave: " + std::to_string(save_log_files), LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);save_logs_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);save_logs_def();}

        try
        {
            display_log_colors = json.getObject().at("colored_logs").getBool();
            log_message("Colored logs: " + std::to_string(display_log_colors), LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);logs_color_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);logs_color_def();}

        try
        {
            show_prerelease_version = json.getObject().at("show_prereleases").getBool();
            log_message("Show pre-release game versions: " + std::to_string(show_prerelease_version), LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);show_prerelease_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);show_prerelease_def();}

        try
        {
            autolaunch_instances = json.getObject().at("auto_launch").getBool();
            log_message("autolaunch instances: " + std::to_string(autolaunch_instances), LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);autolaunch_instances_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);autolaunch_instances_def();}

        try
        {
            show_warnings = json.getObject().at("show_warnings").getBool();
            log_message("show_warnings: " + std::to_string(show_warnings), LOG_TYPES::LOG_INFO);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);show_warns_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);show_warns_def();}

        try
        {
            check_updates_when_start = json.getObject().at("auto_update_check").getBool();
            autocheck_for_update_checkbox.setState(check_updates_when_start);
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);autocheck_updates_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);autocheck_updates_def();}

        try
        {
            theme_selected = json.getObject().at("theme").getNumber();
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);theme_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);theme_def();}

        try
        {
            downloader_selected = json.getObject().at("downloader").getNumber();
        }
        catch (std::runtime_error re){std::string errmsg = re.what();log_message("Json error: " + errmsg, LOG_TYPES::LOG_ERROR);downloader_def();}
        catch (std::out_of_range pe){std::string errmsg = pe.what();log_message("Parse error: " + errmsg, LOG_TYPES::LOG_ERROR);downloader_def();}
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