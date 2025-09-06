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

struct instanceAttribs {
    std::string name;
    std::string version;
    std::string edited;
    std::string iconId;
    std::string importPath;
    std::string path_str;
    std::string playTime;

    fs::path directory_path;
    InstanceModAttributes modsAttribs;
};

bool add_instance(fs::path path, int itr)
{
    instanceAttribs inst;
    
    inst.path_str = path.string();
    inst.directory_path = path;
    if (check_directory_exists(path) == true)
    {
        if (fs::exists(inst.path_str + "/info.json"))
        {
            bool instance_installed_status_placeholder = false;

            JSON json = JSON::parseFromFile(inst.path_str + "/info.json");

            inst.name = json.getObject().at("name").getString();
            inst.version = json.getObject().at("version").getString();
            try
            {
                inst.edited = json.getObject().at("edited").getString();
            }
            catch(std::exception){}
            try
            {
                inst.iconId = json.getObject().at("icon").getString();
            }
            catch(std::exception){}
            if (inst.iconId.empty())
            {
                inst.iconId = "pink";
            }
            try
            {
                inst.playTime = json.getObject().at("playtime").getString();
            }
            catch(std::exception)
            {
                inst.playTime = "0";
            }

            if (fs::exists(inst.path_str + "/SlimeRancher.exe") == true)
            {
                instance_installed_status_placeholder = true;

                if (versionsData_map[inst.version].version_type == "pre-release")
                {
                    if (fs::exists(inst.path_str + "/SlimeRancher_Data/Managed/SlimeRancherModtool.dll"))
                    {
                        inst.modsAttribs.StaysModtool_installed = true;
                    }
                    if (fs::exists(inst.path_str + "/SlimeRancher_Data/Managed/BetterBuildMods.dll"))
                    {
                        inst.modsAttribs.isBetterBuild04x_installed = true;
                    }
                }
                else if (versionsData_map[inst.version].version_type == "stable-release")
                {
                    if (fs::exists(inst.path_str + "/SlimeRancher_Data/Managed/UnityCoreMod.dll"))
                    {
                        inst.modsAttribs.SatysModLoader_installed = true;
                    }
                    if (fs::exists(inst.path_str + "/SlimeRancher_Data/Managed/uModFramework.dll"))
                    {
                        inst.modsAttribs.UMF_installed = true;
                    }
                    if (fs::exists(inst.path_str + "/SlimeRancher_Data/Managed/SRML.dll"))
                    {
                        inst.modsAttribs.SRML_installed = true;
                    }
                }
            }
            else
            {
                instance_installed_status_placeholder = false;
            }

            instances_list[inst.name].create(10, last_insnace_entry_y, 1260, 80, inst.name, inst.version, instance_icons_textures[inst.iconId], playtime_clock_tx, font, window, inst.modsAttribs, itr, inst.playTime);
            last_insnace_entry_y += 85;
            instances_list[inst.name].setInstalledStatus(instance_installed_status_placeholder);
            instances_list[inst.name].setEditedStatus(inst.edited);
            instances_list_iterations[itr] = inst.name;
            return true;
        }
        else
        {
            log_message("Cannot find \"info.json\" file in: " + path.string() + "!", LogTypes::LOG_WARN);
            // MessageBoxA(NULL, "Cannot find \"info.json\" file in game directory!", "Warning", MB_ICONEXCLAMATION);
        }
    }
    return false;
}

void loadInstancesList(fs::path instances_path)
{
    setUiProtection(true);

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
        log_message("Instance refresh error: " + std::string(e.what()), LogTypes::LOG_ERROR);
    }
    
    instances_stat_refresh();

    if (mounted_instance != UNMOUNTED_INSTANCE)
    {
        mounted_instance_version.setString("v." + instances_list[mounted_instance].getVer());
    }

    instancesListLoading = false;

    setUiProtection(false);
}

void prepeareProcess(bool async = false)
{
    window.setMouseCursor(waitCursor);
    instances_list.clear();
    instances_list_iterations.clear();
    instance_list_b.erase();
    instance_list_l.erase();
    last_insnace_entry_y = 85;

    no_instances_text.setPosition((window.getSize().x / 2) - (no_instances_text.getLocalBounds().width / 2), 320);
    instances_vanish_tooltip_text.setPosition((window.getSize().x / 2) - (instances_vanish_tooltip_text.getLocalBounds().width / 2), 770);

    fs::path instances_path = instances_dir;

    dataLoading_text.setString("Loading instances...");
    dataLoading_text.setPosition((window.getSize().x / 2) - (credits_programming_text.getLocalBounds().width / 2), 320);
    instancesListLoading = true;

    if (async)
    {
        std::thread loadThr(loadInstancesList, instances_path);
        loadThr.detach();    
    }
    else
    {
        loadInstancesList(instances_path);
    }
    window.setMouseCursor(arrowCursor);
}

void refresh_instances_list()
{
    prepeareProcess(true);
}

void sync_refresh_instances_list()
{
    prepeareProcess(false);
}