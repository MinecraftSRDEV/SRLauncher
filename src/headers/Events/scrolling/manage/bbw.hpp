void scrollManageBbw(sf::Event& event, sf::Vector2f& mouse_pos)
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