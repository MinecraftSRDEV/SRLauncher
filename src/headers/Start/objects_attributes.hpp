void setTextAtt(sf::Text& text, const std::string& str, int fontSize, int x, int y, sf::Color color = sf::Color(255,255,255))
{
    if (color == sf::Color(255,255,255))
    {
        UIElements.UITexts.emplace_back(&text);

    }
    else
    {
        text.setFillColor(color);    
    }
    
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setString(str);
    text.setPosition(x, y);
}

void setRuntimeTexts()
{
    setTextAtt(Mounted_instance_info_text, "", 36, 10, 725);

    setTextAtt(mounted_instance_version, "", 16, 10, 765);

    setTextAtt(Launcher_version_text, launcher_version, 36, 0, 0);
    Launcher_version_text.setPosition((window.getSize().x - 10) - Launcher_version_text.getLocalBounds().width, 725);

    setTextAtt(bbw_tittle_text, "", 26, 0, 0);

    setTextAtt(update_status_text, "No update data", 26, 130, 380);

    setTextAtt(theme_label_text, "Launcher theme (experimental)", 26, 130, 520);

    setTextAtt(downloaders_list_text, "Selected depot downloader", 26, 680, 520);

    setTextAtt(credits_programming_text, "Programming: MCSR", 32, 130, 380);

    setTextAtt(dataLoading_text, "", 32, 130, 380);

    setTextAtt(downloading_progress_text, "", 20, 130, 380);

    setTextAtt(version_description_text, "", 26, 10, 10);

    setTextAtt(Profile_warning_text, "", 26, 130, 600);

    setTextAtt(steam_profile_offline_status_text, "", 26, 320, 420);

    setTextAtt(steam_profile_AccountName_text, "", 26, 320, 450);

    setTextAtt(steam_profile_PersonalName_text, "", 26, 320, 480);

    setTextAtt(steam_profile_UID_text, "", 26, 320, 510);

    setTextAtt(profile_presonal_data_warning_text, "This data is only needed to download the game using the downloader of your choice.\nYou can use the launcher without this if you already have the game files downloaded.\nI DON'T NEED YOUR LOGIN DETAILS, I DON'T COLLECT THEM IN ANY WAY,\nYOU CAN SAFELY ENTER THEM WITHOUT WORRYING ABOUT THEM LEAKING.", 26, 135, 270, sf::Color::Red);

    setTextAtt(list_mods_instance_text, "Installed mods", 19, 0, 0);
    list_mods_instance_text.setPosition(130 + (280 - (list_mods_instance_text.getLocalBounds().width / 2)), 0);

    setTextAtt(list_mods_launcher_text, "Launcher mods", 19, 0, 0);
    list_mods_launcher_text.setPosition((130 + 560) + ((10 + 280) - (list_mods_launcher_text.getLocalBounds().width / 2)), 0);

    setTextAtt(MNG_Instance_name_text, "Instance name: ", 26, 0, 0);

    setTextAtt(MNG_Instance_saves_text, "Game saves count: ", 26, 0, 0);

    setTextAtt(MNG_instance_mods_own_text, "Installed mods: ", 26, 0, 0);

    setTextAtt(MNG_instance_mods_launcher_text, "Launcher mods: ", 26, 0, 0);

    setTextAtt(tldr_text, "TLDR. This things are hard to do. If some thing don't work correctly please be patient, will be added\nin future. I don't have access to every informations, old mod files and more... so its hard to make\nuniversal tool without that. If some versions informations in launcher database are incorrect, please\ntell me about that.", 26, 130, 600, sf::Color::Red);

    setTextAtt(bbw_tittle_text, "", 26, 0, 0);

    setTextAtt(vsc_text, "", 26, 0, 0);

    setTextAtt(msc_text, "", 26, 0, 0);

    setTextAtt(instance_ver_info_text, "", 20, 1005, 10);

    setTextAtt(CreateInstanceUI::isntance_will_be_created_in_text, "", 20, 10, 745);

    setTextAtt(editInstanceSource, "", 20, 10, 745);

    setTextAtt(CreateInstanceUI::instance_file_separation_text, "Your gamesaves, options and achivements will be automatically separated\nindyvidualy for each instance.\nIf you had any this files before launcher installation instance can't be mounted", 26, 10, 530);
    
    setTextAtt(InstanceIconBar::icon_bar_text, "Select icon", 26, 10, 300);
}

void setShapesAttributes()
{
    steam_profile_icon.setPosition(sf::Vector2f(130, 410));

    progress_bg.setSize(sf::Vector2f(1280, 20));
    progress_bg.setPosition(sf::Vector2f(0, 780));
    progress_bg.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::inactive]);

    progress_moveing.setSize(sf::Vector2f(70, 20));
    progress_moveing.setPosition(sf::Vector2f(-70, 780));
    progress_moveing.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::checkbox_inactive]);

    InstanceIconBar::selectedBG.setSize(sf::Vector2f(80, 80));
    InstanceIconBar::selectedBG.setPosition(sf::Vector2f(50, 330));
    InstanceIconBar::selectedBG.setFillColor(sf::Color(255, 255, 20));
}