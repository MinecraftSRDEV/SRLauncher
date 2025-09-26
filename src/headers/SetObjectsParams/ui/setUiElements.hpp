void setButtons()
{
    {
        using namespace MainpageElements;

        MainpageElements::GuardBox.create(420, 240, font);

        UIElements.createButton(playbar::launchGameButton, 465, 710, 350, 80, font, PLAY_BUTTON_DEF, true);
        UIElements.createTransparrentBg(playbar::background, 0, 700, 1280, 100, true);

        UIElements.createTransparrentBg(lastPlayed::background, 20, 45, 680, 400, false);
        UIElements.createTransparrentBg(details::background, 710, 45, 550, 400, false);    

        UIElements.createButton(console::clearButton, 1160, 450, 100, 30, font, "IDS_BUTTON_CLEARCONSOLE", false);
        UIElements.createCheckbox(console::disableCheckbox, 30, 30, 10, 700, "IDS_BUTTON_DISABLECONSOLE", 26, font, false);
        
        UIElements.createTextfield(console::console, 20, 450, 1240, 210, font);    
    }
    
    UIElements.createCheckbox(DebuggerMainmenuLayout::acceptInfoCheckbox, 30, 30, 130, 85, "Info", 12, font, false);

    UIElements.createTransparrentBg(categories_bg, 0, 0, 1280, 40, true);
    UIElements.createButton(MainCategory_button, -2, 0, 320, 35, font, "IDS_BUTTON_MAINCATEGORY", true);
    UIElements.createButton(InstancesCategory_button, (0 + 320), 0, 320, 35, font, "IDS_BUTTON_INSTANCESCATEGORY", true);
    UIElements.createButton(SettingsCategory_button, (0 + 320 + 2 + 320), 0, 320, 35, font, "IDS_BUTTON_SETTINGSCATEGORY", true);
    UIElements.createButton(VersionsCategory_button, (0 + 320 + 2 + 320 + 2 + 320), 0, 320, 35, font, "IDS_BUTTON_SRVERSIONSCATEGORY", true);

    UIElements.createTransparrentBg(SettingsElemets::settings_bg, 0, 40, 1280, 800, true);

    UIElements.createButton(SettingsElemets::subcatsBar::generalCat_button, 0, 45, 120, 40, font, "IDS_BUTTON_SETTINGS_GENERAL", false);
    UIElements.createButton(SettingsElemets::subcatsBar::profileCat_button, 0, 87, 120, 40, font, "IDS_BUTTON_SETTINGS_STEAMPROFILE", false);
    UIElements.createButton(SettingsElemets::subcatsBar::downloadingCat_button, 0, 129, 120, 40, font, "IDS_BUTTON_SETTINGS_DOWNLOADING", false);
    UIElements.createButton(SettingsElemets::subcatsBar::updatesCat_button, 0, 171, 120, 40, font, "IDS_BUTTON_SETTINGS_UPDATES", false);
    UIElements.createButton(SettingsElemets::subcatsBar::debuggingCat_button, 0, 213, 120, 40, font, "IDS_BUTTON_SETTINGS_DEBUG", false);
    UIElements.createButton(SettingsElemets::subcatsBar::licencesCat_button, 0, 718, 120, 40, font, "IDS_BUTTON_SETTINGS_LICENSES", false);
    UIElements.createButton(SettingsElemets::subcatsBar::creditsCat_button, 0, 760, 120, 40, font, "IDS_BUTTON_SETTINGS_CREDITS", false);

    UIElements.createTransparrentBg(SettingsElemets::subcatsBar::subcat_separator, 125, 43, 0, 754, true);
    UIElements.createTransparrentBg(SettingsElemets::bottomBar::save_config_separator, 125, 745, 1280, 0, true);

    UIElements.createTextbox(SettingsElemets::subcats::general::steam_path_textbox, 130, 100, 1085, 40, false, false, font, 26, "", false, "IDS_TXTBOX_SETTINGS_GAMEDIR");
    UIElements.createButton(SettingsElemets::subcats::general::steam_path_getfolder_button, 1215, 131, 60, 40, font, "IDS_BUTTON_SETTINGS_BROWSE", false);
    UIElements.createTextbox(SettingsElemets::subcats::general::instances_path_textbox, 130, 175, 1085, 40, false, false, font, 26, "", false, "IDS_TXTBOX_SETTINGS_INSTDIR");
    UIElements.createButton(SettingsElemets::subcats::general::instances_path_getfolder_button, 1215, 206, 60, 40, font, "IDS_BUTTON_SETTINGS_BROWSE", false);
    UIElements.createCheckbox(SettingsElemets::subcats::general::Show_prereleases_checkbox, 30, 30, 130, 270, "IDS_CHKBOX_SETTINGS_SWEARLYACCESS", 26, font, true);
    UIElements.createCheckbox(SettingsElemets::subcats::general::Save_logs_files_checkbox, 30, 30, 130, 305, "IDS_CHKBOX_SETTINGS_AUTOSAVELOGS", 26, font, true);
    UIElements.createCheckbox(SettingsElemets::subcats::general::Colored_logs_checkbox, 30, 30, 130, 340, "IDS_CHKBOX_SETTINGS_COLOREDLOGS", 26, font, true);
    UIElements.createCheckbox(SettingsElemets::subcats::general::do_not_show_warnings_checkbox, 30, 30, 130, 375, "IDS_CHKBOX_SETTINGS_ENABLEWARNS", 26, font, true);
    UIElements.createCheckbox(SettingsElemets::subcats::general::use_secure_ipc_checkbox, 30, 30, 130, 410, "IDS_CHKBOX_SETTINGS_USESECUREIPC", 26, font, false);
    UIElements.createCheckbox(SettingsElemets::subcats::general::mount_only_data_checkbox, 30, 30, 130, 445, "IDS_CHKBOX_SETTINGS_MOUNTONLYDATA", 26, font, false);
    UIElements.createTextbox(SettingsElemets::subcats::general::SRL_background_img_path_textbox, 130, 510, 1085, 40, false, false, font, 26, "", false, "IDS_TXTBOX_SETTINGS_SRLBGPATH");
    UIElements.createButton(SettingsElemets::subcats::general::SRL_background_img_path_getfolder_button, 1215, 541, 60, 40, font, "IDS_BUTTON_SETTINGS_BROWSE", false);
    UIElements.createDropDownList(SettingsElemets::subcats::general::theme_list_ddl, 120, 40, 130, 640, {{{"Bright"},{std::to_string(ColorPalete::Bright)}},{{"Dark"},{std::to_string(ColorPalete::Dark)}},{{"High contrast"},{std::to_string(ColorPalete::HighContrast)}}}, "Bright", font, false);
    UIElements.createDropDownList(SettingsElemets::subcats::general::languages_list_ddl, 120, 40, 340, 640, {{{"English"},{"en"}}}, "English", font, false);

    UIElements.createButton(SettingsElemets::bottomBar::RestoreSettings_button, 1000, 750, 120, 40, font, "IDS_BUTTON_SETTINGS_DEFAULTS", false);
    UIElements.createButton(SettingsElemets::bottomBar::SaveConfig_button, 1122, 750, 120, 40, font, "IDS_BUTTON_SETTINGS_SAVECONFIG", false);

    UIElements.createTextbox(SettingsElemets::subcats::steamAccount::profileName_textbox, 130, 100, 400, 40, false, false, font, 26, "", false, "IDS_TXTBOX_SETTINGS_STEAMPROFILENAME");
    UIElements.createPasswordbox(SettingsElemets::subcats::steamAccount::profilePassword_textbox, 130, 175, 400, 40, false, false, font, 26, "", false, "IDS_TXTBOX_SETTINGS_STEAMPROFILEPASSWORD");
    UIElements.createButton(SettingsElemets::subcats::steamAccount::save_profile_button, 1122, 750, 120, 40, font, "IDS_BUTTON_SETTINGS_SAVESTEAMPROFILE", false);

    UIElements.createTextbox(SettingsElemets::subcats::downloading::steamcmd_path_textbox, 130, 200, 1085, 40, false, false, font, 26, "", false, settmaindi::CMDPATH_TEXT);
    UIElements.createButton(SettingsElemets::subcats::downloading::steamcmd_path_getfolder_button, 1215, 231, 60, 40, font, "IDS_BUTTON_SETTINGS_BROWSE", false);
    UIElements.createCheckbox(SettingsElemets::subcats::downloading::automatically_run_downloaded_instances_checkbox, 30, 30, 130, 280, "IDS_CHKBOX_SETTINGS_DOWNLOADEDAUTORUN", 26, font, true);
    UIElements.createDropDownList(SettingsElemets::subcats::downloading::downloaders_ddl, 350, 40, 130, 75, {{{"DepotDownloader (recomended)"},{std::to_string(depotdownloader)}},{{"Legacy SteamCMD (slower)"},{std::to_string(steamcmd)}}}, "DepotDownloader (recomended)", font, false);

    UIElements.createCheckbox(SettingsElemets::subcats::debug::debuggingEnabledCheckbox, 30, 30, 130, 85, "Enable debugging", 26, font, false);
    UIElements.createCheckbox(SettingsElemets::subcats::debug::saveDebugLogsToOtherFileCheckbox, 30, 30, 130, 135, "Save logs to other file", 26, font, false);
    UIElements.createCheckbox(SettingsElemets::subcats::debug::printDebugLogsCheckbox, 30, 30, 130, 175, "Print debug logs", 26, font, false);
    UIElements.createCheckbox(SettingsElemets::subcats::debug::acceptInfoCheckbox, 30, 30, 180, 205, "Info", 26, font, false);
    UIElements.createCheckbox(SettingsElemets::subcats::debug::acceptWarningCheckbox, 30, 30, 180, 245, "Warning", 26, font, false);
    UIElements.createCheckbox(SettingsElemets::subcats::debug::acceptErrorCheckbox, 30, 30, 180, 285, "Error", 26, font, false);
    UIElements.createCheckbox(SettingsElemets::subcats::debug::acceptExceptionCheckbox, 30, 30, 180, 325, "Exception", 26, font, false);
    UIElements.createTextbox(SettingsElemets::subcats::debug::comunicationDelayTextbox, 130, 375, 400, 40, false, false, font, 26, "", false, "Pipe check delay (MS)");
    UIElements.createTextbox(SettingsElemets::subcats::debug::comunicationPipeBufferSizeTextbox, 130, 375 + 80, 400, 40, false, false, font, 26, "", false, "Pipe buffer size (bytes)");
    UIElements.createButton(SettingsElemets::subcats::debug::forcePipeCloseButton, 130, 440 + 105, 100, 40, font, "Force Pipe close", false);
    UIElements.createButton(SettingsElemets::subcats::debug::killInstanceButton, 232, 440 + 105, 100, 40, font, "Kill instance", false);
    UIElements.createButton(SettingsElemets::subcats::debug::saveLogFileButton, 334, 440 + 105, 100, 40, font, "Save log file", false);

    UIElements.createTransparrentBg(instances_bg, 0, 40, 1280, 800, true);

    UIElements.createButton(new_instance_button, 90, 45, 550, 35, font, "IDS_BUTTON_INSTANCESLIST_NEW", false);
    UIElements.createButton(import_instnace_button, 642, 45, 550, 35, font, "IDS_BUTTON_INSTANCESLIST_IMPORT", false);
    
    UIElements.createDropDownList(versions_list_ddl, 350, 40, 620, 60, {{"select version","none"}}, "select version", font);

    UIElements.createTransparrentBg(CreateInstanceUI::instance_creation_bg, 0, 0, 1000, 740, true);
    UIElements.createTransparrentBg(CreateInstanceUI::instance_creation_info1_bg, 0, 740, 1280, 60, true);
    UIElements.createTransparrentBg(CreateInstanceUI::instance_creation_info2_bg, 1000, 0, 280, 740, true);
    UIElements.createTextbox(CreateInstanceUI::new_instance_name_textbox, 10, 20, 570, 40, false, false, font, 35, "IDS_TEXT_NEWINSTANCE_INSTNAMEPLACEHOLDER", false, "IDS_TXTBOX_NEWINSTANCE_INSTANCENAME");
    UIElements.createButton(CreateInstanceUI::create_button, 640, 695, 350, 35, font, "IDS_BUTTON_NEWINSTANCE_CREATE", false);
    UIElements.createButton(CreateInstanceUI::instance_creation_cancel, 280, 695, 350, 35, font, "IDS_BUTTON_NEWINSTANCE_CANCEL", false);
    UIElements.createCheckbox(CreateInstanceUI::automount_checkbox, 30, 30, 10, 140, "IDS_CHKBOX_NEWINSTANCE_AUTOMOUNT", 26, font, false);
    UIElements.createCheckbox(CreateInstanceUI::create_with_graphics_preset_checkbox, 30, 30, 10, 180, "IDS_CHKBOX_NEWINSTANCE_CREATEWITHPRESET", 26, font, false);
    UIElements.createDropDownList(CreateInstanceUI::graphics_preset_ddl, 270, 40, 10, 220, {{"No preset","none"},{"Lowest","lowest"},{"Low","low"},{"Default","default"},{"Medium","medium"},{"High","high"},{"Higest","higest"}}, "No preset", font);

    UIElements.createButton(InstanceIconBar::next_button, 930, 330, 40, 80, font, ">", false);
    UIElements.createButton(InstanceIconBar::prev_button, 10, 330, 40, 80, font, "<", false);

    UIElements.createButton(saveEditedButton, 640, 695, 350, 35, font, "IDS_BUTTON_EDITINSTANCE_SAVE", false);

    UIElements.createTextbox(import_instance_name_textbox, 10, 20, 570, 40, false, false, font, 35, "IDS_TEXT_IMPORTINSTANCE_INSTNAMEPLACEHOLDER", false, "IDS_TXTBOX_IMPORTINSTANCE_INSTANCENAME");
    UIElements.createTextbox(import_instance_path_textbox, 10, 740, 1200, 30, false, false, font, 26, "", false, "IDS_TXTBOX_IMPORTINSTANCE_SOURCEPATH");
    UIElements.createButton(import_instance_path_browse_button, 1210, 771, 60, 30, font, "IDS_BUTTON_SETTINGS_BROWSE");
    UIElements.createButton(import_instance_confirm_button, 640, 695, 350, 35, font, "IDS_BUTTON_IMPORTINSTANCE_CONFIRM");
    UIElements.createButton(import_instance_cancel_button, 280, 695, 350, 35, font, "IDS_BUTTON_IMPORTINSTANCE_CANCEL");

    UIElements.createTransparrentBg(versions_bg, 0, 40, 1280, 800, true);

    UIElements.createButton(ManageSubcatListUI::informations_button, 0, 0, 120, 40, font, "IDS_BUTTON_MNG_DETAILS", false);
    UIElements.createButton(ManageSubcatListUI::vanilla_saves_button, 0, (0 + 42), 120, 40, font, "IDS_BUTTON_MNG_VS", false);
    UIElements.createButton(ManageSubcatListUI::betterbuild_saves_button, 0, (0 + 42 + 42), 120, 40, font, "IDS_BUTTON_MNG_MS", false);
    UIElements.createButton(ManageSubcatListUI::betterbuild_world_button, 0, (0 + 42 + 42 + 42), 120, 40, font, "IDS_BUTTON_MNG_BBW", false);
    UIElements.createButton(ManageSubcatListUI::backups_button, 0, (0 + 42 + 42 + 42 + 42), 120, 40, font, "IDS_BUTTON_MNG_BACKUPS", false);
    UIElements.createButton(ManageSubcatListUI::mods_button, 0, (0 + 42 + 42 + 42 + 42 + 42), 120, 40, font, "IDS_BUTTON_MNG_MODS", false);
    UIElements.createButton(ManageSubcatListUI::debug_button, 0, (0 + 42 + 42 + 42 + 42 + 42 + 42), 120, 40, font, "IDS_BUTTON_MNG_DEBUG", false);
    UIElements.createButton(ManageSubcatListUI::main_back_button, 0, 760, 120, 40, font, "IDS_BUTTON_MNG_BACK", false);

    UIElements.createTransparrentBg(ManageDebug::assemblyInfoBg, 830, 0, 450, 800, true);
    UIElements.createButton(ManageDebug::debugPatchButton, 130, 95, 120, 40, font, "");

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
    UIElements.createButton(version_back_button, 465, 750, 350, 40, font, "IDS_BUTTON_SRVERSIONS_BACK", false);

    UIElements.createButton(SettingsElemets::subcats::updates::check_for_update_button, 130, 100, 120, 40, font, "IDS_BUTTON_SRLUPDATE_CHECK", false);
    UIElements.createCheckbox(SettingsElemets::subcats::updates::autocheck_for_update_checkbox, 30, 30, 130, 150, "IDS_CHKBOX_SRLUPDATE_CHECKONSTART", 26, font, true);

    UIElements.createTextfield(SettingsElemets::subcats::licences::licenseField, 130, 60, 1140, 720, font);
}