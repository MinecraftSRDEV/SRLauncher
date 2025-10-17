void executeCategories(sf::Vector2f mouse)
{
    MainCategory_button.update(mouse);
    InstancesCategory_button.update(mouse);
    SettingsCategory_button.update(mouse);
    VersionsCategory_button.update(mouse);
}

void executeSubcategories(sf::Vector2f mouse)
{
    using namespace SettingsElemets::subcatsBar;
    generalCat_button.update(mouse);
    profileCat_button.update(mouse);
    downloadingCat_button.update(mouse);
    updatesCat_button.update(mouse);
    debuggingCat_button.update(mouse);
    creditsCat_button.update(mouse);
    licencesCat_button.update(mouse);
}

void mouse_left()
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (UI_current == UiPages::MainMenu)
    {
        executeCategories(mouse);

        if (mounted_instance != UNMOUNTED_INSTANCE)
        {
            MainpageElements::playbar::launchGameButton.update(mouse);
            MainpageElements::playbar::infoText.setPosition(sf::Vector2f(10, 725));
        }
        else
        {
            MainpageElements::playbar::infoText.setPosition(sf::Vector2f((1280 / 2) - (MainpageElements::playbar::infoText.getLocalBounds().width / 2), 725));
        }

        MainpageElements::console::clearButton.update(mouse);

        if (display_guard_window == true)
        {
            MainpageElements::GuardBox.update(mouse);
        }

        if (!miniInstanceList::dataLoading)
        {
            if (miniInstancesListMap.size() > 0)
            {
                for (const auto& itr : miniInstancesListMap)
                {
                    miniInstancesListMap[itr.first].update(mouse);

                    if (miniInstancesListMap[itr.first].getMountButtonHitbox().contains(mouse))
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            if (is_mouse_pressed == false)
                            {
                                is_mouse_pressed = true;
                                mount_function(miniInstancesListMap[itr.first].getID());
                            }
                        }
                        else
                        {
                            is_mouse_pressed = false;
                        }
                    }
                }
            }
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
                        instance_manage(pair.first, ManageCategories::MNG_MAIN_PAGE);
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
        
        using namespace SettingsElemets::subcats;

        if (options_ui == SettingsCategories::MAIN_PAGE)
        {
            if (mounted_instance != UNMOUNTED_INSTANCE)
            {
                general::steam_path_textbox.setReadOnlyMode(true);
                general::instances_path_textbox.setReadOnlyMode(true);
                general::steam_path_getfolder_button.setBlockState(true);
                general::instances_path_getfolder_button.setBlockState(true);

                // mount_only_data_checkbox.setBlockState(false);
            }
            else
            {
                general::steam_path_textbox.setReadOnlyMode(false);
                general::instances_path_textbox.setReadOnlyMode(false);
                general::steam_path_getfolder_button.setBlockState(false);
                general::instances_path_getfolder_button.setBlockState(false);

                // mount_only_data_checkbox.setBlockState(true);
            }

            general::steam_path_textbox.update(mouse);
            general::instances_path_textbox.update(mouse);
            general::steam_path_getfolder_button.update(mouse);
            general::instances_path_getfolder_button.update(mouse);

            general::Show_prereleases_checkbox.update(mouse);
            general::Save_logs_files_checkbox.update(mouse);
            general::Colored_logs_checkbox.update(mouse);

            general::do_not_show_warnings_checkbox.update(mouse);
            general::use_secure_ipc_checkbox.update(mouse);
            general::mount_only_data_checkbox.update(mouse);

            general::mount_only_data_checkbox.setBlockState(true);

            SettingsElemets::bottomBar::RestoreSettings_button.update(mouse);
            SettingsElemets::bottomBar::SaveConfig_button.update(mouse);

            general::theme_list_ddl.update(mouse);
            general::languages_list_ddl.update(mouse);

            general::SRL_background_img_path_textbox.update(mouse);
            general::SRL_background_img_path_getfolder_button.update(mouse);
        }
        if (options_ui == SettingsCategories::PROFILE_PAGE)
        {
            steamAccount::profileName_textbox.update(mouse);
            steamAccount::profilePassword_textbox.update(mouse);
            steamAccount::save_profile_button.update(mouse);
        }
        if (options_ui == SettingsCategories::DOWNLOADING_PAGE)
        {
            if (downloader_selected == steamcmd)
            {
                SettingsElemets::subcats::downloading::steamcmd_path_textbox.setReadOnlyMode(false);
                SettingsElemets::subcats::downloading::steamcmd_path_getfolder_button.setBlockState(false);
            }
            else
            {
                SettingsElemets::subcats::downloading::steamcmd_path_textbox.setReadOnlyMode(true);
                SettingsElemets::subcats::downloading::steamcmd_path_getfolder_button.setBlockState(true);
            }

            SettingsElemets::subcats::downloading::steamcmd_path_textbox.update(mouse);
            SettingsElemets::subcats::downloading::steamcmd_path_getfolder_button.update(mouse);
            SettingsElemets::subcats::downloading::automatically_run_downloaded_instances_checkbox.update(mouse);
            SettingsElemets::subcats::downloading::downloaders_ddl.update(mouse);

            SettingsElemets::bottomBar::RestoreSettings_button.update(mouse);
            SettingsElemets::bottomBar::SaveConfig_button.update(mouse);
        }
        if (options_ui == SettingsCategories::UPDATES_PAGE)
        {
            SettingsElemets::subcats::updates::check_for_update_button.update(mouse);
            SettingsElemets::subcats::updates::autocheck_for_update_checkbox.update(mouse);

            SettingsElemets::bottomBar::RestoreSettings_button.update(mouse);
            SettingsElemets::bottomBar::SaveConfig_button.update(mouse);
        }
        if (options_ui == SettingsCategories::DEBUGGING_PAGE)
        {
            SettingsElemets::subcats::debug::debuggingEnabledCheckbox.update(mouse);

            bool state = SettingsElemets::subcats::debug::debuggingEnabledCheckbox.getState();
            state = !state;

            SettingsElemets::subcats::debug::saveDebugLogsToOtherFileCheckbox.setBlockState(state);
            SettingsElemets::subcats::debug::printDebugLogsCheckbox.setBlockState(state);
            SettingsElemets::subcats::debug::comunicationDelayTextbox.setReadOnlyMode(state);
            SettingsElemets::subcats::debug::comunicationPipeBufferSizeTextbox.setReadOnlyMode(state);
            SettingsElemets::subcats::debug::forcePipeCloseButton.setBlockState(state);
            SettingsElemets::subcats::debug::killInstanceButton.setBlockState(state);
            SettingsElemets::subcats::debug::saveLogFileButton.setBlockState(state);
            SettingsElemets::subcats::debug::acceptInfoCheckbox.setBlockState(state);
            SettingsElemets::subcats::debug::acceptWarningCheckbox.setBlockState(state);
            SettingsElemets::subcats::debug::acceptErrorCheckbox.setBlockState(state);
            SettingsElemets::subcats::debug::acceptExceptionCheckbox.setBlockState(state);

            bool state2 = SettingsElemets::subcats::debug::printDebugLogsCheckbox.getState();
            state2 = !state2;

            SettingsElemets::subcats::debug::acceptInfoCheckbox.setBlockState(state2);
            SettingsElemets::subcats::debug::acceptWarningCheckbox.setBlockState(state2);
            SettingsElemets::subcats::debug::acceptErrorCheckbox.setBlockState(state2);
            SettingsElemets::subcats::debug::acceptExceptionCheckbox.setBlockState(state2);

            if (state == false)
            {
                SettingsElemets::subcats::debug::saveDebugLogsToOtherFileCheckbox.update(mouse);
                SettingsElemets::subcats::debug::printDebugLogsCheckbox.update(mouse);
                SettingsElemets::subcats::debug::comunicationDelayTextbox.update(mouse);
                SettingsElemets::subcats::debug::comunicationPipeBufferSizeTextbox.update(mouse);
                SettingsElemets::subcats::debug::forcePipeCloseButton.update(mouse);
                SettingsElemets::subcats::debug::killInstanceButton.update(mouse);
                SettingsElemets::subcats::debug::saveLogFileButton.update(mouse);

                acceptInfoLogs = SettingsElemets::subcats::debug::acceptInfoCheckbox.getState();
                acceptWarningLogs = SettingsElemets::subcats::debug::acceptWarningCheckbox.getState();
                acceptErrorLogs = SettingsElemets::subcats::debug::acceptErrorCheckbox.getState();
                acceptExceptionLogs = SettingsElemets::subcats::debug::acceptExceptionCheckbox.getState();
            }

            SettingsElemets::subcats::debug::acceptInfoCheckbox.update(mouse);
            SettingsElemets::subcats::debug::acceptWarningCheckbox.update(mouse);
            SettingsElemets::subcats::debug::acceptErrorCheckbox.update(mouse);
            SettingsElemets::subcats::debug::acceptExceptionCheckbox.update(mouse);

            SettingsElemets::bottomBar::RestoreSettings_button.update(mouse);
            SettingsElemets::bottomBar::SaveConfig_button.update(mouse);
        }
        if (options_ui == SettingsCategories::CREDITS_PAGE)
        {
            if (SettingsElemets::subcats::credits::github_page_link_text.getGlobalBounds().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        openInBrowser(SettingsElemets::subcats::credits::github_page_link_text.getString());
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }
            if (SettingsElemets::subcats::credits::repos_page_link_text.getGlobalBounds().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        openInBrowser(SettingsElemets::subcats::credits::repos_page_link_text.getString());
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }
            if (SettingsElemets::subcats::credits::issules_page_link_text.getGlobalBounds().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        openInBrowser(SettingsElemets::subcats::credits::issules_page_link_text.getString());
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }
        }
    }

    if (UI_current == UiPages::ManageMenu)
    {
        ManageSubcatListUI::informations_button.update(mouse);
        ManageSubcatListUI::vanilla_saves_button.update(mouse);
        ManageSubcatListUI::betterbuild_saves_button.update(mouse);
        ManageSubcatListUI::betterbuild_world_button.update(mouse);
        ManageSubcatListUI::backups_button.update(mouse);
        ManageSubcatListUI::mods_button.update(mouse);
        ManageSubcatListUI::main_back_button.update(mouse);
        ManageSubcatListUI::debug_button.update(mouse);

        switch(manage_ui)
        {
            case MNG_MAIN_PAGE:
            {
                if (instancesLoader::instanceDataLoading == false)
                {
                    MNG_Instance_saves_text.update(mouse);
                    MNG_instance_installed_mods_text.update(mouse);
                    MNG_instance_mods_saves_text.update(mouse);
                    MNG_instance_mods_launcher_text.update(mouse);    
                }
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
            case BETTERBUILD_SAVES:
            {
                for (const auto& pair : betterbuildsaves_list)
                {
                    betterbuildsaves_list[pair.first].update(mouse);
                }
                break;
            }
            case MODS_PAGE:
            {
                for (const auto& pair : InstanceMods_list)
                {
                    InstanceMods_list[pair.first].update(mouse);
                }
                for (const auto& pair : LauncherMods_list)
                {
                    LauncherMods_list[pair.first].update(mouse);
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
            case ManageCategories::DEBUG_PAGE:
            {
                ManageDebug::debugPatchButton.update(mouse);
                ManageDebug::selectedFramework.update(mouse);
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