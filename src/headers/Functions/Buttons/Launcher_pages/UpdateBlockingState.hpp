void ButtonUIHilight(sfg::Button& button, int& triggeredWhen, int targettedVar)
{
    if (triggeredWhen == targettedVar)
    {
        button.setBlockState(true);
    }
    else
    {
        button.setBlockState(false);
    }
}

void updateButtonsBlockingState()
{
    if (instancesLoader::instancesListLoading == false)
    {
        if (UI_current == UiPages::SettingsMenu)
        {
            ButtonUIHilight(SettingsElemets::subcatsBar::generalCat_button, options_ui, SettingsCategories::MAIN_PAGE);
            ButtonUIHilight(SettingsElemets::subcatsBar::profileCat_button, options_ui, SettingsCategories::PROFILE_PAGE);
            ButtonUIHilight(SettingsElemets::subcatsBar::downloadingCat_button, options_ui, SettingsCategories::DOWNLOADING_PAGE);
            ButtonUIHilight(SettingsElemets::subcatsBar::updatesCat_button, options_ui, SettingsCategories::UPDATES_PAGE);
            ButtonUIHilight(SettingsElemets::subcatsBar::debuggingCat_button, options_ui, SettingsCategories::DEBUGGING_PAGE);
            ButtonUIHilight(SettingsElemets::subcatsBar::creditsCat_button, options_ui, SettingsCategories::CREDITS_PAGE);
            ButtonUIHilight(SettingsElemets::subcatsBar::licencesCat_button, options_ui, SettingsCategories::LICENCES_PAGE);
        }

        if (UI_current == UiPages::ManageMenu)
        {
            ButtonUIHilight(ManageSubcatListUI::vanilla_saves_button, manage_ui, ManageCategories::VANILLA_SAVES);
            ButtonUIHilight(ManageSubcatListUI::mods_button, manage_ui, ManageCategories::MODS_PAGE);
            ButtonUIHilight(ManageSubcatListUI::backups_button, manage_ui, ManageCategories::BACKUPS);
            ButtonUIHilight(ManageSubcatListUI::betterbuild_saves_button, manage_ui, ManageCategories::BETTERBUILD_SAVES);
            ButtonUIHilight(ManageSubcatListUI::betterbuild_world_button, manage_ui, ManageCategories::BETTERBUILD_WORLDS);
            ButtonUIHilight(ManageSubcatListUI::debug_button, manage_ui, ManageCategories::DEBUG_PAGE);
            ButtonUIHilight(ManageSubcatListUI::informations_button, manage_ui, ManageCategories::MNG_MAIN_PAGE);
        }

        if (instancesLoader::instancesListLoading == false)
        {
            ButtonUIHilight(MainCategory_button, UI_current, UiPages::MainMenu);
            ButtonUIHilight(InstancesCategory_button, UI_current, UiPages::InstancesMenu);
            ButtonUIHilight(SettingsCategory_button, UI_current, UiPages::SettingsMenu);
            ButtonUIHilight(VersionsCategory_button, UI_current, UiPages::VersionsList);
        }
    }
}