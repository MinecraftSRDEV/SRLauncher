void scrollPatchNotes(sf::Event& event, sf::Vector2f& mouse_pos)
{
    if (mouse_pos.x > 10 && mouse_pos.x < 1270 && mouse_pos.y > 85 && mouse_pos.y < 800)
    {
        if (event.type == sf::Event::MouseWheelMoved)
        {
            
            int mouse_scroll = event.mouseWheel.delta;

            int first = versions_pachnotes_list.begin()->first;
            int last = versions_pachnotes_list.size();

            if (SettingsElemets::subcats::general::Show_prereleases_checkbox.getState() == false)
            {
                for (const auto& pair : versions_pachnotes_list)
                {
                    if (versionsData_map[versions_pachnotes_list[first].getVersion()].version_type == "pre_release")
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