namespace loadingAnimation
{
    sf::Clock clock;

    sf::Vector2f basePos = {400.f, 300.f}; // pozycja bazowa

    void animateIdleSlime(float time)
    {
        // Parametry animacji
        float wobbleSpeed = 6.0f;      // prędkość bujania
        float wobbleAmount = 0.1f;    // amplituda odkształcenia
        float moveAmount = 1.0f;       // amplituda ruchu góra-dół
        float rotateAmount = 6.5f;     // amplituda rotacji (w stopniach)

        // Sinus i cosinus dla dwóch niezależnych faz
        float wobbleSin = std::sin(time * wobbleSpeed);
        float wobbleCos = std::cos(time * wobbleSpeed);

        // Skala – slime rozciąga się i spłaszcza w rytmie
        float scaleX = 1.0f + wobbleSin * wobbleAmount;
        float scaleY = 1.0f - wobbleSin * wobbleAmount;

        // Ruch góra-dół
        float yOffset = wobbleCos * moveAmount;

        // Rotacja – buja się raz w lewo, raz w prawo
        float rotation = wobbleSin * rotateAmount;

        // Ustawienia slima
        loading_icon.setScale(scaleX, scaleY);

        loading_icon.setPosition(basePos.x, basePos.y + yOffset);

        loading_icon.setRotation(rotation);
    }
    
    void setupLoadingAnimation(sf::Vector2f position, std::string textureId)
    {
        basePos = position;
        basePos.x -= instance_icons_textures[textureId].getSize().x / 2;
        basePos.y += (instance_icons_textures[textureId].getSize().y / 2) - 10;
        loading_icon.setTexture(instance_icons_textures[textureId]);
        loading_icon.setOrigin(instance_icons_textures[textureId].getSize().x / 2, instance_icons_textures[textureId].getSize().y / 2);
    }

    void loadingAnimation()
    {
        if (loadingAnimationDisplay)
        {
            float time = clock.getElapsedTime().asSeconds();
            animateIdleSlime(time);
        }
    }
}