std::string constructSubname(std::string instance_id, std::string ver)
{
    std::string output;
    output = instance_id + "-" + ver + "-";
    if (instances_list[instance_id].getModAttributes().SatysModLoader_installed == true)
    {
        output += "SML";
    }
    if (instances_list[instance_id].getModAttributes().StaysModtool_installed == true)
    {
        output += "SMT";
    }
    if (instances_list[instance_id].getModAttributes().UMF_installed == true)
    {
        output += "UMF";
    }
    return output;
}

bool ifInstanceIsEdited(fs::path instnace_dir, std::string instance_id)
{
    auto json = JSON::parseFromFile(instnace_dir.string() + "/info.json");

    try
    {
        std::string ver = json.getObject().at("version").getString();
        std::string ed = json.getObject().at("edited").getString();

        if (!ed.empty())
        {
            if (ed != ver)
            {
                std::string subname = constructSubname(instance_id, ver);

                fs::path instanceEditedDir = edited_path / subname;

                if (check_directory_exists(instanceEditedDir))
                {
                    if (!instanceEditedDir.empty())
                    {
                        int result = MessageBoxA(NULL, "This instance has files from this version", "Info", MB_ICONINFORMATION | MB_YESNO);

                        if (result == IDYES)
                        {
                            move_directory(instnace_dir, instanceEditedDir);
                            directory_auto(instnace_dir);
                            move_directory(instanceEditedDir / "data", instnace_dir / "data");
                            move_file(instanceEditedDir / "info.json", instnace_dir/ "info.json");

                            auto json = JSON::parseFromFile(instnace_dir.string() + "/info.json");

                            JSONEncoder::JSONObject object;

                            std::vector <fileJsonContent> content;
                            fileJsonContent data;

                            data.value = "version";
                            data.type = JSON::String;
                            data.overwrite = json.getObject().at("edited").getString();
                            content.emplace_back(data);

                            data.value = "edited";
                            data.type = JSONEDIT::KEYDELETE;
                            content.emplace_back(data);

                            editJsonFile(instnace_dir.string() + "/info.json", content);

                            MessageBoxA(NULL, "Instance is ready to reinstall", "Info", MB_ICONINFORMATION | MB_OK);
                        }
                    }    
                }
                else
                {
                    try
                    {
                        move_directory(instnace_dir, instanceEditedDir);
                        directory_auto(instnace_dir);
                        move_directory(instanceEditedDir / "data", instnace_dir / "data");
                        move_file(instanceEditedDir / "info.json", instnace_dir/ "info.json");

                        auto json = JSON::parseFromFile(instnace_dir.string() + "/info.json");

                        JSONEncoder::JSONObject object;

                        std::vector <fileJsonContent> content;
                        fileJsonContent data;

                        data.value = "version";
                        data.type = JSON::String;
                        data.overwrite = json.getObject().at("edited").getString();
                        content.emplace_back(data);

                        data.value = "edited";
                        data.type = JSONEDIT::KEYDELETE;
                        content.emplace_back(data);

                        editJsonFile(instnace_dir.string() + "/info.json", content);

                        MessageBoxA(NULL, "Instance is ready to install", "Info", MB_ICONINFORMATION | MB_OK);
                    }
                    catch (std::exception e) {}
                }
            }
            return true;    
        }
    }
    catch (std::exception e) {}
    return false;
}

void mount_function(std::string instance_id)
{
    if (mounted_instance == instances_list[instance_id].getID())
    {
        unmount_funtcion();
        instances_stat_refresh();
    }
    else
    {
        unmount_funtcion();

        steam_game_dir = steam_path_textbox.getText();
        fs::path steam_dir = steam_game_dir;

        if (ifInstanceIsEdited(instances_dir + "/Slime Rancher_" + instances_list[instance_id].getID(), instance_id) == true)
        {
            sync_refresh_instances_list();
            return;
        }

        mounted_instance = instances_list[instance_id].getID();

        fs::path game_dir = steam_dir / ("Slime Rancher_" + mounted_instance);
        fs::path instnace_dir = fs::path(instances_dir) / ("Slime Rancher_" + mounted_instance);

        Mounted_instance_info_text.setString(mounted_instance);
        mounted_instance_version.setString("v." + instances_list[instance_id].getVer());

        try
        {
            if (check_directory_exists(local_save_path))
            {
                if (fs::is_empty(local_save_path))
                {
                    if (fs::exists(instnace_dir / "data" / "gamedata" / "options_and_achivements.prf"))
                    {
                        if (move_file(instnace_dir / "data" / "gamedata" / "options_and_achivements.prf", local_save_path / "slimerancher.prf") != true)
                        {
                            return;
                        }    
                    }
                    
                    if (fs::exists(instnace_dir / "data" / "gamedata" / "slimerancher.cfg"))
                    {
                        if (move_file(instnace_dir / "data" / "gamedata" / "slimerancher.cfg", local_save_path / "slimerancher.cfg") != true)
                        {
                            return;
                        }    
                    }
                    
                    
                    move_directory(instnace_dir / "data" / "saves", local_save_path);    
                }    
            }
        }
        catch (fs::filesystem_error& e)
        {
            log_message(std::string(e.what()), LogTypes::LOG_ERROR);
            MessageBoxA(NULL, "Cannot overwrite savedata files", "Error", MB_ICONERROR | MB_OK);
            return;
        }
        catch (std::exception& e)
        {
            log_message(std::string(e.what()), LogTypes::LOG_ERROR);
            return;
        }

        if (fs::exists(steam_dir / "Slime Rancher") && fs::is_directory(steam_dir / "Slime Rancher"))
        {
            log_message("Cannot overwrite current instance", LogTypes::LOG_ERROR);
            return;
        }
        else
        {
            try
            {
                if (mountOnlyData == false)
                {
                    fs::rename(instnace_dir, steam_dir / "Slime Rancher");    
                }
                log_message("Mounted instance: " + instances_list[instance_id].getID() + " Version: " + instances_list[instance_id].getVer(), LogTypes::LOG_INFO);
                update_config_file();
                instances_stat_refresh();
                
            }
            catch (fs::filesystem_error& e)
            {
                log_message("Cannot mount instance: " + std::string(e.what()), LogTypes::LOG_ERROR);
                return;
            }
        }    
    }
}