void setDefault_paths()
{
    steam_game_dir = get_steam_default_path();
    instances_dir = instances_path.string();
    steamcmd_dir = cmd_path.string();

    SlimeRancher_steam_path_textbox.setText(steam_game_dir);
    SlimeRancher_instances_path_textbox.setText(instances_dir);
    steamcmd_path_textbox.setText(steamcmd_dir);
}