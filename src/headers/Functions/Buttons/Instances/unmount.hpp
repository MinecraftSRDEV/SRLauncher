/**
 * Unmount mounted instance.
 * Remove mounted instance from config.
 * Rename and move "Slime Rancher" directory from steam game directory to instances directory as "Slime Rancher_INSTANCENAME and separate gamesaves, config and achivements savefile to "data" in instnace directory"
 * 
 * @return bool value 
 */
bool unmount_funtcion()
{
    const std::string FAIL_TEXT = "Cannot unmount instance: ";

    if (!mounted_instance.empty())
    {
        if (mounted_instance != UNMOUNTED_INSTANCE)
        {
            steam_game_dir = steam_path_textbox.getText();
            fs::path steam_dir = steam_game_dir;
            try
            {
                fs::path destination_path = fs::path(instances_dir) / ("Slime Rancher_" + mounted_instance);

                if (fs::exists(destination_path) != true)
                {
                    fs::rename(steam_dir / "Slime Rancher", destination_path);
                }
                else
                {
                    log_message(FAIL_TEXT + "folder with this name exists", LogTypes::LOG_ERROR);
                    return false;
                }

                if (fs::exists(local_save_path / "slimerancher.prf"))
                {
                    if (move_file(local_save_path / "slimerancher.prf", destination_path / "data" / "gamedata" / "options_and_achivements.prf") != true)
                    {
                        return false;
                    }    
                }

                if (fs::exists(local_save_path / "slimerancher.cfg"))
                {
                    if (move_file(local_save_path / "slimerancher.cfg", destination_path / "data" / "gamedata" / "slimerancher.cfg") != true)
                    {
                        return false;
                    }    
                }
                
                move_directory(local_save_path, destination_path / "data" / "saves");
                fs::create_directory(local_save_path);
                
                mounted_instance = UNMOUNTED_INSTANCE;
                Mounted_instance_info_text.setString("No instance mounted");
                mounted_instance_version.setString("");
                update_config_file();
                log_message("Instance unmounted", LogTypes::LOG_INFO);
                return true;
            }
            catch
            (fs::filesystem_error& e)
            {
                log_message(FAIL_TEXT + std::string(e.what()), LogTypes::LOG_ERROR);
                return false;
            }
            catch
            (std::exception e)
            {
                log_message(FAIL_TEXT + std::string(e.what()), LogTypes::LOG_ERROR);
                return false;
            }
        }
    }
    return false;
}