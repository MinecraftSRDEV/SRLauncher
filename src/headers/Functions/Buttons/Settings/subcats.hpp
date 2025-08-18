void settings_main_cat()
{
    options_ui = SettingsCategories::MAIN_PAGE;
}

void settings_profile_cat()
{
    options_ui = SettingsCategories::PROFILE_PAGE;
    getSteamAccountStats();
}

void settings_downloading_cat()
{
    options_ui = SettingsCategories::DOWNLOADING_PAGE;
}

void settings_updates_cat()
{
    options_ui = SettingsCategories::UPDATES_PAGE;
}

void settings_debugging_cat()
{
    options_ui = SettingsCategories::DEBUGGING_PAGE;

    DebugSettingsUI::acceptInfoCheckbox.setState(acceptInfoLogs);
    DebugSettingsUI::acceptWarningCheckbox.setState(acceptWarningLogs);
    DebugSettingsUI::acceptErrorCheckbox.setState(acceptErrorLogs);
    DebugSettingsUI::acceptExceptionCheckbox.setState(acceptExceptionLogs);
}

void settings_licences_cat()
{
    options_ui = SettingsCategories::LICENCES_PAGE;
    LicencesUI::licenseField.toUp();
}

void settings_credits_cat()
{
    credits_programming_text.setPosition((window.getSize().x / 2) - (credits_programming_text.getLocalBounds().width / 2), 150);
    github_page_link_text.setPosition((window.getSize().x / 2) - (github_page_link_text.getLocalBounds().width / 2), 240);
    repos_page_link_text.setPosition((window.getSize().x / 2) - (repos_page_link_text.getLocalBounds().width / 2), 360);
    issules_page_link_text.setPosition((window.getSize().x / 2) - (issules_page_link_text.getLocalBounds().width / 2), 450);
    options_ui = SettingsCategories::CREDITS_PAGE;
}