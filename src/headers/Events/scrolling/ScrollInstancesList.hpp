void scrollInstancesList(sf::Event& event, sf::Vector2f& mouse_pos)
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