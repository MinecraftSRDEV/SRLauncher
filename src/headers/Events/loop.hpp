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
            if (instancesListLoading == false)
            {
                scrollInstancesList(event, mouse_pos);
            }
        }

        if (UI_current == UiPages::MainMenu)
        {
            console.handleEvent(event);

            if (display_guard_window == true)
            {
                GuardBox.event(event);
            }
        }

        if (UI_current == UiPages::ManageMenu)
        {
            switch(manage_ui)
            {
                case BETTERBUILD_WORLDS:
                {
                    if (instanceDataLoading == false)
                    {
                        scrollManageBbw(event, mouse_pos);    
                    }
                    break;
                }
                case VANILLA_SAVES:
                {
                    if (instanceDataLoading == false)
                    {
                        scrollManageVs(event, mouse_pos);    
                    }
                    break;
                }
            }
        }

        if (UI_current == UiPages::SettingsMenu)
        {
            if (options_ui == SettingsCategories::MAIN_PAGE)
            {
                SlimeRancher_steam_path_textbox.handleEvent(event);
                SlimeRancher_instances_path_textbox.handleEvent(event);
                steamcmd_path_textbox.handleEvent(event);
            }
            if (options_ui == SettingsCategories::DEBUGGING_PAGE)
            {
                if (debuggingEnabledCheckbox.getState() == true)
                {
                    comunicationDelayTextbox.handleEvent(event);
                    comunicationPipeBufferSizeTextbox.handleEvent(event);
                }
            }
            if (options_ui == SettingsCategories::PROFILE_PAGE)
            {
                SteamProfile_name_textbox.handleEvent(event);
                SteamProfile_password_textbox.handleEvent(event);
            }
            if (options_ui == SettingsCategories::LICENCES_PAGE)
            {
                LicencesUI::licenseField.handleEvent(event);
            }
        }

        if (UI_current == UiPages::VersionsList)
        {
            scrollPatchNotes(event, mouse_pos);
        }
    }
}