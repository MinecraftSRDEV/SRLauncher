void setButtons()
{
    launch_last_instance_button.create(465, 710, 350, 80, font, "Launch mounted instance");
    last_played_bg.create(0, 700, 1280, 100, true);

    categories_bg.create(0, 0, 1280, 40, true);
    MainCategory_button.create(0, 0, 320, 35, font, "Main");
    InstancesCategory_button.create(320, 0, 320, 35, font, "Instances");
    SettingsCategory_button.create(640, 0, 320, 35, font, "Settings");
    SavesToolCategory_button.create(960, 0, 320, 35, font, "Data tool");

    settings_bg.create(0, 40, 1280, 800, true);

    Subcat_settings_main_button.create(0, 45, 120, 40, font, "main");
    Subcat_settings_progile_button.create(0, 85, 120, 40, font, "profile");
    Subcat_settings_versions_button.create(0, 720, 120, 40, font, "versions");
    Subcat_settings_credits_button.create(0, 760, 120, 40, font, "credits");

    SlimeRancher_steam_path_textbox.create(130, 100, 1000, 40, false, false, font, 26, "", false, "Steam games directory path");
    SlimeRancher_steam_path_getfolder_button.create(1130, 131, 60, 40, font, "Browse");
    SlimeRancher_instances_path_textbox.create(130, 175, 1000, 40, false, false, font, 26, "", false, "Insrances location path");
    SlimeRancher_instances_path_getfolder_button.create(1130, 206, 60, 40, font, "Browse");
    steamcmd_path_textbox.create(130, 250, 1000, 40, false, false, font, 26, "", false, "SteamCMD location path");
    steamcmd_path_getfolder_button.create(1130, 281, 60, 40, font, "Browse");
    Show_older_instances_checkbox.create(30, 30, 130, 340, "Show pre-release game versions", 26, font, true);
    Save_logs_files_checkbox.create(30, 30, 130, 375, "Autosave log files", 26, font, true);
    Colored_logs_checkbox.create(30, 30, 130, 410, "Enable colored logs", 26, font, true);

    automatically_run_downloaded_instances_checkbox.create(30, 30, 130, 445, "Run downloaded instances automatically", 26, font, true);
    do_not_show_warnings_checkbox.create(30, 30, 130, 480, "Enable warning messages", 26, font, true);

    RestoreSettings_button.create(1000, 750, 120, 40, font, "Restore defaults");
    SaveConfig_button.create(1120, 750, 120, 40, font, "Save config");

    SteamProfile_name_textbox.create(130, 100, 1130, 40, false, false, font, 26, "", false, "Steam profile name");
    // SteamProfile_password_textbox.create(130, 175, 1130, 40, false, false, font, 26, "", false, "Steam profile password");
    save_profile_button.create(1000, 750, 120, 40, font, "Save profile");
    login_manualy_checkbox.create(30, 30, 130, 275, "Login to SteamCMD manualy", 26, font, false);

    instances_bg.create(0, 40, 1280, 800, true);

    new_instance_button.create(90, 45, 550, 35, font, "New instance");
    import_instnace_button.create(641, 45, 550, 35, font, "Import instance");
    
    versions_list.create(350, 40, 465, 140, {{"select version","none"}}, "select version", font);

    new_instance_name_textbox.create(465, 70, 350, 30, false, false, font, 26, "New instance", false, "Instance name");
    create_button.create(465, 220, 350, 35, font, "Create");
    instance_creation_cancel.create(465, 260, 350, 35, font, "Cancel");

    import_instance_name_textbox.create(465, 70, 350, 30, false, false, font, 26, "Imported instance", false, "Instance name");
    import_instance_path_textbox.create(100, 190, 1100, 30, false, false, font, 26, "", false, "Import source path");
    import_instance_path_browse_button.create(1150, 221, 60, 30, font, "Browse");
    import_instance_confirm_button.create(465, 300, 350, 35, font, "Confirm import");
    import_instance_cancel_button.create(465, 340, 350, 35, font, "Cancel");

    datatools_bg.create(0, 40, 1280, 800, true);
}