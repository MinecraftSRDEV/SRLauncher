void events_loop()
{
    sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                close_launcher();
                break;
            }

            case sf::Event::MouseWheelMoved:
            {
                scrollVersionDescription(event, mouse_pos);

                break;
            }
        }

        if (UI_current == UiPages::NewInstanceMenu or UI_current == UiPages::ImportInstanceMenu or UI_current == UiPages::EditInstanceMenu)
        {
            if (versions_list_ddl.getState() == true)
            {
                versions_list_ddl.scrollEvent(event);    
            }

            scrollIconBar(event, mouse_pos);
        }

        if (versions_list_ddl.getState() == false)
        {
            new_instance_name_textbox.handleEvent(event);

            import_instance_name_textbox.handleEvent(event);
            import_instance_path_textbox.handleEvent(event);
        }

        if (UI_current == UiPages::InstancesMenu)
        {
            if (instancesLoader::instancesListLoading == false)
            {
                if (instancesScrollingArea.getGlobalBounds().contains(mouse_pos))
                scrollInstancesList(event, mouse_pos);
            }
        }

        if (UI_current == UiPages::MainMenu)
        {
            if (MainpageElements::console::mouseBox.getGlobalBounds().contains(mouse_pos))
            MainpageElements::console::console.handleEvent(event);

            if (display_guard_window == true)
            {
                MainpageElements::GuardBox.event(event);
            }
        }

        if (UI_current == UiPages::ManageMenu)
        {
            if (instancesLoader::instanceDataLoading == false)
            {
                switch(manage_ui)
                {
                    case BETTERBUILD_WORLDS:
                    {
                        scrollManageBbw(event, mouse_pos);    
                        break;
                    }
                    case VANILLA_SAVES:
                    {
                        scrollManageVs(event, mouse_pos);    
                        break;
                    }
                    case BETTERBUILD_SAVES:
                    {
                        scrollManageBbw(event, mouse_pos);
                        break;
                    }
                    case MODS_PAGE:
                    {
                        if (instanceModsMouseWorkingBox.getGlobalBounds().contains(mouse_pos))
                        scrollInstanceMods(event, mouse_pos);

                        if (launcherModsMouseWorkingBox.getGlobalBounds().contains(mouse_pos))
                        scrollLauncherMods(event, mouse_pos);
                    }
                }
            }
        }

        if (UI_current == UiPages::SettingsMenu)
        {
            if (options_ui == SettingsCategories::MAIN_PAGE)
            {
                SettingsElemets::subcats::general::steam_path_textbox.handleEvent(event);
                SettingsElemets::subcats::general::instances_path_textbox.handleEvent(event);
                SettingsElemets::subcats::general::SRL_background_img_path_textbox.handleEvent(event);
            }
            if (options_ui == SettingsCategories::DOWNLOADING_PAGE)
            {
                SettingsElemets::subcats::downloading::steamcmd_path_textbox.handleEvent(event);
            }
            if (options_ui == SettingsCategories::DEBUGGING_PAGE)
            {
                if (SettingsElemets::subcats::debug::debuggingEnabledCheckbox.getState() == true)
                {
                    SettingsElemets::subcats::debug::comunicationDelayTextbox.handleEvent(event);
                    SettingsElemets::subcats::debug::comunicationPipeBufferSizeTextbox.handleEvent(event);
                }
            }
            if (options_ui == SettingsCategories::PROFILE_PAGE)
            {
                SettingsElemets::subcats::steamAccount::profileName_textbox.handleEvent(event);
                SettingsElemets::subcats::steamAccount::profilePassword_textbox.handleEvent(event);
            }
            if (options_ui == SettingsCategories::LICENCES_PAGE)
            {
                SettingsElemets::subcats::licences::licenseField.handleEvent(event);
            }
        }

        if (UI_current == UiPages::VersionsList)
        {
            scrollPatchNotes(event, mouse_pos);
        }
    }
}