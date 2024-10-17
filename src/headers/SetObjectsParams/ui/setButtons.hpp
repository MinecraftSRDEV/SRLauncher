void setButtons()
{
    launch_last_instance_button.create(465, 710, 350, 80, font, "Launch instance", false, theme_selected);
    last_played_bg.create(0, 700, 1280, 100, true, theme_selected);

    categories_bg.create(0, 0, 1280, 40, true, theme_selected);
    MainCategory_button.create(0, 0, 320, 35, font, "Main", false, theme_selected);
    InstancesCategory_button.create(320, 0, 320, 35, font, "Instances", false, theme_selected);
    SettingsCategory_button.create(640, 0, 320, 35, font, "Settings", false, theme_selected);
    VersionsCategory_button.create(960, 0, 320, 35, font, "Slime Rancher Versions", false, theme_selected);

    settings_bg.create(0, 40, 1280, 800, true, theme_selected);

    Subcat_settings_main_button.create(0, 45, 120, 40, font, "main", false, theme_selected);
    Subcat_settings_progile_button.create(0, 85, 120, 40, font, "profile", false, theme_selected);
    Subcat_settings_updates_button.create(0, 125, 120, 40, font, "updates", false, theme_selected);
    Subcat_settings_credits_button.create(0, 760, 120, 40, font, "credits", false, theme_selected);

    subcat_separator.create(125, 43, 0, 754, true, theme_selected);

    SlimeRancher_steam_path_textbox.create(130, 100, 1085, 40, false, false, font, 26, "", false, "Steam games directory path", theme_selected);
    SlimeRancher_steam_path_getfolder_button.create(1215, 131, 60, 40, font, "Browse", false, theme_selected);
    SlimeRancher_instances_path_textbox.create(130, 175, 1085, 40, false, false, font, 26, "", false, "Insrances location path", theme_selected);
    SlimeRancher_instances_path_getfolder_button.create(1215, 206, 60, 40, font, "Browse", false, theme_selected);
    steamcmd_path_textbox.create(130, 250, 1085, 40, false, false, font, 26, "", false, "SteamCMD location path", theme_selected);
    steamcmd_path_getfolder_button.create(1215, 281, 60, 40, font, "Browse", false, theme_selected);
    Show_older_instances_checkbox.create(30, 30, 130, 340, "Show pre-release game versions", 26, font, true, theme_selected);
    Save_logs_files_checkbox.create(30, 30, 130, 375, "Autosave log files", 26, font, true, theme_selected);
    Colored_logs_checkbox.create(30, 30, 130, 410, "Enable colored logs", 26, font, true, theme_selected);

    automatically_run_downloaded_instances_checkbox.create(30, 30, 130, 445, "Run downloaded instances automatically", 26, font, true, theme_selected);
    do_not_show_warnings_checkbox.create(30, 30, 130, 480, "Enable warning messages", 26, font, true, theme_selected);

    RestoreSettings_button.create(1000, 750, 120, 40, font, "Restore defaults", false, theme_selected);
    SaveConfig_button.create(1120, 750, 120, 40, font, "Save config", false, theme_selected);

    SteamProfile_name_textbox.create(130, 100, 400, 40, false, false, font, 26, "", false, "Steam profile name", theme_selected);
    SteamProfile_password_textbox.create(130, 175, 400, 40, false, false, font, 26, "", false, "Steam profile password", theme_selected);
    save_profile_button.create(1120, 750, 120, 40, font, "Save profile", false, theme_selected);

    instances_bg.create(0, 40, 1280, 800, true, theme_selected);

    new_instance_button.create(90, 45, 550, 35, font, "New instance", false, theme_selected);
    import_instnace_button.create(641, 45, 550, 35, font, "Import instance", false, theme_selected);
    
    versions_list.create(350, 40, 465, 140, {{"select version","none"}}, "select version", font);

    new_instance_name_textbox.create(465, 70, 350, 30, false, false, font, 26, "New instance", false, "Instance name", theme_selected);
    create_button.create(465, 220, 350, 35, font, "Create", false, theme_selected);
    instance_creation_cancel.create(465, 260, 350, 35, font, "Cancel", false, theme_selected);

    import_instance_name_textbox.create(465, 70, 350, 30, false, false, font, 26, "Imported instance", false, "Instance name", theme_selected);
    import_instance_path_textbox.create(100, 190, 1100, 30, false, false, font, 26, "", false, "Import source path", theme_selected);
    import_instance_path_browse_button.create(1150, 221, 60, 30, font, "Browse");
    import_instance_confirm_button.create(465, 300, 350, 35, font, "Confirm import");
    import_instance_cancel_button.create(465, 340, 350, 35, font, "Cancel");

    versions_bg.create(0, 40, 1280, 800, true, theme_selected);

    manage_vanilla_saves_button.create(0, 0, 120, 40, font, "Vanilla saves", false, theme_selected);
    manage_mod_saves_button.create(0, 40, 120, 40, font, "Mods saves", false, theme_selected);
    manage_betterbuild_world_button.create(0, 80, 120, 40, font, "BetterBuild worlds", false, theme_selected);
    manage_backups_button.create(0, 120, 120, 40, font, "Backups manager", false, theme_selected);
    manage_mods_button.create(0, 160, 120, 40, font, "Mods", false, theme_selected);
    manage_main_back_button.create(0, 760, 120, 40, font, "Back", false, theme_selected);
    
    manage_cats_separator.create(125, 3, 0, 794, true, theme_selected);

    mods_separator.create(130 + 560 + 5, 3, 0, 794, true, theme_selected);

    manage_bg.create(0, 0, 1280, 800, true, theme_selected);

    ver_desc_bg.create(0, 0, 1280, 800, true, theme_selected);
    version_back_button.create(465, 750, 350, 40, font, "Back", false, theme_selected);

    check_for_update_button.create(130, 100, 120, 40, font, "Check for update", false, theme_selected);
    autocheck_for_update_checkbox.create(30, 30, 130, 150, "Check for update when launcher started", 26, font, true, theme_selected);

    theme_list_ddl.create(120, 40, 130, 560, {{{"Bright"},{std::to_string(ColorPalete::Bright)}},{{"Dark"},{std::to_string(ColorPalete::Dark)}},{{"High contrast"},{std::to_string(ColorPalete::HighContrast)}}}, "Bright", font, false);
    downloaders_ddl.create(200, 40, 680, 560, {{{"DepotDownloader (recomended)"},{std::to_string(depotdownloader)}},{{"SteamCMD (slower)"},{std::to_string(steamcmd)}}}, "DepotDownloader (recomended)", font, false);

    console_clear_button.create(1160, 651, 100, 30, font, "Clear console", false, theme_selected);
    console.create(20, 50, 1240, 600, font, theme_selected);

    GuardBox.create(420, 240, font, theme_selected);
}