void refresh_instances_list();

namespace launcherCategories
{
    void main()
    {
        UI_current = UiPages::MainMenu;
    }

    void instances()
    {
        UI_current = UiPages::InstancesMenu;
        refresh_instances_list();
    }

    void settings()
    {
        UI_current = UiPages::SettingsMenu;
        options_ui = SettingsCategories::MAIN_PAGE;
    }

    void versions()
    {
        UI_current = UiPages::VersionsList;
        positionListElements();
    }
}
