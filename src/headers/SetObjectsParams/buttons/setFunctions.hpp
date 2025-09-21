void runGameInitial();
void getSettingsValuesAndSave();
void save_profiles();

void clearConsole()
{
    MainpageElements::console::console.clearText();
    log_message("Console ready", LogTypes::LOG_INFO);
}

void updateShowPrereleaseState()
{
    show_prerelease_version = SettingsElemets::subcats::general::Show_prereleases_checkbox.getState();
}

void applyTheme()
{
    std::string result = SettingsElemets::subcats::general::theme_list_ddl.getRResult();
    theme_selected = std::stoi(result);
    setTheme();
}

void setDownloader()
{
    std::string result = SettingsElemets::subcats::downloading::downloaders_ddl.getRResult();
    downloader_selected = std::stoi(result);

    if (downloader_selected == steamcmd)
    {
        SettingsElemets::subcats::downloading::steamcmd_path_textbox.setLabelText(settmaindi::CMDPATH_TEXT);
    }
    else
    {
        SettingsElemets::subcats::downloading::steamcmd_path_textbox.setLabelText(settmaindi::CMDPATH_DISABLED);
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

    MainpageElements::playbar::launchGameButton.setFunction(runGameInitial);

    SettingsElemets::subcats::updates::check_for_update_button.setFunction(checkUpdate);

    SettingsElemets::subcatsBar::generalCat_button.setFunction(settingsCategories::main_cat);
    SettingsElemets::subcatsBar::profileCat_button.setFunction(settingsCategories::profile_cat);
    SettingsElemets::subcatsBar::downloadingCat_button.setFunction(settingsCategories::downloading_cat);
    SettingsElemets::subcatsBar::updatesCat_button.setFunction(settingsCategories::updates_cat);
    SettingsElemets::subcatsBar::debuggingCat_button.setFunction(settingsCategories::debugging_cat);
    SettingsElemets::subcatsBar::licencesCat_button.setFunction(settingsCategories::licences_cat);
    SettingsElemets::subcatsBar::creditsCat_button.setFunction(settingsCategories::credits_cat);

    SettingsElemets::subcats::general::Show_prereleases_checkbox.setFunction(updateShowPrereleaseState);

    SettingsElemets::subcats::general::steam_path_getfolder_button.setFunction(getfolder_steamdir);
    SettingsElemets::subcats::general::instances_path_getfolder_button.setFunction(getfolder_instancesdir);
    SettingsElemets::subcats::downloading::steamcmd_path_getfolder_button.setFunction(getfolder_steamcmddir);

    SettingsElemets::subcats::downloading::downloaders_ddl.setFunction(setDownloader);
    SettingsElemets::subcats::general::theme_list_ddl.setFunction(applyTheme);

    SettingsElemets::subcats::general::SRL_background_img_path_getfolder_button.setFunction(getfolder_background_path);

    SettingsElemets::subcats::steamAccount::profileName_textbox.setOnChangeFunction(getSteamAccountStats);

    SettingsElemets::bottomBar::RestoreSettings_button.setFunction(setSettingsDefault);
    SettingsElemets::bottomBar::SaveConfig_button.setFunction(getSettingsValuesAndSave);

    SettingsElemets::subcats::steamAccount::save_profile_button.setFunction(getProfileSettingsValuesAndSave);

    SettingsElemets::subcats::debug::forcePipeCloseButton.setFunction(DebugBridge::forceClose);
    SettingsElemets::subcats::debug::killInstanceButton.setFunction(DebugBridge::killInstance);
    SettingsElemets::subcats::debug::saveDebugLogsToOtherFileCheckbox.setFunction(DebugBridge::saveLogs);

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

    MainpageElements::console::clearButton.setFunction(clearConsole);
}