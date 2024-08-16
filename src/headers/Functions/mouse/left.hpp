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
}

bool unmount_funtcion()
{
    if (!mounted_instance.empty())
    {
        if (mounted_instance != "Unmounted")
        {
            steam_game_dir = SlimeRancher_steam_path_textbox.getText();
            fs::path steam_dir = steam_game_dir;
            try
            {
                fs::rename(steam_dir / "Slime Rancher", fs::path(instances_dir) / ("Slime Rancher_" + mounted_instance));
                mounted_instance = "Unmounted";
                Mounted_instance_info_text.setString("No instance mounted");
                update_config_file();
                log_message("Instance unmounted", LOG_TYPES::LOG_INFO);
                return true;
            }
            catch
            (fs::filesystem_error& e)
            {
                log_message("Cannot unmount instance", LOG_TYPES::LOG_ERROR);
                std::cerr << "Error: " << e.what() << std::endl;
                return false;
            }
        }
    }
    return false;
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
                        if (mounted_instance == instances_list[pair.first].getID())
                        {
                            unmount_funtcion();
                            instances_stat_refresh();
                        }
                        else
                        {
                            unmount_funtcion();
                            mounted_instance = instances_list[pair.first].getID();
                            Mounted_instance_info_text.setString(mounted_instance);

                            steam_game_dir = SlimeRancher_steam_path_textbox.getText();
                            fs::path steam_dir = steam_game_dir;
                            fs::path game_dir = steam_dir / ("Slime Rancher_" + mounted_instance);

                            if (fs::exists(steam_dir / "Slime Rancher") && fs::is_directory(steam_dir / "Slime Rancher"))
                            {
                                log_message("Cannot overwrite current instance", LOG_TYPES::LOG_ERROR);
                            }
                            else
                            {
                                fs::rename(fs::path(instances_dir) / ("Slime Rancher_" + mounted_instance), steam_dir / "Slime Rancher");
                                log_message("Mounted instance: " + instances_list[pair.first].getID() + "Version: " + instances_list[pair.first].getVer(), LOG_TYPES::LOG_INFO);
                                update_config_file();
                                instances_stat_refresh();
                            }
                        }
                        
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
                        if (mounted_instance != "Unmounted")
                        {
                            unmount_funtcion();
                            instances_stat_refresh();
                        }

                        // mounted_instance = instances_list[pair.first].getID();

                        // steam_game_dir = SlimeRancher_steam_path_textbox.getText();
                        // fs::path steam_dir = steam_game_dir;
                        // fs::path game_dir = steam_dir / ("Slime Rancher_" + mounted_instance);

                        // if (fs::exists(steam_dir / "Slime Rancher") && fs::is_directory(steam_dir / "Slime Rancher"))
                        // {
                        //     std::cout << "Cannot overwrite current instance" << std::endl;
                        // }
                        // else
                        // {
                        //     fs::rename(fs::path(instances_dir) / ("Slime Rancher_" + mounted_instance), steam_dir / "Slime Rancher");
                        //     std::cout << "Mounted instance: " << instances_list[pair.first].getID() << "Version: " << instances_list[pair.first].getVer() << std::endl;
                        //     update_config_file();
                        //     instances_stat_refresh();
                        // }
                    }
                }
                else
                {
                    is_mouse_pressed = false;
                }
            }

            if (instances_list[pair.first].getOpenFolderButtonHitbox().contains(mouse))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (is_mouse_pressed == false)
                    {
                        is_mouse_pressed = true;
                        std::string command = "explorer ";
                        fs::path path;
                        if (mounted_instance != "Unmounted")
                        {
                            if (mounted_instance == instances_list[pair.first].getID())
                            {
                                path = steam_game_dir + "\\Slime Rancher";
                            }
                            else
                            {
                                path = (instances_dir + "\\Slime Rancher_" + instances_list[pair.first].getID());
                            }
                        }
                        else
                        {
                            path = (instances_dir + "\\Slime Rancher_" + instances_list[pair.first].getID());
                        }

                        if (check_directory_exists(path) == true)
                        {
                            command += path.string();
                            command = reduceBackslashes(command);
                            log_message("Executing command: " + command, LOG_TYPES::LOG_INFO);
                            WinExec(command.c_str(), SW_SHOWDEFAULT);
                        }
                        else
                        {
                            log_message("Directory \"" + path.string() + "\" not found", LOG_TYPES::LOG_ERROR);
                        }
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

            SaveConfig_button.update(mouse);
        }
        if (options_ui == SETTIGNS_CATEGORIES::PROFILE_PAGE)
        {
            SteamProfile_name_textbox.update();
            SteamProfile_password_textbox.update();
            save_profile_button.update(mouse);
            // login_manualy_checkbox.update(mouse);
        }
    }

    if (UI_current == UI_PAGES::DataToolsMenu)
    {
        executeCategories(mouse);
    }

    if (UI_current == UI_PAGES::NewInstanceMenu)
    {
        versions_list.update(mouse);
        new_instance_name_textbox.update();
        create_button.update(mouse);
        instance_creation_cancel.update(mouse);
    }
}