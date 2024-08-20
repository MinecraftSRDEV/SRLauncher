/**
 * Unmount mounted instance.
 * Remove mounted instance from config.
 * Rename and move "Slime Rancher" directory from steam game directory to instances directory as "Slime Rancher_INSTANCENAME and separate gamesaves, config and achivements savefile to "data" in instnace directory"
 * 
 * Returns: bool value 
 */
bool unmount_funtcion()
{
    if (!mounted_instance.empty())
    {
        if (mounted_instance != "Unmounted")
        {
            steam_game_dir = SlimeRancher_steam_path_textbox.getText();
            fs::path steam_dir = steam_game_dir;
            try
            {
                fs::path destination_path = fs::path(instances_dir) / ("Slime Rancher_" + mounted_instance);
                fs::rename(steam_dir / "Slime Rancher", destination_path);

                if (fs::exists(local_save_path / "slimerancher.prf"))
                {
                    fs::rename(local_save_path / "slimerancher.prf", destination_path / "data" / "gamedata" / "options_and_achivements.prf");
                }
                if (fs::exists(local_save_path / "slimerancher.cfg"))
                {
                    fs::rename(local_save_path / "slimerancher.cfg", destination_path / "data" / "gamedata" / "slimerancher.cfg");
                }
                
                move_directory(local_save_path, destination_path / "data" / "saves");
                fs::create_directory(local_save_path);
                
                mounted_instance = "Unmounted";
                Mounted_instance_info_text.setString("No instance mounted");
                update_config_file();
                log_message("Instance unmounted", LOG_TYPES::LOG_INFO);
                return true;
            }
            catch
            (fs::filesystem_error& e)
            {
                std::string errormsg = e.what();
                log_message("Cannot unmount instance: " + errormsg, LOG_TYPES::LOG_ERROR);
                return false;
            }
        }
    }
    return false;
}