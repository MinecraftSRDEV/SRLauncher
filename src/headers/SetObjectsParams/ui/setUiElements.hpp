void setButtons()
{
    UIElements.createButton(launch_game_button, 465, 710, 350, 80, font, PLAY_BUTTON_DEF, true);
    UIElements.createTransparrentBg(main_page_playbar_bg, 0, 700, 1280, 100, true);

    UIElements.createCheckbox(DebuggerMainmenuLayout::acceptInfoCheckbox, 30, 30, 130, 85, "Info", 12, font, false);

    UIElements.createTransparrentBg(categories_bg, 0, 0, 1280, 40, true);
    UIElements.createButton(MainCategory_button, -2, 0, 320, 35, font, "Main", true);
    UIElements.createButton(InstancesCategory_button, 320, 0, 320, 35, font, "Instances", true);
    UIElements.createButton(SettingsCategory_button, 642, 0, 320, 35, font, "Settings", true);
    UIElements.createButton(VersionsCategory_button, 964, 0, 320, 35, font, "Slime Rancher Versions", true);

    UIElements.createTransparrentBg(settings_bg, 0, 40, 1280, 800, true);

    UIElements.createButton(Subcat_settings_main_button, 0, 45, 120, 40, font, "Main", false);
    UIElements.createButton(Subcat_settings_progile_button, 0, 85, 120, 40, font, "Profile", false);
    UIElements.createButton(Subcat_settings_downloading_button, 0, 125, 120, 40, font, "Downloading", false);
    UIElements.createButton(Subcat_settings_updates_button, 0, 165, 120, 40, font, "Updates", false);
    UIElements.createButton(Subcat_settings_debugging_button, 0, 205, 120, 40, font, "Debug options", false);
    UIElements.createButton(Subcat_settings_licences_button, 0, 720, 120, 40, font, "Licenses", false);
    UIElements.createButton(Subcat_settings_credits_button, 0, 760, 120, 40, font, "Credits", false);

    UIElements.createTransparrentBg(subcat_separator, 125, 43, 0, 754, true);

    UIElements.createTextbox(SlimeRancher_steam_path_textbox, 130, 100, 1085, 40, false, false, font, 26, "", false, "Steam games directory path");
    UIElements.createButton(SlimeRancher_steam_path_getfolder_button, 1215, 131, 60, 40, font, "Browse", false);
    UIElements.createTextbox(SlimeRancher_instances_path_textbox, 130, 175, 1085, 40, false, false, font, 26, "", false, "Insrances location path");
    UIElements.createButton(SlimeRancher_instances_path_getfolder_button, 1215, 206, 60, 40, font, "Browse", false);
    UIElements.createCheckbox(Show_prereleases_checkbox, 30, 30, 130, 270, "Show pre-release game versions", 26, font, true);
    UIElements.createCheckbox(Save_logs_files_checkbox, 30, 30, 130, 305, "Autosave log files", 26, font, true);
    UIElements.createCheckbox(Colored_logs_checkbox, 30, 30, 130, 340, "Enable colored logs", 26, font, true);
    UIElements.createCheckbox(do_not_show_warnings_checkbox, 30, 30, 130, 375, "Enable warning messages", 26, font, true);
    UIElements.createCheckbox(use_secure_ipc_checkbox, 30, 30, 130, 410, "Use secure IPC (experimental)", 26, font, false);
    UIElements.createCheckbox(mount_only_data_checkbox, 30, 30, 130, 445, "Mount only game data", 26, font, false);
    UIElements.createDropDownList(theme_list_ddl, 120, 40, 130, 545, {{{"Bright"},{std::to_string(ColorPalete::Bright)}},{{"Dark"},{std::to_string(ColorPalete::Dark)}},{{"High contrast"},{std::to_string(ColorPalete::HighContrast)}}}, "Bright", font, false);

    UIElements.createButton(RestoreSettings_button, 1000, 750, 120, 40, font, "Restore defaults", false);
    UIElements.createButton(SaveConfig_button, 1120, 750, 120, 40, font, "Save config", false);

    UIElements.createTextbox(SteamProfile_name_textbox, 130, 100, 400, 40, false, false, font, 26, "", false, "Steam profile name");
    UIElements.createPasswordbox(SteamProfile_password_textbox, 130, 175, 400, 40, false, false, font, 26, "", false, "Steam profile password");
    UIElements.createButton(save_profile_button, 1120, 750, 120, 40, font, "Save profile", false);

    UIElements.createTextbox(steamcmd_path_textbox, 130, 200, 1085, 40, false, false, font, 26, "", false, settmaindi::CMDPATH_TEXT);
    UIElements.createButton(steamcmd_path_getfolder_button, 1215, 231, 60, 40, font, "Browse", false);
    UIElements.createCheckbox(automatically_run_downloaded_instances_checkbox, 30, 30, 130, 280, "Run downloaded instances automatically", 26, font, true);
    UIElements.createDropDownList(downloaders_ddl, 350, 40, 130, 75, {{{"DepotDownloader (recomended)"},{std::to_string(depotdownloader)}},{{"Legacy SteamCMD (slower)"},{std::to_string(steamcmd)}}}, "DepotDownloader (recomended)", font, false);

    UIElements.createCheckbox(DebugSettingsUI::debuggingEnabledCheckbox, 30, 30, 130, 85, "Enable debugging", 26, font, false);
    UIElements.createCheckbox(DebugSettingsUI::saveDebugLogsToOtherFileCheckbox, 30, 30, 130, 135, "Save logs to other file", 26, font, false);
    UIElements.createCheckbox(DebugSettingsUI::printDebugLogsCheckbox, 30, 30, 130, 175, "Print debug logs", 26, font, false);
    UIElements.createCheckbox(DebugSettingsUI::acceptInfoCheckbox, 30, 30, 180, 205, "Info", 26, font, false);
    UIElements.createCheckbox(DebugSettingsUI::acceptWarningCheckbox, 30, 30, 180, 245, "Warning", 26, font, false);
    UIElements.createCheckbox(DebugSettingsUI::acceptErrorCheckbox, 30, 30, 180, 285, "Error", 26, font, false);
    UIElements.createCheckbox(DebugSettingsUI::acceptExceptionCheckbox, 30, 30, 180, 325, "Exception", 26, font, false);
    UIElements.createTextbox(DebugSettingsUI::comunicationDelayTextbox, 130, 375, 400, 40, false, false, font, 26, "", false, "Pipe check delay (MS)");
    UIElements.createTextbox(DebugSettingsUI::comunicationPipeBufferSizeTextbox, 130, 375 + 80, 400, 40, false, false, font, 26, "", false, "Pipe buffer size (bytes)");
    UIElements.createButton(DebugSettingsUI::forcePipeCloseButton, 130, 440 + 105, 100, 40, font, "Force Pipe close", false);
    UIElements.createButton(DebugSettingsUI::killInstanceButton, 232, 440 + 105, 100, 40, font, "Kill instance", false);
    UIElements.createButton(DebugSettingsUI::saveLogFileButton, 334, 440 + 105, 100, 40, font, "Save log file", false);

    UIElements.createTransparrentBg(instances_bg, 0, 40, 1280, 800, true);

    UIElements.createButton(new_instance_button, 90, 45, 550, 35, font, "New instance", false);
    UIElements.createButton(import_instnace_button, 641, 45, 550, 35, font, "Import instance", false);
    
    UIElements.createDropDownList(versions_list_ddl, 350, 40, 620, 60, {{"select version","none"}}, "select version", font);

    UIElements.createTransparrentBg(CreateInstanceUI::instance_creation_bg, 0, 0, 1000, 740, true);
    UIElements.createTransparrentBg(CreateInstanceUI::instance_creation_info1_bg, 0, 740, 1280, 60, true);
    UIElements.createTransparrentBg(CreateInstanceUI::instance_creation_info2_bg, 1000, 0, 280, 740, true);
    UIElements.createTextbox(CreateInstanceUI::new_instance_name_textbox, 10, 20, 570, 40, false, false, font, 35, "New instance", false, "Instance name");
    UIElements.createButton(CreateInstanceUI::create_button, 640, 695, 350, 35, font, "Create", false);
    UIElements.createButton(CreateInstanceUI::instance_creation_cancel, 280, 695, 350, 35, font, "Cancel", false);
    UIElements.createCheckbox(CreateInstanceUI::automount_checkbox, 30, 30, 10, 140, "Auto mount (if possible)", 26, font, false);
    UIElements.createCheckbox(CreateInstanceUI::create_with_graphics_preset_checkbox, 30, 30, 10, 180, "Create with graphics preset", 26, font, false);
    UIElements.createDropDownList(CreateInstanceUI::graphics_preset_ddl, 270, 40, 10, 220, {{"No preset","none"},{"Lowest","lowest"},{"Low","low"},{"Default","default"},{"Medium","medium"},{"High","high"},{"Higest","higest"}}, "No preset", font);

    UIElements.createButton(InstanceIconBar::next_button, 930, 330, 40, 80, font, ">", false);
    UIElements.createButton(InstanceIconBar::prev_button, 10, 330, 40, 80, font, "<", false);

    UIElements.createButton(saveEditedButton, 640, 695, 350, 35, font, "Save", false);

    UIElements.createTextbox(import_instance_name_textbox, 10, 20, 570, 40, false, false, font, 35, "Imported instance", false, "Instance name");
    UIElements.createTextbox(import_instance_path_textbox, 10, 740, 1200, 30, false, false, font, 26, "", false, "Import source path");
    UIElements.createButton(import_instance_path_browse_button, 1210, 771, 60, 30, font, "Browse");
    UIElements.createButton(import_instance_confirm_button, 640, 695, 350, 35, font, "Confirm import");
    UIElements.createButton(import_instance_cancel_button, 280, 695, 350, 35, font, "Cancel");

    UIElements.createTransparrentBg(versions_bg, 0, 40, 1280, 800, true);

    UIElements.createButton(manage_vanilla_saves_button, 0, 0, 120, 40, font, "Vanilla saves", false);
    UIElements.createButton(manage_betterbuild_saves_button, 0, 40, 120, 40, font, "Mods saves", false);
    UIElements.createButton(manage_betterbuild_world_button, 0, 80, 120, 40, font, "BetterBuild worlds", false);
    UIElements.createButton(manage_backups_button, 0, 120, 120, 40, font, "Backups manager", false);
    UIElements.createButton(manage_mods_button, 0, 160, 120, 40, font, "Mods", false);
    UIElements.createButton(manage_main_back_button, 0, 760, 120, 40, font, "Back", false);
    
    UIElements.createTransparrentBg(manage_cats_separator, 125, 3, 0, 794, true);

    UIElements.createTransparrentBg(mods_separator, 130 + 560 + 5, 3, 0, 794, true);

    UIElements.createTransparrentBg(manage_bg, 0, 0, 1280, 800, true);

    UIElements.createTransparrentBg(ver_desc_bg, 0, 0, 1280, 800, true);
    UIElements.createButton(version_back_button, 465, 750, 350, 40, font, "Back", false);

    UIElements.createButton(check_for_update_button, 130, 100, 120, 40, font, "Check for update", false);
    UIElements.createCheckbox(autocheck_for_update_checkbox, 30, 30, 130, 150, "Check for update when launcher started", 26, font, true);

    UIElements.createButton(console_clear_button, 1160, 651, 100, 30, font, "Clear console", false);
    UIElements.createTextfield(console, 20, 50, 1240, 600, font);

    UIElements.createTextfield(LicencesUI::licenseField, 130, 60, 1140, 720, font);

    GuardBox.create(420, 240, font);
}