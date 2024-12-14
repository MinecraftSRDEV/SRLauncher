void executeCategories(sf::Vector2f mouse)
{
    MainCategory_button.update(mouse);
    InstancesCategory_button.update(mouse);
    SettingsCategory_button.update(mouse);
    VersionsCategory_button.update(mouse);
}

void executeSubcategories(sf::Vector2f mouse)
{
    Subcat_settings_main_button.update(mouse);
    Subcat_settings_progile_button.update(mouse);
    Subcat_settings_downloading_button.update(mouse);
    Subcat_settings_updates_button.update(mouse);
    Subcat_settings_debugging_button.update(mouse);
    Subcat_settings_credits_button.update(mouse);
    Subcat_settings_licences_button.update(mouse);
}

void mouse_left()
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (UI_current == UiPages::MainMenu)
    {
        executeCategories(mouse);

        if (mounted_instance != UNMOUNTED_INSTANCE)
        {
            launch_game_button.update(mouse);
            Mounted_instance_info_text.setPosition(sf::Vector2f(10, 725));
        }
        else
        {
            Mounted_instance_info_text.setPosition(sf::Vector2f((1280 / 2) - (Mounted_instance_info_text.getLocalBounds().width / 2), 725));
        }

        console_clear_button.update(mouse);

        if (display_guard_window == true)
        {
            GuardBox.update(mouse);
        }
    }

    if (UI_current == UiPages::InstancesMenu)
    {
        executeCategories(mouse);

        new_instance_button.update(mouse);
        import_instnace_button.update(mouse);

        for (const auto& pair : instances_list)
        {
            instances_list[pair.first].update(mouse);

            if (instances_list[pair.first].getMountButtonHitbox().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        mount_function(pair.first);
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }

            if (instances_list[pair.first].getEditButtonHitbox().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        edit_instance_function(pair.first);
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }

            if (instances_list[pair.first].getMenageButtonHitbox().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        instance_manage(pair.first);
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }

            if (instances_list[pair.first].getOpenGameFolderButtonHitbox().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        instance_open_game_folder(pair.first);
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }

            if (instances_list[pair.first].getOpenSavesFolderButtonHitbox().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        instnace_open_saves_folder(pair.first);
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }

            if (instances_list[pair.first].getRemoveButtonHitbox().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        remove_instnace_function(pair.first);
                        break;
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }
        }
    }

    if (UI_current == UiPages::SettingsMenu)
    {
        executeCategories(mouse);
        executeSubcategories(mouse);

        if (options_ui == SettingsCategories::MAIN_PAGE)
        {
            SlimeRancher_steam_path_textbox.update(mouse);
            SlimeRancher_instances_path_textbox.update(mouse);
            SlimeRancher_steam_path_getfolder_button.update(mouse);
            SlimeRancher_instances_path_getfolder_button.update(mouse);

            Show_prereleases_checkbox.update(mouse);
            Save_logs_files_checkbox.update(mouse);
            Colored_logs_checkbox.update(mouse);

            do_not_show_warnings_checkbox.update(mouse);
            use_secure_ipc_checkbox.update(mouse);

            RestoreSettings_button.update(mouse);
            SaveConfig_button.update(mouse);

            theme_list_ddl.update(mouse);

            if (mounted_instance != UNMOUNTED_INSTANCE)
            {
                SlimeRancher_steam_path_textbox.setReadOnlyMode(true);
                SlimeRancher_instances_path_textbox.setReadOnlyMode(true);
                SlimeRancher_steam_path_getfolder_button.setBlockState(true);
                SlimeRancher_instances_path_getfolder_button.setBlockState(true);
            }
            else
            {
                SlimeRancher_steam_path_textbox.setReadOnlyMode(false);
                SlimeRancher_instances_path_textbox.setReadOnlyMode(false);
                SlimeRancher_steam_path_getfolder_button.setBlockState(false);
                SlimeRancher_instances_path_getfolder_button.setBlockState(false);
            }
        }
        if (options_ui == SettingsCategories::PROFILE_PAGE)
        {
            SteamProfile_name_textbox.update(mouse);
            SteamProfile_password_textbox.update(mouse);
            save_profile_button.update(mouse);
        }
        if (options_ui == SettingsCategories::DOWNLOADING_PAGE)
        {
            steamcmd_path_textbox.update(mouse);
            steamcmd_path_getfolder_button.update(mouse);
            automatically_run_downloaded_instances_checkbox.update(mouse);
            downloaders_ddl.update(mouse);

            if (downloader_selected == steamcmd)
            {
                steamcmd_path_textbox.setReadOnlyMode(false);
                steamcmd_path_getfolder_button.setBlockState(false);
            }
            else
            {
                steamcmd_path_textbox.setReadOnlyMode(true);
                steamcmd_path_getfolder_button.setBlockState(true);
            }

            RestoreSettings_button.update(mouse);
            SaveConfig_button.update(mouse);
        }
        if (options_ui == SettingsCategories::UPDATES_PAGE)
        {
            check_for_update_button.update(mouse);
            autocheck_for_update_checkbox.update(mouse);

            RestoreSettings_button.update(mouse);
            SaveConfig_button.update(mouse);
        }
        if (options_ui == SettingsCategories::DEBUGGING_PAGE)
        {
            DebugSettingsUI::debuggingEnabledCheckbox.update(mouse);

            bool state = DebugSettingsUI::debuggingEnabledCheckbox.getState();
            state = !state;

            DebugSettingsUI::saveDebugLogsToOtherFileCheckbox.setBlockState(state);
            DebugSettingsUI::printDebugLogsCheckbox.setBlockState(state);
            DebugSettingsUI::comunicationDelayTextbox.setReadOnlyMode(state);
            DebugSettingsUI::comunicationPipeBufferSizeTextbox.setReadOnlyMode(state);
            DebugSettingsUI::forcePipeCloseButton.setBlockState(state);
            DebugSettingsUI::killInstanceButton.setBlockState(state);
            DebugSettingsUI::saveLogFileButton.setBlockState(state);
            DebugSettingsUI::acceptInfoCheckbox.setBlockState(state);
            DebugSettingsUI::acceptWarningCheckbox.setBlockState(state);
            DebugSettingsUI::acceptErrorCheckbox.setBlockState(state);
            DebugSettingsUI::acceptExceptionCheckbox.setBlockState(state);

            bool state2 = DebugSettingsUI::printDebugLogsCheckbox.getState();
            state2 = !state2;

            DebugSettingsUI::acceptInfoCheckbox.setBlockState(state2);
            DebugSettingsUI::acceptWarningCheckbox.setBlockState(state2);
            DebugSettingsUI::acceptErrorCheckbox.setBlockState(state2);
            DebugSettingsUI::acceptExceptionCheckbox.setBlockState(state2);

            DebugSettingsUI::acceptInfoCheckbox.setState(acceptInfoLogs);
            DebugSettingsUI::acceptWarningCheckbox.setState(acceptWarningLogs);
            DebugSettingsUI::acceptErrorCheckbox.setState(acceptErrorLogs);
            DebugSettingsUI::acceptExceptionCheckbox.setState(acceptExceptionLogs);

            if (state == false)
            {
                DebugSettingsUI::saveDebugLogsToOtherFileCheckbox.update(mouse);
                DebugSettingsUI::printDebugLogsCheckbox.update(mouse);
                DebugSettingsUI::comunicationDelayTextbox.update(mouse);
                DebugSettingsUI::comunicationPipeBufferSizeTextbox.update(mouse);
                DebugSettingsUI::forcePipeCloseButton.update(mouse);
                DebugSettingsUI::killInstanceButton.update(mouse);
                DebugSettingsUI::saveLogFileButton.update(mouse);

                acceptInfoLogs = DebugSettingsUI::acceptInfoCheckbox.getState();
                acceptWarningLogs = DebugSettingsUI::acceptWarningCheckbox.getState();
                acceptErrorLogs = DebugSettingsUI::acceptErrorCheckbox.getState();
                acceptExceptionLogs = DebugSettingsUI::acceptExceptionCheckbox.getState();
            }

            DebugSettingsUI::acceptInfoCheckbox.update(mouse);
            DebugSettingsUI::acceptWarningCheckbox.update(mouse);
            DebugSettingsUI::acceptErrorCheckbox.update(mouse);
            DebugSettingsUI::acceptExceptionCheckbox.update(mouse);

            RestoreSettings_button.update(mouse);
            SaveConfig_button.update(mouse);
        }
    }

    if (UI_current == UiPages::ManageMenu)
    {
        manage_vanilla_saves_button.update(mouse);
        manage_betterbuild_saves_button.update(mouse);
        manage_betterbuild_world_button.update(mouse);
        manage_backups_button.update(mouse);
        manage_mods_button.update(mouse);
        manage_main_back_button.update(mouse);

        switch(manage_ui)
        {
            case MNG_MAIN_PAGE:
            {
                break;
            }
            case VANILLA_SAVES:
            {
                for (const auto& pair : vanillasaves_list)
                {
                    vanillasaves_list[pair.first].update(mouse);
                }
                break;
            }
            case BETTERBUILD_WORLDS:
            {
                for (const auto& pair : betterbuildworlds_list)
                {
                    betterbuildworlds_list[pair.first].update(mouse);
                }
                break;
            }
            case MODS_PAGE:
            {
                for (const auto& pair : InstanceMods_list)
                {
                    InstanceMods_list[pair.first].update(mouse);
                }
                break;
            }
            case BACKUPS:
            {
                for (const auto& pair : Backups_list)
                {
                    Backups_list[pair.first].update(mouse);
                }
                break;
            }
        }
    }

    if (UI_current == UiPages::VersionDescriptionMenu)
    {
        version_back_button.update(mouse);
    }

    if (UI_current == UiPages::VersionsList)
    {
        executeCategories(mouse);

        for (const auto& pair : versions_pachnotes_list)
        {
            versions_pachnotes_list[pair.first].update(mouse);
            if (versions_pachnotes_list[pair.first].getPosition().y > 65)
            {
                if (versions_pachnotes_list[pair.first].hitbox().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    version_description_text.setString(versions_pachnotes_list[pair.first].getDescription());
                    version_description_text.setPosition(10, 10);
                    UI_current = UiPages::VersionDescriptionMenu;
                }    
            }
        }
    }

    if (UI_current == UiPages::NewInstanceMenu)
    {
        versions_list_ddl.update(mouse);

        if (versions_list_ddl.getState() == false)
        {
            new_instance_name_textbox.update(mouse);
            create_button.update(mouse);
            instance_creation_cancel.update(mouse);

            InstanceIconBar::next_button.update(mouse);

            updateInstanceInfo();
        }

        if (graphics_preset_ddl.getState() == false)
        {
            InstanceIconBar::prev_button.update(mouse);
        }

        automount_checkbox.update(mouse);
        create_with_graphics_preset_checkbox.update(mouse);
        graphics_preset_ddl.update(mouse);

        if (create_with_graphics_preset_checkbox.getState() == true)
        {
            graphics_preset_ddl.setBlockState(false);
        }
        else
        {
            graphics_preset_ddl.setBlockState(true);
        }
    }

    if (UI_current == UiPages::EditInstanceMenu)
    {
        versions_list_ddl.update(mouse);

        if (versions_list_ddl.getState() == false)
        {
            new_instance_name_textbox.update(mouse);
            saveEditedButton.update(mouse);
            instance_creation_cancel.update(mouse);    

            InstanceIconBar::prev_button.update(mouse);
            InstanceIconBar::next_button.update(mouse);

            updateInstanceInfo();
        }   
    }

    if (UI_current == UiPages::ImportInstanceMenu)
    {
        if (versions_list_ddl.getState() == false)
        {
            import_instance_name_textbox.update(mouse);
            import_instance_path_textbox.update(mouse);
            import_instance_path_browse_button.update(mouse);
            import_instance_confirm_button.update(mouse);
            import_instance_cancel_button.update(mouse);
            InstanceIconBar::prev_button.update(mouse);
            InstanceIconBar::next_button.update(mouse);

            updateInstanceInfo();
        }
        versions_list_ddl.update(mouse);
    }

    devUiView.update(mouse, font);
}