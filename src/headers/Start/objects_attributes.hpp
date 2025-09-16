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
    setTextAtt(MainpageElements::playbar::infoText, "", 36, 10, 725);

    setTextAtt(MainpageElements::playbar::versionText, "", 16, 10, 765);

    setTextAtt(MainpageElements::playbar::LauncherVersionText, "    SRL\nv." + launcher_version, 16, 0, 0);
    MainpageElements::playbar::LauncherVersionText.setPosition((window.getSize().x - 10) - MainpageElements::playbar::LauncherVersionText.getLocalBounds().width, 755);

    setTextAtt(no_instances_text, "No game instances were found. Create them or import currently existing.", 30, 0, 0);

    setTextAtt(instances_vanish_tooltip_text, "Have your instances vanished? Check if instances directory path is correct in settings.", 26, 0, 0);

    setTextAtt(bbw_tittle_text, "", 26, 0, 0);

    setTextAtt(update_status_text, "No update data", 26, 130, 380);

    setTextAtt(blockedPaths_text, "To change paths you must unmount current instance", 26, 160, 65, sf::Color::Red);

    setTextAtt(theme_label_text, "Launcher theme", 26, 130, 605);

    setTextAtt(downloaders_list_text, "Selected depot downloader", 26, 130, 40);

    setTextAtt(DebugSettingsUI::debug_info_text, "Debug options are only for mod developers! Do not enable that if you just want to play.", 26, 130, 55, sf::Color::Red);

    setTextAtt(credits_programming_text, "Programming: MCSR", 32, 130, 150);
    setTextAtt(github_page_link_text, "                 GitHub project page\nhttps://github.com/MinecraftSRDEV/SRLauncher", 32, 60, 240, sf::Color::Blue);
    setTextAtt(repos_page_link_text, "       Other My projects you can find at\nhttps://github.com/MinecraftSRDEV", 32, 60, 360, sf::Color::Blue);
    setTextAtt(issules_page_link_text, "            Found a BUG? Report it here\nhttps://github.com/MinecraftSRDEV/SRLauncher/issues", 32, 60, 450, sf::Color::Blue);

    setTextAtt(MainpageElements::details::lastPlayedDateText, "", 26, 730, 70);
    setTextAtt(MainpageElements::lastPlayed::noLastPlayedInstancesText, "No instances have been played recently", 26, 120, 140);
    setTextAtt(MainpageElements::details::totalPlayTimeInstanceText, "", 26, 730, 120);
    setTextAtt(MainpageElements::details::totalLauncherPlaytimeText, "", 26, 730, 70);
    setTextAtt(MainpageElements::details::debugWarnText, "Debugging is enabled!", 26, 730, 400, sf::Color::Red);

    setTextAtt(dataLoading_text, "", 32, 130, 380);

    setTextAtt(MainpageElements::playbar::downloadingProgressText, "", 20, 130, 380);

    setTextAtt(MainpageElements::lastPlayed::loadingMiniInstancesText, "", 20, 120, 140);

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

    setTextAtt(MNG_betterBuild_status, "", 26, 130, 520);

    setTextAtt(MNG_betterBuild_UID, "", 26, 130, 550);

    setTextAtt(tldr_text, "TLDR. This things are hard to do. If some thing don't work correctly please be patient, will be added\nin future. I don't have access to every informations, old mod files and more... so its hard to make\nuniversal tool without that. If some versions informations in launcher database are incorrect, please\ntell me about that.", 26, 130, 630, sf::Color::Red);

    setTextAtt(ManageDebug::assemblyDataText, "", 18, 840, 15);

    setTextAtt(bbw_tittle_text, "", 26, 0, 0);

    setTextAtt(vsc_text, "", 26, 0, 0);

    setTextAtt(msc_text, "", 26, 0, 0);

    setTextAtt(instance_ver_info_text, "", 20, 1005, 10);

    setTextAtt(CreateInstanceUI::isntance_will_be_created_in_text, "", 20, 10, 745);

    setTextAtt(editInstanceSource, "", 20, 10, 745);

    setTextAtt(CreateInstanceUI::instance_file_separation_text, "Your gamesaves, options and achivements will be automatically separated\nindyvidualy for each instance.\nIf you had any this files before launcher installation instance can't be mounted", 26, 10, 530);
    
    setTextAtt(InstanceIconBar::icon_bar_text, "Select icon", 26, 10, 300);

    setTextAtt(MainpageElements::debuger::ipcElapsedText, "", 12, 30, 670);
}

void setShapesAttributes()
{
    steam_profile_icon.setPosition(sf::Vector2f(130, 410));

    MainpageElements::playbar::progress_bg.setSize(sf::Vector2f(1280, 20));
    MainpageElements::playbar::progress_bg.setPosition(sf::Vector2f(0, 780));
    MainpageElements::playbar::progress_bg.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::inactive]);

    MainpageElements::playbar::progress_moveing.setSize(sf::Vector2f(70, 20));
    MainpageElements::playbar::progress_moveing.setPosition(sf::Vector2f(-70, 780));
    MainpageElements::playbar::progress_moveing.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::checkbox_inactive]);

    MainpageElements::debuger::working.setSize(sf::Vector2f(10, 10));
    MainpageElements::debuger::working.setPosition(sf::Vector2f(10, 670));
    MainpageElements::debuger::working.setFillColor(sf::Color::Red);

    instanceModsMouseWorkingBox.setSize(sf::Vector2f(565, 790));
    instanceModsMouseWorkingBox.setPosition(sf::Vector2f(126, 5));
    instanceModsMouseWorkingBox.setFillColor(sf::Color::Transparent);

    launcherModsMouseWorkingBox.setSize(sf::Vector2f(565, 790));
    launcherModsMouseWorkingBox.setPosition(sf::Vector2f(695, 5));
    launcherModsMouseWorkingBox.setFillColor(sf::Color::Transparent);

    instancesScrollingArea.setSize(sf::Vector2f(1280, 629));
    instancesScrollingArea.setPosition(sf::Vector2f(0, 84));
    instancesScrollingArea.setFillColor(sf::Color::Transparent);

    MainpageElements::lastPlayed::mouseBox.setSize(sf::Vector2f(680, 400));
    MainpageElements::lastPlayed::mouseBox.setPosition(sf::Vector2f(20, 45));
    MainpageElements::lastPlayed::mouseBox.setFillColor(sf::Color::Transparent);

    MainpageElements::console::mouseBox.setSize(sf::Vector2f(1240, 240));
    MainpageElements::console::mouseBox.setPosition(sf::Vector2f(20, 450));
    MainpageElements::console::mouseBox.setFillColor(sf::Color::Transparent);

    MainpageElements::playbar::downloadingProgress.create(0, 780, sf::Vector2f(1280, 20), ProgressBar::Mode::Static, 100.0f);

    InstanceIconBar::selectedBG.setSize(sf::Vector2f(80, 80));
    InstanceIconBar::selectedBG.setPosition(sf::Vector2f(50, 330));
    InstanceIconBar::selectedBG.setFillColor(sf::Color(255, 255, 20));
}