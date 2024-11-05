void scrollManageVs(sf::Event& event, sf::Vector2f& mouse_pos)
{
    if (event.type == sf::Event::MouseWheelMoved)
    {
        int mouse_scroll = event.mouseWheel.delta;

        if (mouse_scroll > 0)
        {
            int mp = event.mouseWheel.delta;
            while (mp > 0)
            {
                if (vanillasaves_list.begin()->second.getPOsition().y < 0)
                {
                    for (const auto& pair : vanillasaves_list)
                    {
                        vanillasaves_list[pair.first].changePosition(vanillasaves_list[pair.first].getPOsition().x, vanillasaves_list[pair.first].getPOsition().y + 120);
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
                auto last = std::prev(vanillasaves_list.end());
                if (last->second.getPOsition().y + last->second.getHitbox().height > 800)
                {
                    for (const auto& pair : vanillasaves_list)
                    {
                        vanillasaves_list[pair.first].changePosition(vanillasaves_list[pair.first].getPOsition().x, vanillasaves_list[pair.first].getPOsition().y - 120);
                    }
                }
                mp++;
            }
        }
    }
}