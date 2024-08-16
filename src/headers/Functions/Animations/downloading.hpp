void downloading_animation()
{
    progress_moveing.setPosition(-70, progress_moveing.getPosition().y);

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

            if (progress_moveing.getPosition().x > 1280)
            {
                progress_moveing.setPosition(-70, progress_moveing.getPosition().y);
            }
            else
            {
                progress_moveing.setPosition(progress_moveing.getPosition().x + 20, progress_moveing.getPosition().y);
            }
        }
    }
}