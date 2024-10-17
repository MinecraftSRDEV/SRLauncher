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

            case sf::Event::GainedFocus:
            {
                window_actived = true;
                break;
            }

            case sf::Event::LostFocus:
            {
                window_actived = true;
                break;
            }

            case sf::Event::MouseWheelMoved:
            {
                if (UI_current == UI_PAGES::VersionDescriptionMenu)
                {
                    int mouse_scroll = event.mouseWheel.delta;

                    if (mouse_scroll > 0)
                    {
                        int mp = event.mouseWheel.delta;
                        while (mp > 0)
                        {
                            if (version_description_text.getPosition().y < 10)    
                            {
                                version_description_text.setPosition(version_description_text.getPosition().x, version_description_text.getPosition().y + 50);
                            }  
                            mp--;
                        }
                    }
                    else
                    {
                        int mp = event.mouseWheel.delta;
                        while (mp < 0)
                        {
                            if (version_description_text.getPosition().y + (version_description_text.getGlobalBounds().height - 50) > 700)
                            {
                                version_description_text.setPosition(version_description_text.getPosition().x, version_description_text.getPosition().y - 50);
                            }
                            mp++;
                        }
                    }
                }

                break;
            }
        }

        if (UI_current == UI_PAGES::NewInstanceMenu)
        {
            versions_list.scrollEvent(event);
        }

        if (UI_current == UI_PAGES::ImportInstanceMenu)
        {
            versions_list.scrollEvent(event);
        }

        if (versions_list.getState() == false)
        {
            new_instance_name_textbox.handleEvent(event);

            import_instance_name_textbox.handleEvent(event);
            import_instance_path_textbox.handleEvent(event);
        }

        if (UI_current == UI_PAGES::InstancesMenu)
        {
            if (instancesListLoading == false)
            {
                if (instances_list.size() > 0)
                {
                    instance_list_b = instances_list_iterations.begin()->second;
                    auto last = std::prev(instances_list_iterations.end());
                    instance_list_l = last->second;

                    if (event.type == sf::Event::MouseWheelMoved)
                    {
                        int mouse_scroll = event.mouseWheel.delta;

                        if (mouse_scroll > 0)
                        {
                            int mp = event.mouseWheel.delta;
                            while (mp > 0)
                            {
                                if (instances_list[instance_list_b].getPosition().y < 85)
                                {
                                    for (const auto& pair : instances_list_iterations)
                                    {
                                        instances_list[pair.second].changePosition(instances_list[pair.second].getPosition().x, instances_list[pair.second].getPosition().y + 85);
                                    }
                                } 
                                mp--;
                            }
                        }
                        else
                        {
                            int mp = event.mouseWheel.delta;
                            while (mp < 0)
                            {
                                for (const auto& pair : instances_list_iterations)
                                {
                                    if (instances_list[instance_list_l].getPosition().y + instances_list[instance_list_l].getHitbox().height > 800)
                                    {
                                        instances_list[pair.second].changePosition(instances_list[pair.second].getPosition().x, instances_list[pair.second].getPosition().y - 85);
                                    }    
                                }
                                mp++; 
                            }
                        }
                    }
                }
            }
        }

        if (UI_current == UI_PAGES::MainMenu)
        {
            console.handleEvent(event);

            if (display_guard_window == true)
            {
                GuardBox.event(event);
            }
        }

        if (UI_current == UI_PAGES::ManageMenu)
        {
            switch(manage_ui)
            {
                case BETTERBUILD_WORLDS:
                {
                    if (instanceDataLoading == false)
                    {
                        if (event.type == sf::Event::MouseWheelMoved)
                        {
                            int mouse_scroll = event.mouseWheel.delta;

                            if (mouse_scroll > 0)
                            {
                                int mp = event.mouseWheel.delta;
                                while (mp > 0)
                                {
                                    if (betterbuildworlds_list.begin()->second.getPOsition().y < 0)
                                    {
                                        for (const auto& pair : betterbuildworlds_list)
                                        {
                                            betterbuildworlds_list[pair.first].changePosition(betterbuildworlds_list[pair.first].getPOsition().x, betterbuildworlds_list[pair.first].getPOsition().y + 120);
                                        }    
                                    }
                                    mp--;
                                }
                            }
                            else
                            {
                                int mp = event.mouseWheel.delta;
                                while (mp < 0)
                                {
                                    auto last = std::prev(betterbuildworlds_list.end());
                                    if (last->second.getPOsition().y + last->second.getHitbox().height > 800)
                                    {
                                        for (const auto& pair : betterbuildworlds_list)
                                        {
                                            betterbuildworlds_list[pair.first].changePosition(betterbuildworlds_list[pair.first].getPOsition().x, betterbuildworlds_list[pair.first].getPOsition().y - 120);
                                        }
                                    }
                                    mp++;
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }

        if (UI_current == UI_PAGES::SettingsMenu)
        {
            if (options_ui == SETTIGNS_CATEGORIES::MAIN_PAGE)
            {
                SlimeRancher_steam_path_textbox.handleEvent(event);
                SlimeRancher_instances_path_textbox.handleEvent(event);
                steamcmd_path_textbox.handleEvent(event);

                // theme_list_ddl.scrollEvent(event);
            }
            if (options_ui == SETTIGNS_CATEGORIES::PROFILE_PAGE)
            {
                SteamProfile_name_textbox.handleEvent(event);
                SteamProfile_password_textbox.handleEvent(event);
            }
        }

        if (UI_current == UI_PAGES::VersionsList)
        {

            if (mouse_pos.x > 10 && mouse_pos.x < 1270 && mouse_pos.y > 85 && mouse_pos.y < 800)
            {
                if (event.type == sf::Event::MouseWheelMoved)
                {
                    
                    int mouse_scroll = event.mouseWheel.delta;

                    int first = versions_pachnotes_list.begin()->first;
                    int last = versions_pachnotes_list.size();

                    if (Show_older_instances_checkbox.getState() == false)
                    {
                        for (const auto& pair : versions_pachnotes_list)
                        {
                            if (versions_map[versions_pachnotes_list[first].getVersion()].version_type == "pre_release")
                            {
                                first++;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                    if (mouse_scroll > 0)
                    {
                        int mp = event.mouseWheel.delta;
                        while (mp > 0)
                        {
                            if (versions_pachnotes_list[first].getPosition().y < 45)
                            {
                                for (const auto& pair : versions_pachnotes_list)
                                {
                                    versions_pachnotes_list[pair.first].reposition(versions_pachnotes_list[pair.first].getPosition().x, versions_pachnotes_list[pair.first].getPosition().y + 180);
                                }
                            } 
                            mp--;
                        }
                    }
                    else
                    {
                        int mp = event.mouseWheel.delta;
                        while (mp < 0)
                        {
                            if (versions_pachnotes_list[last].getPosition().y + versions_pachnotes_list[last].hitbox().height > 640)
                            {
                                for (const auto& pair : versions_pachnotes_list)
                                {
                                    versions_pachnotes_list[pair.first].reposition(versions_pachnotes_list[pair.first].getPosition().x, versions_pachnotes_list[pair.first].getPosition().y - 180);
                                }    
                            }
                            mp++; 
                        }
                    }
                }    
            }
        }
    }
}