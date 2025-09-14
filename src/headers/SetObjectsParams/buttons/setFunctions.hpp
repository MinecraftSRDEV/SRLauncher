void runGameInitial();
void getSettingsValuesAndSave();
void save_profiles();

void clearConsole()
{
    ConsoleElements::console.clearText();
    log_message("Console ready", LogTypes::LOG_INFO);
}

void updateShowPrereleaseState()
{
    show_prerelease_version = Show_prereleases_checkbox.getState();
}

void applyTheme()
{
    std::string result = theme_list_ddl.getRResult();
    theme_selected = std::stoi(result);
    setTheme();
}

void setDownloader()
{
    std::string result = downloaders_ddl.getRResult();
    downloader_selected = std::stoi(result);

    if (downloader_selected == steamcmd)
    {
        steamcmd_path_textbox.setLabelText(settmaindi::CMDPATH_TEXT);
    }
    else
    {
        steamcmd_path_textbox.setLabelText(settmaindi::CMDPATH_DISABLED);
    }
}

void setFunctions()
{
    MainCategory_button.setFunction(launcherCategories::main);
    InstancesCategory_button.setFunction(launcherCategories::instances);
    SettingsCategory_button.setFunction(launcherCategories::settings);
    VersionsCategory_button.setFunction(launcherCategories::versions);

    new_instance_button.setFunction(new_instance_change);
    import_instnace_button.setFunction(import_instance_change);

    instance_creation_cancel.setFunction(cancel_instance_creation);
    // create_button.setFunction(generate_instances_list);
    create_button.setFunction(instance_params);

    InstanceIconBar::next_button.setFunction(iconsBarScrollLeft);
    InstanceIconBar::prev_button.setFunction(iconsBarScrollRight);

    saveEditedButton.setFunction(setEditedInstace);

    import_instance_confirm_button.setFunction(import_instance);
    import_instance_cancel_button.setFunction(cancel_instance_import);

    launch_game_button.setFunction(runGameInitial);

    check_for_update_button.setFunction(checkUpdate);

    settingsGeneralCat_button.setFunction(settingsCategories::main_cat);
    settingsProfileCat_button.setFunction(settingsCategories::profile_cat);
    settingsDownloadingCat_button.setFunction(settingsCategories::downloading_cat);
    settingsUpdatesCat_button.setFunction(settingsCategories::updates_cat);
    settingsDebuggingCat_button.setFunction(settingsCategories::debugging_cat);
    settingsLicencesCat_button.setFunction(settingsCategories::licences_cat);
    settingsCreditsCat_button.setFunction(settingsCategories::credits_cat);

    Show_prereleases_checkbox.setFunction(updateShowPrereleaseState);

    steam_path_getfolder_button.setFunction(getfolder_steamdir);
    instances_path_getfolder_button.setFunction(getfolder_instancesdir);
    steamcmd_path_getfolder_button.setFunction(getfolder_steamcmddir);

    downloaders_ddl.setFunction(setDownloader);
    theme_list_ddl.setFunction(applyTheme);

    SRL_background_img_path_getfolder_button.setFunction(getfolder_background_path);

    SteamProfile_name_textbox.setOnChangeFunction(getSteamAccountStats);

    RestoreSettings_button.setFunction(setSettingsDefault);
    SaveConfig_button.setFunction(getSettingsValuesAndSave);

    save_profile_button.setFunction(getProfileSettingsValuesAndSave);

    DebugSettingsUI::forcePipeCloseButton.setFunction(DebugBridge::forceClose);
    DebugSettingsUI::killInstanceButton.setFunction(DebugBridge::killInstance);
    DebugSettingsUI::saveDebugLogsToOtherFileCheckbox.setFunction(DebugBridge::saveLogs);
    DebugSettingsUI::enableDebuggingOnInstance.setFunction(DebugBridge::applyDebugPathToInstance);

    ManageSubcatListUI::informations_button.setFunction(manageCategories::details);
    ManageSubcatListUI::main_back_button.setFunction(manageCategories::exit_function);
    ManageSubcatListUI::betterbuild_world_button.setFunction(manageCategories::bbworls);
    ManageSubcatListUI::vanilla_saves_button.setFunction(manageCategories::vanilla);
    ManageSubcatListUI::betterbuild_saves_button.setFunction(manageCategories::bbsaves);
    ManageSubcatListUI::mods_button.setFunction(manageCategories::mods);
    ManageSubcatListUI::backups_button.setFunction(manageCategories::backups);
    ManageSubcatListUI::debug_button.setFunction(manageCategories::debug);

    MNG_Instance_saves_text.setFunction(manageCategories::vanilla);
    MNG_instance_installed_mods_text.setFunction(manageCategories::mods);
    MNG_instance_mods_saves_text.setFunction(manageCategories::bbworls);
    MNG_instance_mods_launcher_text.setFunction(manageCategories::mods);

    version_back_button.setFunction(launcherCategories::versions);

    ConsoleElements::console_clear_button.setFunction(clearConsole);
}