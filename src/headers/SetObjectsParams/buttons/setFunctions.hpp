void hanglefunction();
void get_textbox_settings_values_and_save();
void save_profiles();
void getfolder_steamdir();
void getfolder_instancesdir();
void setSettingsDefault();

void setFunctions()
{
    MainCategory_button.setFunction(changeCategory_main);
    InstancesCategory_button.setFunction(changeCategory_instances);
    SettingsCategory_button.setFunction(changeCategory_settings);
    SavesToolCategory_button.setFunction(changeCategory_datatools);

    new_instance_button.setFunction(new_instance_change);

    instance_creation_cancel.setFunction(cancel_instance_creation);
    create_button.setFunction(create_instance);

    launch_last_instance_button.setFunction(hanglefunction);

    Subcat_settings_main_button.setFunction(settings_main_cat);
    Subcat_settings_progile_button.setFunction(settings_profile_cat);

    SlimeRancher_steam_path_getfolder_button.setFunction(getfolder_steamdir);
    SlimeRancher_instances_path_getfolder_button.setFunction(getfolder_instancesdir);

    RestoreSettings_button.setFunction(setSettingsDefault);
    SaveConfig_button.setFunction(get_textbox_settings_values_and_save);

    save_profile_button.setFunction(get_profile_textboxes_values_and_save);
}