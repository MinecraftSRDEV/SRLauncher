void create_instance(const std::string& instance_name, const std::string& version_selected, const std::string& icon_id = "pink", bool aytoc = false)
{
    const std::string FAIL_TEXT = "Cannot create instance: ";
    try
    {
        if (!instance_name.empty())
        {
            // fs::path new_instance_path = defaultDir / "instances" / instance_name;
            std::string instances_dir = SlimeRancher_instances_path_textbox.getText();
            // fs::path steam_dir = steam_game_dir;
            fs::path steam_dir = instances_dir;
            fs::path new_instance_path = steam_dir / ("Slime Rancher_" + instance_name);
            if (check_directory_exists(new_instance_path) == true)
            {
                log_message(FAIL_TEXT + instdi::EXST_FAIL, LogTypes::LOG_ERROR);
                MessageBoxA(NULL, std::string(FAIL_TEXT + instdi::EXST_FAIL).c_str(), "Error", MB_ICONERROR | MB_OK);
            }
            else
            {
                if (version_selected != "none" and !version_selected.empty())
                {
                    if (fs::create_directory(new_instance_path))
                    {
                        JSONEncoder::JSONObject obj;

                        obj.add("name", new JSONEncoder::JSONString(instance_name));
                        obj.add("version", new JSONEncoder::JSONString(version_selected));
                        obj.add("icon", new JSONEncoder::JSONString(icon_id));
                        obj.add("playtime", new JSONEncoder::JSONString("0"));

                        std::string jsonConfig =  JSONEncoder::formatJson(obj.stringify());
                        std::ofstream configfile;
                        configfile.open(new_instance_path / "info.json");
                        configfile << jsonConfig;
                        configfile.close();

                        fs::create_directory(new_instance_path / "data");
                        fs::create_directory(new_instance_path / "data" / "gamedata");
                        fs::create_directory(new_instance_path / "data" / "saves");

                        log_message("Instance created successfuly", LogTypes::LOG_INFO);
                        log_message("Instance name: " + instance_name, LogTypes::LOG_INFO);
                        log_message("Instance game version: " + version_selected, LogTypes::LOG_INFO);

                        if (aytoc == false)
                        {
                            UI_current = UiPages::InstancesMenu;
                            refresh_instances_list();        
                        }
                    }
                    else
                    {
                        log_message("Cannot create instance directory", LogTypes::LOG_ERROR);
                        MessageBoxA(NULL, "Cannot create instance directory", "Error", MB_ICONERROR | MB_OK);
                    }
                }
                else
                {
                    log_message(FAIL_TEXT + instdi::VERS_FAIL, LogTypes::LOG_ERROR);
                    MessageBoxA(NULL, std::string(FAIL_TEXT + instdi::VERS_FAIL).c_str(), "Error", MB_ICONERROR | MB_OK);
                }
            }  
        }
        else
        {
            log_message(FAIL_TEXT + instdi::NAME_FAIL, LogTypes::LOG_ERROR);
            MessageBoxA(NULL, std::string(FAIL_TEXT + instdi::NAME_FAIL).c_str(), "Error", MB_ICONERROR | MB_OK);
        }       
    }
    catch (std::exception e)
    {
        log_message(FAIL_TEXT + std::string(e.what()), LogTypes::LOG_ERROR);
    }
}

void instance_params()
{
    create_instance(new_instance_name_textbox.getText(), versions_list_ddl.getResult(), getInstanceSelectedIcon());
}

void generate_instances_list()
{
    for (const auto& pair : versionsData_map)
    {
        create_instance("SR_" + pair.second.version_name, pair.second.version_name, "pink", true);
    }
}