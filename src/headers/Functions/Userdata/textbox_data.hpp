void get_textbox_settings_values_and_save()
{
    steam_game_dir = SlimeRancher_steam_path_textbox.getText();
    instances_dir = SlimeRancher_instances_path_textbox.getText();

    save_log_files = Save_logs_files_checkbox.getState();
    show_prerelease_version = Show_older_instances_checkbox.getState();
    update_config_file();
}

void get_profile_textboxes_values_and_save()
{
    steam_profile_name = encryptor(SteamProfile_name_textbox.getText());
    steam_profile_passwd = encryptor(SteamProfile_password_textbox.getText());
    loging_manualy = login_manualy_checkbox.getState();
    update_config_file();
}