void downloading_animation()
{
    MainpageElements::playbar::progress_moveing.setPosition(-70, MainpageElements::playbar::progress_moveing.getPosition().y);

    sf::Clock cooldown;
    cooldown.restart();

    while (true)
    {
        if (game_downloading == false)
        {
            break;
        }

        if (cooldown.getElapsedTime() > sf::milliseconds(100))
        {
            cooldown.restart();

            if (MainpageElements::playbar::progress_moveing.getPosition().x > 1280)
            {
                MainpageElements::playbar::progress_moveing.setPosition(-70, MainpageElements::playbar::progress_moveing.getPosition().y);
            }
            else
            {
                MainpageElements::playbar::progress_moveing.setPosition(MainpageElements::playbar::progress_moveing.getPosition().x + 20, MainpageElements::playbar::progress_moveing.getPosition().y);
            }
        }
    }
}