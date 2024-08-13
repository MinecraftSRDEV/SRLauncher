void refresh_instances_list();

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

void changeCategory_datatools()
{
    UI_current = UI_PAGES::DataToolsMenu;
}