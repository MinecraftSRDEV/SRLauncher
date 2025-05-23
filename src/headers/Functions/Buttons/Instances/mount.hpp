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
        mounted_instance = instances_list[instance_id].getID();
        Mounted_instance_info_text.setString(mounted_instance);
        mounted_instance_version.setString("v." + instances_list[instance_id].getVer());

        steam_game_dir = SlimeRancher_steam_path_textbox.getText();
        fs::path steam_dir = steam_game_dir;
        fs::path game_dir = steam_dir / ("Slime Rancher_" + mounted_instance);
        fs::path instnace_dir = fs::path(instances_dir) / ("Slime Rancher_" + mounted_instance);

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
                fs::rename(instnace_dir, steam_dir / "Slime Rancher");
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