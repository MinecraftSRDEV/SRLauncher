std::string getInstanceSelectedIcon()
{
    std::string output;
    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        if (InstanceIconBar::IconBarMap[pair.first].getPosition() == sf::Vector2f(50, 330))
        {
            output = pair.first;
            break;
        }
    }
    return output;
}

void iconsBarScrollLeft()
{
    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        InstanceIconBar::IconBarMap[pair.first].reposition(InstanceIconBar::IconBarMap[pair.first].getPosition().x - 80, 330);
    }

    std::string last;
    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        if (InstanceIconBar::IconBarMap[pair.first].getPosition() == sf::Vector2f(50 - 80, 330))
        {
            last = pair.first;
            InstanceIconBar::IconBarMap[pair.first].reposition(InstanceIconBar::IconBarMap[pair.first].getPosition().x + 1600, 330);
            break;
        }
    }
}

void iconsBarScrollRight()
{
    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        InstanceIconBar::IconBarMap[pair.first].reposition(InstanceIconBar::IconBarMap[pair.first].getPosition().x + 80, 330);
    }

    std::string last;
    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        if (InstanceIconBar::IconBarMap[pair.first].getPosition() == sf::Vector2f(1650, 330))
        {
            last = pair.first;
            InstanceIconBar::IconBarMap[pair.first].reposition(50, 330);
            break;
        }
    }
}

void iconBarScrollWhile(std::string id)
{
    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        if (InstanceIconBar::IconBarMap[id].getPosition() == sf::Vector2f(50, 330))
        {
            break;  
        }
        iconsBarScrollLeft();
    }
}

void scrollIconBar(sf::Event& event, sf::Vector2f& mouse_pos)
{
    if (event.type == sf::Event::MouseWheelMoved)
    {
        int mouse_scroll = event.mouseWheel.delta;

        if (mouse_pos.x > 50 && mouse_pos.x < 940 && mouse_pos.y > 300 && mouse_pos.y < 380)
        {
            int mouse_scroll = event.mouseWheel.delta;

            if (mouse_scroll > 0)
            {
                int mp = event.mouseWheel.delta;
                while (mp > 0)
                {
                    iconsBarScrollLeft();
                    mp--;
                }
            }
            if (mouse_scroll < 0)
            {
                int mp = event.mouseWheel.delta;
                while (mp < 0)
                {
                    iconsBarScrollRight();
                    mp++;
                }
            }
        }    
    }
}