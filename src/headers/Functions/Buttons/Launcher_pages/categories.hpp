void refresh_instances_list();
namespace miniInstanceList
{
    void prepare();
}

namespace instUtilitiesMenu
{
    void hideMenuInsantly();
}

namespace launcherCategories
{
    void main()
    {
        UI_current = UiPages::MainMenu;
        instUtilitiesMenu::hideMenuInsantly();
        miniInstanceList::prepare();
    }

    void instances()
    {
        instUtilitiesMenu::hideMenuInsantly();
        UI_current = UiPages::InstancesMenu;
        refresh_instances_list();
    }

    void settings()
    {
        instUtilitiesMenu::hideMenuInsantly();
        UI_current = UiPages::SettingsMenu;
        options_ui = SettingsCategories::MAIN_PAGE;
    }

    void versions()
    {
        instUtilitiesMenu::hideMenuInsantly();
        UI_current = UiPages::VersionsList;
        positionListElements();
    }
}
