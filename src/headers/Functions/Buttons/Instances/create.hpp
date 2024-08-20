void create_instance()
{
    std::string instance_name = new_instance_name_textbox.getText();
    std::string version_selected = versions_list.getResult();
    if (!instance_name.empty())
    {
        // fs::path new_instance_path = defaultDir / "instances" / instance_name;
        std::string instances_dir = SlimeRancher_instances_path_textbox.getText();
        // fs::path steam_dir = steam_game_dir;
        fs::path steam_dir = instances_dir;
        fs::path new_instance_path = steam_dir / ("Slime Rancher_" + instance_name);
        if (check_directory_exists(new_instance_path) == true)
        {
            log_message("Cannot create instance: Instance with this name exists", LOG_TYPES::LOG_ERROR);
            MessageBoxA(NULL, "Cannot create instance: Instance with this name exists", "Error", MB_ICONERROR | MB_OK);
        }
        else
        {
            if (version_selected != "none")
            {
                if (fs::create_directory(new_instance_path))
                {
                    JSONEncoder::JSONObject obj;

                    obj.add("name", new JSONEncoder::JSONString(instance_name));
                    obj.add("version", new JSONEncoder::JSONString(version_selected));

                    std::string jsonConfig =  obj.stringify();
                    std::ofstream configfile;
                    configfile.open(new_instance_path / "info.json");
                    configfile << jsonConfig;
                    configfile.close();

                    fs::create_directory(new_instance_path / "data");
                    fs::create_directory(new_instance_path / "data" / "gamedata");
                    fs::create_directory(new_instance_path / "data" / "saves");

                    UI_current = UI_PAGES::InstancesMenu;

                    log_message("Instance created successfuly", LOG_TYPES::LOG_INFO);
                    log_message("Instance name: " + instance_name, LOG_TYPES::LOG_INFO);
                    log_message("Instance game version: " + version_selected, LOG_TYPES::LOG_INFO);
                    refresh_instances_list();    
                }
                else
                {
                    log_message("Cannot create instance directory", LOG_TYPES::LOG_ERROR);
                    MessageBoxA(NULL, "Cannot create instance directory", "Error", MB_ICONERROR | MB_OK);
                }
            }
            else
            {
                log_message("Cannot create instance: Version is missing", LOG_TYPES::LOG_ERROR);
                MessageBoxA(NULL, "Cannot create instance: Version is missing", "Error", MB_ICONERROR | MB_OK);
            }
        }  
    }
    else
    {
        log_message("Cannot create instance: Name is missing", LOG_TYPES::LOG_ERROR);
        MessageBoxA(NULL, "Cannot create instance: Name is missing", "Error", MB_ICONERROR | MB_OK);
        //popup error here
    }   
}