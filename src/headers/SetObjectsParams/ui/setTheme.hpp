void setTheme()
{
    new_instance_button.setTheme(theme_selected);
    import_instnace_button.setTheme(theme_selected);
    create_button.setTheme(theme_selected);
    instance_creation_cancel.setTheme(theme_selected);
    import_instance_path_browse_button.setTheme(theme_selected);
    import_instance_confirm_button.setTheme(theme_selected);
    import_instance_cancel_button.setTheme(theme_selected);
    MainCategory_button.setTheme(theme_selected);
    InstancesCategory_button.setTheme(theme_selected);
    SettingsCategory_button.setTheme(theme_selected);
    VersionsCategory_button.setTheme(theme_selected);
    Subcat_settings_main_button.setTheme(theme_selected);
    SlimeRancher_steam_path_getfolder_button.setTheme(theme_selected);
    SlimeRancher_instances_path_getfolder_button.setTheme(theme_selected);
    steamcmd_path_getfolder_button.setTheme(theme_selected);
    RestoreSettings_button.setTheme(theme_selected);
    SaveConfig_button.setTheme(theme_selected);
    Subcat_settings_progile_button.setTheme(theme_selected);
    save_profile_button.setTheme(theme_selected);
    Subcat_settings_updates_button.setTheme(theme_selected);
    check_for_update_button.setTheme(theme_selected);
    manage_vanilla_saves_button.setTheme(theme_selected);
    manage_mod_saves_button.setTheme(theme_selected);
    manage_betterbuild_world_button.setTheme(theme_selected);
    manage_backups_button.setTheme(theme_selected);
    manage_mods_button.setTheme(theme_selected);
    manage_main_back_button.setTheme(theme_selected);
    Subcat_settings_credits_button.setTheme(theme_selected);
    launch_last_instance_button.setTheme(theme_selected);
    version_back_button.setTheme(theme_selected);

    new_instance_name_textbox.setTheme(theme_selected);
    import_instance_name_textbox.setTheme(theme_selected);
    import_instance_path_textbox.setTheme(theme_selected);
    SlimeRancher_steam_path_textbox.setTheme(theme_selected);
    SlimeRancher_instances_path_textbox.setTheme(theme_selected);
    steamcmd_path_textbox.setTheme(theme_selected);
    SteamProfile_name_textbox.setTheme(theme_selected);

    SteamProfile_password_textbox.setTheme(theme_selected);

    versions_list.setTheme(theme_selected);
    theme_list_ddl.setTheme(theme_selected);
    downloaders_ddl.setTheme(theme_selected);

    separate_data_checkbox.setTheme(theme_selected);
    move_imported_instance_files_checkbox.setTheme(theme_selected);
    Show_older_instances_checkbox.setTheme(theme_selected);
    Show_moded_instances_checkbox.setTheme(theme_selected);
    autocheck_for_update_checkbox.setTheme(theme_selected);
    Save_logs_files_checkbox.setTheme(theme_selected);
    Colored_logs_checkbox.setTheme(theme_selected);
    automatically_run_downloaded_instances_checkbox.setTheme(theme_selected);
    do_not_show_warnings_checkbox.setTheme(theme_selected);

    last_played_bg.setTheme(theme_selected);
    categories_bg.setTheme(theme_selected);
    settings_bg.setTheme(theme_selected);
    instances_bg.setTheme(theme_selected);
    versions_bg.setTheme(theme_selected);
    manage_bg.setTheme(theme_selected);
    ver_desc_bg.setTheme(theme_selected);

    subcat_separator.setTheme(theme_selected);
    manage_cats_separator.setTheme(theme_selected);
    mods_separator.setTheme(theme_selected);
    
    Profile_warning_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    Mounted_instance_info_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    mounted_instance_version.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    Launcher_version_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    update_status_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    bbw_tittle_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    theme_label_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    credits_programming_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    dataLoading_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    downloading_progress_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    downloaders_list_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    version_description_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    steam_profile_offline_status_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    steam_profile_AccountName_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    steam_profile_PersonalName_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    steam_profile_UID_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    list_mods_instance_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    list_mods_launcher_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    MNG_Instance_name_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    MNG_installed_mods_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    MNG_Instance_saves_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    MNG_instance_mods_own_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    MNG_instance_mods_launcher_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);

    console.setTheme(theme_selected);
    console.applyTextColor(theme_selected);
    console_clear_button.setTheme(theme_selected);
}