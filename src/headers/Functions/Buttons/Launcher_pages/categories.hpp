void refresh_instances_list();
void display_version_log();

void changeCategory_main()
{
    UI_current = UiPages::MainMenu;
}

void changeCategory_instances()
{
    UI_current = UiPages::InstancesMenu;
    refresh_instances_list();
}

void changeCategory_settings()
{
    UI_current = UiPages::SettingsMenu;
    options_ui = SettingsCategories::MAIN_PAGE;
}

void changeCategory_versions()
{
    UI_current = UiPages::VersionsList;
    positionListElements();
    // display_version_log();
}