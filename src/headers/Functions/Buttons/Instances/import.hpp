std::string calcFileMD(const std::string& path);

bool getfolder_import_instance()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty() and fs::is_directory(fs::path(input_path)) == true)
    {
        iconBarScrollWhile("pink");

        import_instance_path_textbox.setText(input_path);
        fs::path filepath(input_path);
        import_instance_name_textbox.setText(filepath.stem().string());
        std::string chksum = calcFileMD(fs::path(fs::path(input_path) / "SlimeRancher_Data" / "Managed" / "Assembly-CSharp.dll").string());
        std::string version_id;
        for (const auto& pair : versionsData_map)
        {
            if (versionsData_map[pair.first].assembly_hash == chksum)
            {
                version_id = pair.first;
                break;
            }
        }

        if (!version_id.empty())
        {
            versions_list_ddl.setFromResult(version_id);
        }
        version_id.erase();
        return true;
    }
    return false;
}

void import_instance()
{
    const std::string FAIL_TEXT = "Cannot import instance: ";

    std::string instance_name = import_instance_name_textbox.getText();
    fs::path source_path = import_instance_path_textbox.getText();
    std::string version_selected = versions_list_ddl.getResult();
    if (!instance_name.empty())
    {
        std::string instances_dir = SettingsElemets::subcats::general::instances_path_textbox.getText();
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
                            obj.add("icon", new JSONEncoder::JSONString(getInstanceSelectedIcon()));
                            obj.add("playtime", new JSONEncoder::JSONString("0"));

                            std::string jsonConfig =  JSONEncoder::formatJson(obj.stringify());
                            std::ofstream configfile;
                            configfile.open(new_instance_path / "info.json");
                            configfile << jsonConfig;
                            configfile.close();

                            fs::create_directory(new_instance_path / "data");
                            fs::create_directory(new_instance_path / "data" / "gamedata");
                            fs::create_directory(new_instance_path / "data" / "saves");

                            move_directory(source_path, new_instance_path);

                            UI_current = UiPages::InstancesMenu;

                            log_message("Instance imported successfuly", LogTypes::LOG_INFO);
                            log_message("Instance name: " + instance_name, LogTypes::LOG_INFO);
                            log_message("Instance game version: " + version_selected, LogTypes::LOG_INFO);
                            refresh_instances_list();    
                        }
                        else
                        {
                            log_message("Cannot create instance directory", LogTypes::LOG_ERROR);
                            MessageBoxA(NULL, "Cannot create instance directory", "Error", MB_ICONERROR | MB_OK);
                        }
                        break;
                    }
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