void rename_orginal_dir()
{
    steam_game_dir = SlimeRancher_steam_path_textbox.getText();
    fs::path steam_dir = steam_game_dir;
    fs::path orginal_game_dir = steam_dir / "Slime Rancher";
    fs::path renamed_game_dir = steam_dir / "Slime Rancher_orginal";

    log_message("Renamed orginal game dir from: \"" + orginal_game_dir.string() + "\" to: \"" + renamed_game_dir.string() + "\"", LOG_TYPES::LOG_INFO);

    if (fs::exists(orginal_game_dir) && fs::is_directory(orginal_game_dir))
    {
        // fs::rename(orginal_game_dir, renamed_game_dir);
    }
    else
    {
        log_message("No Slime Rancher instance detected in: \"" + orginal_game_dir.string() + "\"", LOG_TYPES::LOG_INFO);
    }
}