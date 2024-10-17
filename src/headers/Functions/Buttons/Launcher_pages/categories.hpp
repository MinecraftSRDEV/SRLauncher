void refresh_instances_list();
void display_version_log();

void changeCategory_main()
{
    UI_current = UI_PAGES::MainMenu;
}

void changeCategory_instances()
{
    UI_current = UI_PAGES::InstancesMenu;
    refresh_instances_list();
}

void changeCategory_settings()
{
    UI_current = UI_PAGES::SettingsMenu;
}

void changeCategory_versions()
{
    UI_current = UI_PAGES::VersionsList;
    positionListElements();
    // display_version_log();
}

void exit_manage_function()
{
    UI_current = UI_PAGES::InstancesMenu;
    selected_instance.erase();
    refresh_instances_list();
}

void changeCategory_mng_bbworls()
{
    manage_ui = BETTERBUILD_WORLDS;
}

void changeCategory_mng_mods()
{
    manage_ui = MODS_PAGE;
}