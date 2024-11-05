void scrollVersionDescription(sf::Event& event, sf::Vector2f& mouse_pos)
{
    if (UI_current == UiPages::VersionDescriptionMenu)
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
}