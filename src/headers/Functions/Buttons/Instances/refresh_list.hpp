void instances_stat_refresh()
{
    for(const auto& pair : instances_list)
    {
        if (mounted_instance == pair.first)
        {
            instances_list[pair.first].updateStatus(instance_list_class::status::Mounted);
        }
        else
        {
            instances_list[pair.first].updateStatus(instance_list_class::status::Unmounted);
        }
    }
}

int last_insnace_entry_y = 85;



void add_instance(fs::path path)
{
    std::string path_str = path.string();
    InstanceModAttributes modsAttribs;
    if (check_directory_exists(path) == true)
    {
        if (fs::exists(path_str + "/info.json"))
        {
            bool instance_installed_status_placeholder = false;

            JSON json = JSON::parseFromFile(path_str + "/info.json");

            std::string name = json.getObject().at("name").getString();
            std::string version = json.getObject().at("version").getString();

            if (check_file_exists(path_str + "/SlimeRancher.exe") == true)
            {
                instance_installed_status_placeholder = true;
                if (versions_map[version].mod_support == true)
                {
                    if (versions_map[version].version_type == "pre-release")
                    {
                        if (fs::exists(path_str + "/SlimeRancher_Data/Managed/SlimeRancherModtool.dll"))
                        {
                            modsAttribs.StaysModtool_installed = true;
                        }  
                    }
                    else if (versions_map[version].version_type == "stable-release")
                    {
                        if (fs::exists(path_str + "/SlimeRancher_Data/Managed/UnityCoreMod.dll"))
                        {
                            modsAttribs.SatysModLoader_installed = true;
                        }
                        if (fs::exists(path_str + "/SlimeRancher_Data/Managed/uModFramework.dll"))
                        {
                            modsAttribs.UMF_installed = true;
                        }
                    }
                    
                }    
            }
            else
            {
                instance_installed_status_placeholder = false;
            }

            instances_list[name].create(10, last_insnace_entry_y, 1260, 80, name, version, font, modsAttribs);
            last_insnace_entry_y += 85;
            instances_list[name].setInstalledStatus(instance_installed_status_placeholder);
        }
        else
        {
            log_message("Cannot find \"info.json\" file in: " + path.string() + "!", LOG_TYPES::LOG_WARN);
            // MessageBoxA(NULL, "Cannot find \"info.json\" file in game directory!", "Warning", MB_ICONEXCLAMATION);
        }
    }
}

void refresh_instances_list()
{
    instances_list.clear();
    last_insnace_entry_y = 85;

    fs::path instances_path = instances_dir;

    add_instance(fs::path(steam_game_dir) / "Slime Rancher");

    try
    {
        for (const auto& entry : fs::directory_iterator(instances_path))
        {
            add_instance(instances_path / entry.path());
        }    
    }
    catch (fs::filesystem_error e)
    {
        std::string errormsg = e.what();
        log_message("Instance refresh error: " + errormsg, LOG_TYPES::LOG_ERROR);
    }
    

    instances_stat_refresh();
}