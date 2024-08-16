void get_textbox_settings_values_and_save()
{
    steam_game_dir = SlimeRancher_steam_path_textbox.getText();
    instances_dir = SlimeRancher_instances_path_textbox.getText();

    steam_profile_name = SteamProfile_name_textbox.getText();
    steam_profile_passwd = SteamProfile_password_textbox.getText();
    update_config_file();
}