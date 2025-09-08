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
    if (instancesListLoading == false)
    {
        if (UI_current == UiPages::SettingsMenu)
        {
            ButtonUIHilight(settingsGeneralCat_button, options_ui, SettingsCategories::MAIN_PAGE);
            ButtonUIHilight(settingsProfileCat_button, options_ui, SettingsCategories::PROFILE_PAGE);
            ButtonUIHilight(settingsDownloadingCat_button, options_ui, SettingsCategories::DOWNLOADING_PAGE);
            ButtonUIHilight(settingsUpdatesCat_button, options_ui, SettingsCategories::UPDATES_PAGE);
            ButtonUIHilight(settingsDebuggingCat_button, options_ui, SettingsCategories::DEBUGGING_PAGE);
            ButtonUIHilight(settingsCreditsCat_button, options_ui, SettingsCategories::CREDITS_PAGE);
            ButtonUIHilight(settingsLicencesCat_button, options_ui, SettingsCategories::LICENCES_PAGE);
        }

        if (UI_current == UiPages::ManageMenu)
        {
            ButtonUIHilight(manage_vanilla_saves_button, manage_ui, ManageCategories::VANILLA_SAVES);
            ButtonUIHilight(manage_mods_button, manage_ui, ManageCategories::MODS_PAGE);
            ButtonUIHilight(manage_backups_button, manage_ui, ManageCategories::BACKUPS);
            ButtonUIHilight(manage_betterbuild_saves_button, manage_ui, ManageCategories::BETTERBUILD_SAVES);
            ButtonUIHilight(manage_betterbuild_world_button, manage_ui, ManageCategories::BETTERBUILD_WORLDS);
        }

        if (instancesListLoading == false)
        {
            ButtonUIHilight(MainCategory_button, UI_current, UiPages::MainMenu);
            ButtonUIHilight(InstancesCategory_button, UI_current, UiPages::InstancesMenu);
            ButtonUIHilight(SettingsCategory_button, UI_current, UiPages::SettingsMenu);
            ButtonUIHilight(VersionsCategory_button, UI_current, UiPages::VersionsList);       
        }
    }
}