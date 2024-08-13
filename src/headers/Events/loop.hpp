void events_loop()
{
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
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
                versions_list.scrollEvent(event);
                break;
            }
        }

        new_instance_name_textbox.handleEvent(event);

        for (const auto& pair : instances_list)
        {
            instances_list[pair.first].event(event);
        }

        if (UI_current == UI_PAGES::SettingsMenu)
        {
            if (options_ui == SETTIGNS_CATEGORIES::MAIN_PAGE)
            {
                SlimeRancher_steam_path_textbox.handleEvent(event);
                SlimeRancher_instances_path_textbox.handleEvent(event);    
            }
            if (options_ui == SETTIGNS_CATEGORIES::PROFILE_PAGE)
            {
                SteamProfile_name_textbox.handleEvent(event);
                SteamProfile_password_textbox.handleEvent(event);
            }
        }
    }
}