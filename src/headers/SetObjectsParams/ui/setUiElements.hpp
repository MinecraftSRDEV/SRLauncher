void setButtons()
{
    UIElements.createButton(launch_game_button, 465, 710, 350, 80, font, PLAY_BUTTON_DEF, true);
    UIElements.createTransparrentBg(MainpageElements::main_page_playbar_bg, 0, 700, 1280, 100, true);
    UIElements.createTransparrentBg(MainpageElements::main_page_last_played_bg, 20, 45, 680, 400, false);
    UIElements.createTransparrentBg(MainpageElements::main_page_details_bg, 710, 45, 550, 400, false);

    UIElements.createCheckbox(DebuggerMainmenuLayout::acceptInfoCheckbox, 30, 30, 130, 85, "Info", 12, font, false);

    UIElements.createTransparrentBg(categories_bg, 0, 0, 1280, 40, true);
    UIElements.createButton(MainCategory_button, -2, 0, 320, 35, font, "Main", true);
    UIElements.createButton(InstancesCategory_button, (0 + 320), 0, 320, 35, font, "Instances", true);
    UIElements.createButton(SettingsCategory_button, (0 + 320 + 2 + 320), 0, 320, 35, font, "Settings", true);
    UIElements.createButton(VersionsCategory_button, (0 + 320 + 2 + 320 + 2 + 320), 0, 320, 35, font, "Slime Rancher Versions", true);

    UIElements.createTransparrentBg(settings_bg, 0, 40, 1280, 800, true);

    UIElements.createButton(settingsGeneralCat_button, 0, 45, 120, 40, font, "General", false);
    UIElements.createButton(settingsProfileCat_button, 0, 87, 120, 40, font, "Steam profile", false);
    UIElements.createButton(settingsDownloadingCat_button, 0, 129, 120, 40, font, "Downloading", false);
    UIElements.createButton(settingsUpdatesCat_button, 0, 171, 120, 40, font, "Launcher updates", false);
    UIElements.createButton(settingsDebuggingCat_button, 0, 213, 120, 40, font, "Debug options", false);
    UIElements.createButton(settingsLicencesCat_button, 0, 718, 120, 40, font, "Licenses", false);
    UIElements.createButton(settingsCreditsCat_button, 0, 760, 120, 40, font, "Credits", false);

    UIElements.createTransparrentBg(subcat_separator, 125, 43, 0, 754, true);
    UIElements.createTransparrentBg(save_config_separator, 125, 745, 1280, 0, true);

    UIElements.createTextbox(steam_path_textbox, 130, 100, 1085, 40, false, false, font, 26, "", false, "Steam games directory path");
    UIElements.createButton(steam_path_getfolder_button, 1215, 131, 60, 40, font, "Browse", false);
    UIElements.createTextbox(instances_path_textbox, 130, 175, 1085, 40, false, false, font, 26, "", false, "Insrances location path");
    UIElements.createButton(instances_path_getfolder_button, 1215, 206, 60, 40, font, "Browse", false);
    UIElements.createCheckbox(Show_prereleases_checkbox, 30, 30, 130, 270, "Show pre-release game versions", 26, font, true);
    UIElements.createCheckbox(Save_logs_files_checkbox, 30, 30, 130, 305, "Autosave log files", 26, font, true);
    UIElements.createCheckbox(Colored_logs_checkbox, 30, 30, 130, 340, "Enable colored logs", 26, font, true);
    UIElements.createCheckbox(do_not_show_warnings_checkbox, 30, 30, 130, 375, "Enable warning messages", 26, font, true);
    UIElements.createCheckbox(use_secure_ipc_checkbox, 30, 30, 130, 410, "Use secure IPC (experimental)", 26, font, false);
    UIElements.createCheckbox(mount_only_data_checkbox, 30, 30, 130, 445, "Mount only game data (W.I.P.)", 26, font, false);
    UIElements.createTextbox(SRL_background_img_path_textbox, 130, 510, 1085, 40, false, false, font, 26, "", false, "SRL background image path");
    UIElements.createButton(SRL_background_img_path_getfolder_button, 1215, 541, 60, 40, font, "Browse", false);
    UIElements.createDropDownList(theme_list_ddl, 120, 40, 130, 640, {{{"Bright"},{std::to_string(ColorPalete::Bright)}},{{"Dark"},{std::to_string(ColorPalete::Dark)}},{{"High contrast"},{std::to_string(ColorPalete::HighContrast)}}}, "Bright", font, false);

    UIElements.createButton(RestoreSettings_button, 1000, 750, 120, 40, font, "Restore defaults", false);
    UIElements.createButton(SaveConfig_button, 1122, 750, 120, 40, font, "Save config", false);

    UIElements.createTextbox(SteamProfile_name_textbox, 130, 100, 400, 40, false, false, font, 26, "", false, "Steam profile name");
    UIElements.createPasswordbox(SteamProfile_password_textbox, 130, 175, 400, 40, false, false, font, 26, "", false, "Steam profile password");
    UIElements.createButton(save_profile_button, 1122, 750, 120, 40, font, "Save profile", false);

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
    UIElements.createButton(DebugSettingsUI::enableDebuggingOnInstance, 130, 480 + 150, 240, 40, font, "Apply debuger patch to current instance", false);

    UIElements.createTransparrentBg(instances_bg, 0, 40, 1280, 800, true);

    UIElements.createButton(new_instance_button, 90, 45, 550, 35, font, "New instance", false);
    UIElements.createButton(import_instnace_button, 642, 45, 550, 35, font, "Import instance", false);
    
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

    UIElements.createButton(ManageSubcatListUI::informations_button, 0, 0, 120, 40, font, "Details", false);
    UIElements.createButton(ManageSubcatListUI::vanilla_saves_button, 0, (0 + 42), 120, 40, font, "Vanilla saves", false);
    UIElements.createButton(ManageSubcatListUI::betterbuild_saves_button, 0, (0 + 42 + 42), 120, 40, font, "Mods saves", false);
    UIElements.createButton(ManageSubcatListUI::betterbuild_world_button, 0, (0 + 42 + 42 + 42), 120, 40, font, "BetterBuild worlds", false);
    UIElements.createButton(ManageSubcatListUI::backups_button, 0, (0 + 42 + 42 + 42 + 42), 120, 40, font, "Backups manager", false);
    UIElements.createButton(ManageSubcatListUI::mods_button, 0, (0 + 42 + 42 + 42 + 42 + 42), 120, 40, font, "Mods", false);
    UIElements.createButton(ManageSubcatListUI::debug_button, 0, (0 + 42 + 42 + 42 + 42 + 42 + 42), 120, 40, font, "Debug", false);
    UIElements.createButton(ManageSubcatListUI::main_back_button, 0, 760, 120, 40, font, "Back", false);

    UIElements.createTransparrentBg(ManageDebug::assemblyInfoBg, 830, 0, 450, 800, true);

    UIElements.createTransparrentBg(ManageSubcatListUI::cats_separator, 125, 3, 0, 794, true);

    UIElements.createButton(BBGamesavesSlots::A, 130, 400, 120, 120, font, "Slot A", false);
    UIElements.createButton(BBGamesavesSlots::B, 260, 400, 120, 120, font, "Slot B", false);
    UIElements.createButton(BBGamesavesSlots::C, 380, 400, 120, 120, font, "Slot C", false);

    UIElements.createMenagementButton(MNG_Instance_saves_text, 135, 70, font, instance_icons_textures["pink_slime"], "", false);
    UIElements.createMenagementButton(MNG_instance_installed_mods_text, 135, (70 + 91), font, instance_icons_textures["pink_slime"], "", false);
    UIElements.createMenagementButton(MNG_instance_mods_saves_text, 135, (70 + (91 + 91)), font, instance_icons_textures["pink_slime"], "", false);
    UIElements.createMenagementButton(MNG_instance_mods_launcher_text, 135, (70 + (91 + (91 + 91))), font, instance_icons_textures["pink_slime"], "", false);
    
    UIElements.createTransparrentBg(mods_separator, 130 + 560 + 5, 3, 0, 794, true);

    UIElements.createTransparrentBg(manage_bg, 0, 0, 1280, 800, true);

    UIElements.createTransparrentBg(ver_desc_bg, 0, 0, 1280, 800, true);
    UIElements.createButton(version_back_button, 465, 750, 350, 40, font, "Back", false);

    UIElements.createButton(check_for_update_button, 130, 100, 120, 40, font, "Check for updates", false);
    UIElements.createCheckbox(autocheck_for_update_checkbox, 30, 30, 130, 150, "Check for update when launcher started", 26, font, true);

    UIElements.createButton(ConsoleElements::console_clear_button, 1160, 450, 100, 30, font, "Clear console", false);
    UIElements.createCheckbox(ConsoleElements::disable, 30, 30, 10, 700, "Disable console", 26, font, false);
    UIElements.createTextfield(ConsoleElements::console, 20, 450, 1240, 240, font);

    UIElements.createTextfield(LicencesUI::licenseField, 130, 60, 1140, 720, font);

    GuardBox.create(420, 240, font);
}