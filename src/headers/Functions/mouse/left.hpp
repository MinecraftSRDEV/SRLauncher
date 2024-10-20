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
    Subcat_settings_updates_button.update(mouse);
    Subcat_settings_credits_button.update(mouse);
}

void mouse_left()
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (UI_current == UI_PAGES::MainMenu)
    {
        executeCategories(mouse);

        launch_last_instance_button.update(mouse);

        console_clear_button.update(mouse);

        if (display_guard_window == true)
        {
            GuardBox.update(mouse);
        }
    }

    if (UI_current == UI_PAGES::InstancesMenu)
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

    if (UI_current == UI_PAGES::SettingsMenu)
    {
        executeCategories(mouse);
        executeSubcategories(mouse);

        if (options_ui == SETTIGNS_CATEGORIES::MAIN_PAGE)
        {
            SlimeRancher_steam_path_textbox.update(mouse);
            SlimeRancher_instances_path_textbox.update(mouse);
            SlimeRancher_steam_path_getfolder_button.update(mouse);
            SlimeRancher_instances_path_getfolder_button.update(mouse);
            steamcmd_path_textbox.update(mouse);
            steamcmd_path_getfolder_button.update(mouse);

            Show_older_instances_checkbox.update(mouse);
            Save_logs_files_checkbox.update(mouse);
            Colored_logs_checkbox.update(mouse);

            automatically_run_downloaded_instances_checkbox.update(mouse);
            do_not_show_warnings_checkbox.update(mouse);

            RestoreSettings_button.update(mouse);
            SaveConfig_button.update(mouse);

            theme_list_ddl.update(mouse);
            downloaders_ddl.update(mouse);
        }
        if (options_ui == SETTIGNS_CATEGORIES::PROFILE_PAGE)
        {
            SteamProfile_name_textbox.update(mouse);
            SteamProfile_password_textbox.update(mouse);
            save_profile_button.update(mouse);
        }
        if (options_ui == SETTIGNS_CATEGORIES::UPDATES_PAGE)
        {
            check_for_update_button.update(mouse);
            autocheck_for_update_checkbox.update(mouse);

            RestoreSettings_button.update(mouse);
            SaveConfig_button.update(mouse);
        }
    }

    if (UI_current == UI_PAGES::ManageMenu)
    {
        manage_vanilla_saves_button.update(mouse);
        manage_mod_saves_button.update(mouse);
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
        }
    }

    if (UI_current == UI_PAGES::VersionDescriptionMenu)
    {
        version_back_button.update(mouse);
    }

    if (UI_current == UI_PAGES::VersionsList)
    {
        executeCategories(mouse);

        for (const auto& pair : versions_pachnotes_list)
        {
            if (Show_older_instances_checkbox.getState() == true and versions_map[versions_pachnotes_list[pair.first].getVersion()].version_type != "pre_release")
            {
                versions_pachnotes_list[pair.first].update(mouse);
                if (versions_pachnotes_list[pair.first].getPosition().y > 65)
                {
                    if (versions_pachnotes_list[pair.first].hitbox().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        version_description_text.setString(versions_pachnotes_list[pair.first].getDescription());
                        version_description_text.setPosition(10, 10);
                        UI_current = UI_PAGES::VersionDescriptionMenu;
                    }    
                }
            }
        }
    }

    if (UI_current == UI_PAGES::NewInstanceMenu)
    {
        versions_list.update(mouse);

        if (versions_list.getState() == false)
        {
            new_instance_name_textbox.update(mouse);
            create_button.update(mouse);
            instance_creation_cancel.update(mouse);    
        }   
    }

    if (UI_current == UI_PAGES::ImportInstanceMenu)
    {
        if (versions_list.getState() == false)
        {
            import_instance_name_textbox.update(mouse);
            import_instance_path_textbox.update(mouse);
            import_instance_path_browse_button.update(mouse);
            import_instance_confirm_button.update(mouse);
            import_instance_cancel_button.update(mouse);
        }
        versions_list.update(mouse);
    }
}