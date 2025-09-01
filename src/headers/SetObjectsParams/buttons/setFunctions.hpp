void runGameInitial();
void getSettingsValuesAndSave();
void save_profiles();

void clearConsole()
{
    console.clearText();
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
    MainCategory_button.setFunction(changeCategory_main);
    InstancesCategory_button.setFunction(changeCategory_instances);
    SettingsCategory_button.setFunction(changeCategory_settings);
    VersionsCategory_button.setFunction(changeCategory_versions);

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

    settingsGeneralCat_button.setFunction(settings_main_cat);
    settingsProfileCat_button.setFunction(settings_profile_cat);
    settingsDownloadingCat_button.setFunction(settings_downloading_cat);
    settingsUpdatesCat_button.setFunction(settings_updates_cat);
    settingsDebuggingCat_button.setFunction(settings_debugging_cat);
    settingsLicencesCat_button.setFunction(settings_licences_cat);
    settingsCreditsCat_button.setFunction(settings_credits_cat);

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

    manage_main_back_button.setFunction(exit_manage_function);
    manage_betterbuild_world_button.setFunction(changeCategory_mng_bbworls);
    manage_vanilla_saves_button.setFunction(changeCategory_mng_vanilla);
    manage_betterbuild_saves_button.setFunction(changeCategory_mng_bbsaves);
    manage_mods_button.setFunction(changeCategory_mng_mods);
    manage_backups_button.setFunction(changeCategory_mng_backups);

    MNG_Instance_saves_text.setFunction(changeCategory_mng_vanilla);
    MNG_instance_installed_mods_text.setFunction(changeCategory_mng_mods);
    MNG_instance_mods_saves_text.setFunction(changeCategory_mng_bbworls);
    MNG_instance_mods_launcher_text.setFunction(changeCategory_mng_mods);

    version_back_button.setFunction(changeCategory_versions);

    console_clear_button.setFunction(clearConsole);
}