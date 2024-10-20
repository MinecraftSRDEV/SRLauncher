void get_textbox_settings_values_and_save()
{
    steam_game_dir = SlimeRancher_steam_path_textbox.getText();
    instances_dir = SlimeRancher_instances_path_textbox.getText();
    steamcmd_dir = steamcmd_path_textbox.getText();

    save_log_files = Save_logs_files_checkbox.getState();
    display_log_colors = Colored_logs_checkbox.getState();
    autolaunch_instances = automatically_run_downloaded_instances_checkbox.getState();
    show_warnings = do_not_show_warnings_checkbox.getState();
    show_prerelease_version = Show_older_instances_checkbox.getState();

    check_updates_when_start = autocheck_for_update_checkbox.getState();

    std::string result = theme_list_ddl.getRResult();
    theme_selected = std::stoi(result);

    result = downloaders_ddl.getRResult();
    downloader_selected = std::stoi(result);
    update_config_file();
}

void get_profile_textboxes_values_and_save()
{
    steam_profile_name = encryptor(SteamProfile_name_textbox.getText());
    steam_profile_passwd = encryptor(SteamProfile_password_textbox.getText());
    update_config_file();
}