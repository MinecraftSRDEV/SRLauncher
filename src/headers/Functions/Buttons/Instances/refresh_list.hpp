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



bool add_instance(fs::path path, int itr)
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

            if (fs::exists(path_str + "/SlimeRancher.exe") == true)
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

            instances_list[name].create(10, last_insnace_entry_y, 1260, 80, name, version, font, modsAttribs, itr);
            last_insnace_entry_y += 85;
            instances_list[name].setInstalledStatus(instance_installed_status_placeholder);
            instances_list_iterations[itr] = name;
            return true;
        }
        else
        {
            log_message("Cannot find \"info.json\" file in: " + path.string() + "!", LOG_TYPES::LOG_WARN);
            // MessageBoxA(NULL, "Cannot find \"info.json\" file in game directory!", "Warning", MB_ICONEXCLAMATION);
        }
    }
    return false;
}

void loadInstancesList(fs::path instances_path)
{
    int iteration = 0;

    if (add_instance(fs::path(steam_game_dir) / "Slime Rancher", iteration) == true)
    {
        iteration++;
    }

    try
    {
        for (const auto& entry : fs::directory_iterator(instances_path))
        {
            if (add_instance(instances_path / entry.path(), iteration) == true)
            {
                iteration++;
            }
        }    
    }
    catch (fs::filesystem_error e)
    {
        std::string errormsg = e.what();
        log_message("Instance refresh error: " + errormsg, LOG_TYPES::LOG_ERROR);
    }
    
    instances_stat_refresh();

    if (mounted_instance != "Unmounted")
    {
        mounted_instance_version.setString("v." + instances_list[mounted_instance].getVer());
    }

    instancesListLoading = false;
}

void refresh_instances_list()
{
    instances_list.clear();
    instances_list_iterations.clear();
    instance_list_b.erase();
    instance_list_l.erase();
    last_insnace_entry_y = 85;

    fs::path instances_path = instances_dir;

    dataLoading_text.setString("Loading instances...");
    dataLoading_text.setPosition((window.getSize().x / 2) - (credits_programming_text.getLocalBounds().width / 2), 320);
    instancesListLoading = true;

    std::thread loadThr(loadInstancesList, instances_path);
    loadThr.detach();
}