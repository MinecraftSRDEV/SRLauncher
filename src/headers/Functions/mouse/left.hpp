void executeCategories(sf::Vector2f mouse)
{
    MainCategory_button.update(mouse);
    InstancesCategory_button.update(mouse);
    SettingsCategory_button.update(mouse);
    SavesToolCategory_button.update(mouse);
}

void executeSubcategories(sf::Vector2f mouse)
{
    Subcat_settings_main_button.update(mouse);
    Subcat_settings_progile_button.update(mouse);
    Subcat_settings_versions_button.update(mouse);
    Subcat_settings_credits_button.update(mouse);
}

void mouse_left()
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (UI_current == UI_PAGES::MainMenu)
    {
        executeCategories(mouse);

        launch_last_instance_button.update(mouse);
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
            SlimeRancher_steam_path_textbox.update();
            SlimeRancher_instances_path_textbox.update();
            SlimeRancher_steam_path_getfolder_button.update(mouse);
            SlimeRancher_instances_path_getfolder_button.update(mouse);
            steamcmd_path_textbox.update();
            steamcmd_path_getfolder_button.update(mouse);

            Show_older_instances_checkbox.update(mouse);
            Save_logs_files_checkbox.update(mouse);
            Colored_logs_checkbox.update(mouse);

            automatically_run_downloaded_instances_checkbox.update(mouse);
            do_not_show_warnings_checkbox.update(mouse);

            RestoreSettings_button.update(mouse);
            SaveConfig_button.update(mouse);
        }
        if (options_ui == SETTIGNS_CATEGORIES::PROFILE_PAGE)
        {
            SteamProfile_name_textbox.update();
            // SteamProfile_password_textbox.update();
            save_profile_button.update(mouse);
            login_manualy_checkbox.update(mouse);
        }
    }

    if (UI_current == UI_PAGES::DataToolsMenu)
    {
        executeCategories(mouse);
    }

    if (UI_current == UI_PAGES::NewInstanceMenu)
    {
        versions_list.update(mouse);

        if (versions_list.getState() == false)
        {
            new_instance_name_textbox.update();
            create_button.update(mouse);
            instance_creation_cancel.update(mouse);    
        }   
    }

    if (UI_current == UI_PAGES::ImportInstanceMenu)
    {
        if (versions_list.getState() == false)
        {
            import_instance_name_textbox.update();
            import_instance_path_textbox.update();
            import_instance_path_browse_button.update(mouse);
            import_instance_confirm_button.update(mouse);
            import_instance_cancel_button.update(mouse);
        }
        versions_list.update(mouse);
    }
}