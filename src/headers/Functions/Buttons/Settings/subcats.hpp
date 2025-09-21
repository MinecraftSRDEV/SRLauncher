namespace settingsCategories
{
    void main_cat()
    {
        options_ui = SettingsCategories::MAIN_PAGE;
    }

    void profile_cat()
    {
        options_ui = SettingsCategories::PROFILE_PAGE;
        getSteamAccountStats();
    }

    void downloading_cat()
    {
        options_ui = SettingsCategories::DOWNLOADING_PAGE;
    }

    void updates_cat()
    {
        options_ui = SettingsCategories::UPDATES_PAGE;
    }

    void debugging_cat()
    {
        options_ui = SettingsCategories::DEBUGGING_PAGE;

        SettingsElemets::subcats::debug::acceptInfoCheckbox.setState(acceptInfoLogs);
        SettingsElemets::subcats::debug::acceptWarningCheckbox.setState(acceptWarningLogs);
        SettingsElemets::subcats::debug::acceptErrorCheckbox.setState(acceptErrorLogs);
        SettingsElemets::subcats::debug::acceptExceptionCheckbox.setState(acceptExceptionLogs);
    }

    void licences_cat()
    {
        options_ui = SettingsCategories::LICENCES_PAGE;
        SettingsElemets::subcats::licences::licenseField.toUp();
    }

    void credits_cat()
    {
        SettingsElemets::subcats::credits::credits_programming_text.setPosition((window.getSize().x / 2) - (SettingsElemets::subcats::credits::credits_programming_text.getLocalBounds().width / 2), 150);
        SettingsElemets::subcats::credits::github_page_link_text.setPosition((window.getSize().x / 2) - (SettingsElemets::subcats::credits::github_page_link_text.getLocalBounds().width / 2), 240);
        SettingsElemets::subcats::credits::repos_page_link_text.setPosition((window.getSize().x / 2) - (SettingsElemets::subcats::credits::repos_page_link_text.getLocalBounds().width / 2), 360);
        SettingsElemets::subcats::credits::issules_page_link_text.setPosition((window.getSize().x / 2) - (SettingsElemets::subcats::credits::issules_page_link_text.getLocalBounds().width / 2), 450);
        options_ui = SettingsCategories::CREDITS_PAGE;
    }
}