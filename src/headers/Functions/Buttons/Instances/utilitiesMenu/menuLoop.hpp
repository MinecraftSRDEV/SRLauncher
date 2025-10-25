namespace instUtilitiesMenu
{
    using namespace InstanceslistElements;

    sf::Clock clock;

    float deltaTime;

    void MoveToTarget(sf::RectangleShape& sprite, sf::Vector2f target, float speed, float deltaTime)
    {
        sf::Vector2f pos = sprite.getPosition();
        sf::Vector2f direction = target - pos;

        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Jeżeli obiekt już prawie dotarł — ustaw dokładnie na cel
        if (distance < speed * deltaTime || distance == 0.f)
        {
            sprite.setPosition(target);
            return;
        }

        // Normalizujemy kierunek
        direction /= distance;

        // Przesuwamy o prędkość * czas
        sprite.move(direction * speed * deltaTime);
    }

    void moveElementsTo(int x, int y)
    {
        utilitiesMenu::slideButton.changePosition(x + 220, utilitiesMenu::slideButton.getPosition().y);

        utilitiesMenu::scanAllButton.changePosition(x + 40, utilitiesMenu::scanAllButton.getPosition().y);
        utilitiesMenu::refreshListButton.changePosition(x + 40, utilitiesMenu::refreshListButton.getPosition().y);
        utilitiesMenu::goToSettingsButton.changePosition(x + 40, utilitiesMenu::goToSettingsButton.getPosition().y);
    }

    void hideMenuInsantly()
    {
        utilitiesMenu::body.setPosition(-220, utilitiesMenu::body.getPosition().y);
        moveElementsTo(utilitiesMenu::body.getPosition().x, utilitiesMenu::body.getPosition().y);
        utilitiesMenu::utilsShown = false;
        utilitiesMenu::utilsMenuDisplay = false;
        utilitiesMenu::slideButton.setText(">");
    }

    void menuSliding()
    {
        if (utilitiesMenu::utilsShown)
        {
            if (utilitiesMenu::body.getPosition().x < 0)
            {
                utilitiesMenu::utilsMenuDisplay = true;
                utilitiesMenu::slideButton.setText("<");
                MoveToTarget(utilitiesMenu::body, sf::Vector2f(0, 45), 510.0f, deltaTime);
                moveElementsTo(utilitiesMenu::body.getPosition().x, utilitiesMenu::body.getPosition().y);
            }
        }
        else
        {
            if (utilitiesMenu::body.getPosition().x > -220)
            {
                MoveToTarget(utilitiesMenu::body, sf::Vector2f(-220, 45), 510.0f, deltaTime);
                moveElementsTo(utilitiesMenu::body.getPosition().x, utilitiesMenu::body.getPosition().y);
            }
            else
            {
                utilitiesMenu::utilsMenuDisplay = false;
                utilitiesMenu::slideButton.setText(">");
            }
        }
    }

    void utilitiesMenuLoop()
    {
        if (UI_current == UiPages::InstancesMenu)
        {
            menuSliding();    
        }
        
        deltaTime = clock.restart().asSeconds();
    }
}