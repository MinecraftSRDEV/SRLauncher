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

void setRectAtt(sf::RectangleShape& rect, int x, int y, int dx, int dy, sf::Color color = sf::Color(255,255,255))
{
    rect.setSize(sf::Vector2f(dx, dy));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setFillColor(color);
}

namespace subfunctions
{
    namespace setRuntimeTextsFunctions
    {
        void mainCategoryBottomBar()
        {
            {
                using namespace MainpageElements;

                setTextAtt(playbar::infoText, "", 36, 10, 725);

                setTextAtt(playbar::versionText, "", 16, 10, 765);

                setTextAtt(playbar::LauncherVersionText, "    SRL\nv." + launcher_version, 16, 0, 0);

                playbar::LauncherVersionText.setPosition((window.getSize().x - 10) - playbar::LauncherVersionText.getLocalBounds().width, 755);

                setTextAtt(playbar::downloadingProgressText, "", 20, 130, 380);
                
                setTextAtt(details::lastPlayedDateText, "", 26, 730, 70);
                setTextAtt(details::totalPlayTimeInstanceText, "", 26, 730, 120);
                setTextAtt(details::totalLauncherPlaytimeText, "", 26, 730, 70);
                setTextAtt(details::debugWarnText, tr("IDS_TEXT_DETAILS_DEBUGENABLED"), 26, 730, 400, sf::Color::Red);

                setTextAtt(lastPlayed::noLastPlayedInstancesText, tr("IDS_TEXT_MAIN_NOMINIINSTANCES"), 26, 120, 140);

                setTextAtt(lastPlayed::loadingMiniInstancesText, "", 20, 120, 140);
                
                setTextAtt(debuger::ipcElapsedText, "", 12, 30, 670);
            }
        }

        void instancesCategoryBody()
        {
            setTextAtt(no_instances_text, tr("IDS_TEXT_INSTLIST_NOINSTANCES"), 30, 0, 0);

            setTextAtt(instances_vanish_tooltip_text, tr("IDS_TEXT_INSTLIST_INSTANCESVANISHED"), 26, 0, 0);

            setTextAtt(dataLoading_text, "", 32, 130, 380);
        }

        void settingsTexts()
        {
            {
                using namespace SettingsElemets;

                setTextAtt(subcats::updates::update_status_text, tr("IDS_TEXT_SRLUPDATE_NOUPDATEDATA"), 26, 130, 380);

                setTextAtt(subcats::general::blockedPaths_text, tr("IDS_TEXT_SETTINGS_BLOCKEDPATHS"), 26, 160, 65, sf::Color::Red);

                setTextAtt(subcats::general::theme_label_text, tr("IDS_TEXT_SETTINGS_LAUNCHERTHEME"), 26, 130, 605);

                setTextAtt(subcats::general::language_labet_text, tr("IDS_TEXT_SETTINGS_LANGUAGESEL"), 26, 420, 605);

                setTextAtt(subcats::downloading::downloaders_list_text, tr("IDS_TEXT_DOWNLOADING_SELECTEDDOWNLOADER"), 26, 130, 40);

                setTextAtt(subcats::debug::debug_info_text, tr("IDS_TEXT_DEBUG_WARNING"), 26, 130, 55, sf::Color::Red);

                setTextAtt(subcats::credits::credits_programming_text, "Programming: MCSR", 32, 130, 150);
                setTextAtt(subcats::credits::github_page_link_text, "                 GitHub project page\nhttps://github.com/MinecraftSRDEV/SRLauncher", 32, 60, 240, sf::Color::Blue);
                setTextAtt(subcats::credits::repos_page_link_text, "       Other My projects you can find at\nhttps://github.com/MinecraftSRDEV", 32, 60, 360, sf::Color::Blue);
                setTextAtt(subcats::credits::issules_page_link_text, "            Found a BUG? Report it here\nhttps://github.com/MinecraftSRDEV/SRLauncher/issues", 32, 60, 450, sf::Color::Blue);    

                setTextAtt(subcats::steamAccount::Profile_warning_text, "", 26, 130, 600);

                setTextAtt(subcats::steamAccount::profileOffline_status_text, "", 26, 320, 420);

                setTextAtt(subcats::steamAccount::profileAccountName_text, "", 26, 320, 450);

                setTextAtt(subcats::steamAccount::profilePersonalName_text, "", 26, 320, 480);

                setTextAtt(subcats::steamAccount::profileUID_text, "", 26, 320, 510);

                setTextAtt(subcats::steamAccount::profilePresonal_data_warning_text, tr("IDS_TEXT_STEAMPROFILE_PERSONALDATAINFO"), 26, 135, 270, sf::Color::Red);            
            }
        }

        void manageTexts()
        {
            setTextAtt(list_mods_instance_text, tr("IDS_TEXT_MNG_INSTINSTALLEDMODS"), 19, 0, 0);
            list_mods_instance_text.setPosition(130 + (280 - (list_mods_instance_text.getLocalBounds().width / 2)), 0);

            setTextAtt(list_mods_launcher_text, tr("IDS_TEXT_MNG_SRLINSTALLEDMODS"), 19, 0, 0);
            list_mods_launcher_text.setPosition((130 + 560) + ((10 + 280) - (list_mods_launcher_text.getLocalBounds().width / 2)), 0);

            setTextAtt(MNG_Instance_name_text, tr("IDS_TEXT_MNG_INSTNAME"), 26, 0, 0);

            setTextAtt(MNG_betterBuild_status, "", 26, 130, 520);

            setTextAtt(MNG_betterBuild_UID, "", 26, 130, 550);

            setTextAtt(tldr_text, tr("IDS_TEXT_MNG_TLDR"), 26, 130, 630, sf::Color::Red);

            setTextAtt(ManageDebug::assemblyDataText, "", 18, 840, 15);

            setTextAtt(ManageDebug::debugPatchStatusText, "", 26, 130, 55);

            setTextAtt(ManageDebug::selectedFrameworkLabelText, ".netFramework", 26, 520, 55);

            setTextAtt(bbw_tittle_text, "", 26, 0, 0);

            setTextAtt(vsc_text, "", 26, 0, 0);

            setTextAtt(msc_text, "", 26, 0, 0);
        }
    }
}

void setRuntimeTexts()
{
    {
        using namespace subfunctions::setRuntimeTextsFunctions;

        mainCategoryBottomBar();

        instancesCategoryBody();

        settingsTexts();

        manageTexts();
    }
    
    setTextAtt(bbw_tittle_text, "", 26, 0, 0);

    setTextAtt(version_description_text, "", 26, 10, 10);

    setTextAtt(instance_ver_info_text, "", 20, 1005, 10);

    setTextAtt(CreateInstanceUI::isntance_will_be_created_in_text, "", 20, 10, 745);

    setTextAtt(editInstanceSource, "", 20, 10, 745);

    setTextAtt(CreateInstanceUI::instance_file_separation_text, tr("IDS_TEXT_NEWINST_SEPARATIONINFO"), 26, 10, 530);
    
    setTextAtt(InstanceIconBar::icon_bar_text, tr("IDS_TEXT_NEWINST_SELECTICON"), 26, 10, 300);
}

void setShapesAttributes()
{
    SettingsElemets::subcats::steamAccount::profileIcon.setPosition(sf::Vector2f(130, 410));

    setRectAtt(MainpageElements::playbar::progress_bg, 0, 780, 1280, 20, ColorPalete::Palete[theme_selected][ColorPalete::inactive]);

    setRectAtt(MainpageElements::playbar::progress_moveing, -70, 780, 70, 20, ColorPalete::Palete[theme_selected][ColorPalete::checkbox_inactive]);

    setRectAtt(MainpageElements::debuger::working, 10, 670, 10, 10, sf::Color::Red);

    setRectAtt(instanceModsMouseWorkingBox, 126, 5, 565, 790, sf::Color::Transparent);

    setRectAtt(launcherModsMouseWorkingBox, 695, 5, 565, 790, sf::Color::Transparent);

    setRectAtt(instancesScrollingArea, 0, 84, 1280, 629, sf::Color::Transparent);

    setRectAtt(MainpageElements::lastPlayed::mouseBox, 20, 45, 680, 400, sf::Color::Transparent);

    setRectAtt(MainpageElements::console::mouseBox, 20, 450, 1240, 240, sf::Color::Transparent);

    MainpageElements::playbar::downloadingProgress.create(0, 780, sf::Vector2f(1280, 20), ProgressBar::Mode::Static, 100.0f);

    setRectAtt(InstanceIconBar::selectedBG, 50, 330, 80, 80, sf::Color(255, 255, 20));

    setRectAtt(InstanceslistElements::utilitiesMenu::body, -220, 55, 220, 629, ColorPalete::Palete[theme_selected][ColorPalete::semitransparrent]);
    InstanceslistElements::utilitiesMenu::body.setOutlineThickness(1);
    InstanceslistElements::utilitiesMenu::body.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::outline]);
}