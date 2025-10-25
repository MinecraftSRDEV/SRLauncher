bool is_right_mouse_button_pressed = false;

void mouse_right()
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (UI_current == UiPages::InstancesMenu)
    {
        if (instances_list.size() > 0)
        {
            for (const auto& itr : instances_list)
            {
                if (instances_list[itr.first].getHitbox().contains(mouse))
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        if (is_right_mouse_button_pressed == false)
                        {
                            is_right_mouse_button_pressed = true;
                            instanceDetailsCategory::change(instances_list[itr.first].getID());
                        }
                    }
                    else
                    {
                        is_right_mouse_button_pressed = false;
                    }
                }
            }
        }
    }
}