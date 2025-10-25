namespace instUtilitiesFunctions
{
    void refreshList()
    {
        instUtilitiesMenu::hideMenuInsantly();
        refresh_instances_list();
    }

    void downloadAll()
    {
        instUtilitiesMenu::hideMenuInsantly();
        UI_current = UiPages::SelectionMenu;
        // apply instances informations from map to submap, and create List with checkboxes
    }

    void goToSettings()
    {
        instUtilitiesMenu::hideMenuInsantly();
        launcherCategories::settings();
    }
}