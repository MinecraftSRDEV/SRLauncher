void backup_orginal_game(fs::path gamedir)
{
    try
    {
        log_message("Creating autobackup of: \"" + gamedir.string(), LogTypes::LOG_INFO);
        directory_auto(autobackup_path / "Slime Rancher");
        fs::copy(gamedir, autobackup_path / "Slime Rancher");
        log_message("Creating autobackup of: \"" + local_save_path.string(), LogTypes::LOG_INFO);
        directory_auto(autobackup_path / "savedata");
        fs::copy(local_save_path, autobackup_path / "savedata");    
    }
    catch (fs::filesystem_error e)
    {
        std::string errormsg = e.what();
        log_message("Backup error: " + errormsg, LogTypes::LOG_ERROR);
    }
    
}

void rename_orginal_dir()
{
    steam_game_dir = SlimeRancher_steam_path_textbox.getText();
    fs::path steam_dir = steam_game_dir;
    fs::path orginal_game_dir = steam_dir / "Slime Rancher";
    fs::path renamed_game_dir = steam_dir / "Slime Rancher_orginal";

    if (fs::exists(orginal_game_dir) && fs::is_directory(orginal_game_dir))
    {
        // fs::rename(orginal_game_dir, renamed_game_dir);
        backup_orginal_game(orginal_game_dir);
    }
    else
    {
        log_message("No Slime Rancher instance detected in: \"" + orginal_game_dir.string() + "\"", LogTypes::LOG_INFO);
    }
}