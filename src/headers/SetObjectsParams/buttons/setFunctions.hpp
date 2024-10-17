void hanglefunction();
void get_textbox_settings_values_and_save();
void save_profiles();

void clearConsole()
{
    console.clearText();
    log_message("Console ready", LOG_TYPES::LOG_INFO);
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
    create_button.setFunction(create_instance);

    import_instance_confirm_button.setFunction(import_instance);
    import_instance_cancel_button.setFunction(cancel_instance_import);

    launch_last_instance_button.setFunction(hanglefunction);

    check_for_update_button.setFunction(checkUpdate);

    Subcat_settings_main_button.setFunction(settings_main_cat);
    Subcat_settings_progile_button.setFunction(settings_profile_cat);
    Subcat_settings_updates_button.setFunction(settings_updates_cat);
    Subcat_settings_credits_button.setFunction(settings_credits_cat);

    SlimeRancher_steam_path_getfolder_button.setFunction(getfolder_steamdir);
    SlimeRancher_instances_path_getfolder_button.setFunction(getfolder_instancesdir);
    steamcmd_path_getfolder_button.setFunction(getfolder_steamcmddir);

    SteamProfile_name_textbox.setOnChangeFunction(getSteamAccountStats);

    RestoreSettings_button.setFunction(setSettingsDefault);
    SaveConfig_button.setFunction(get_textbox_settings_values_and_save);

    save_profile_button.setFunction(get_profile_textboxes_values_and_save);

    manage_main_back_button.setFunction(exit_manage_function);
    manage_betterbuild_world_button.setFunction(changeCategory_mng_bbworls);
    manage_mods_button.setFunction(changeCategory_mng_mods);

    version_back_button.setFunction(changeCategory_versions);

    console_clear_button.setFunction(clearConsole);
}