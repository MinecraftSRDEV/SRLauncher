void settings_main_cat()
{
    options_ui = SETTIGNS_CATEGORIES::MAIN_PAGE;
}

void settings_profile_cat()
{
    options_ui = SETTIGNS_CATEGORIES::PROFILE_PAGE;
    getSteamAccountStats();
}

void settings_updates_cat()
{
    options_ui = SETTIGNS_CATEGORIES::UPDATES_PAGE;
}

void settings_credits_cat()
{
    credits_programming_text.setPosition((window.getSize().x / 2) - (credits_programming_text.getLocalBounds().width / 2), 320);
    options_ui = SETTIGNS_CATEGORIES::CREDITS_PAGE;
}