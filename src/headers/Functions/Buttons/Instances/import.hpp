bool getfolder_import_instance()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty() and fs::is_directory(fs::path(input_path)) == true)
    {
        import_instance_path_textbox.setText(input_path);
        fs::path filepath(input_path);
        import_instance_name_textbox.setText(filepath.stem().string());
        return true;
    }
    return false;
}

void import_instance()
{
    std::string instance_name = import_instance_name_textbox.getText();
    fs::path source_path = import_instance_path_textbox.getText();
    std::string version_selected = versions_list.getResult();
    if (!instance_name.empty())
    {
        std::string instances_dir = SlimeRancher_instances_path_textbox.getText();
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
                std::string message = "Source directory:\n" + source_path.string() + "\nwill be moved to launcher instances directory:\n" + new_instance_path.string() + "\n\nDo you want to continue?";
                int result = MessageBoxA(NULL, message.c_str(), "Warning", MB_ICONEXCLAMATION | MB_YESNO);

                switch(result)
                {
                    case IDNO:
                    {
                        break;
                    }
                    case IDYES:
                    {
                        if (fs::create_directory(new_instance_path))
                        {
                            JSONEncoder::JSONObject obj;

                            obj.add("name", new JSONEncoder::JSONString(instance_name));
                            obj.add("version", new JSONEncoder::JSONString(version_selected));
                            obj.add("source_path", new JSONEncoder::JSONString(source_path.string()));

                            std::string jsonConfig =  JSONEncoder::formatJson(obj.stringify());
                            std::ofstream configfile;
                            configfile.open(new_instance_path / "info.json");
                            configfile << jsonConfig;
                            configfile.close();

                            fs::create_directory(new_instance_path / "data");
                            fs::create_directory(new_instance_path / "data" / "gamedata");
                            fs::create_directory(new_instance_path / "data" / "saves");

                            move_directory(source_path, new_instance_path);

                            UI_current = UI_PAGES::InstancesMenu;

                            log_message("Instance imported successfuly", LOG_TYPES::LOG_INFO);
                            log_message("Instance name: " + instance_name, LOG_TYPES::LOG_INFO);
                            log_message("Instance game version: " + version_selected, LOG_TYPES::LOG_INFO);
                            refresh_instances_list();    
                        }
                        else
                        {
                            log_message("Cannot create instance directory", LOG_TYPES::LOG_ERROR);
                            MessageBoxA(NULL, "Cannot create instance directory", "Error", MB_ICONERROR | MB_OK);
                        }
                        break;
                    }
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