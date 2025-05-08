class ProgressBar {
public:
    enum class Mode {
        Static,   // Pasek wypełnia się wartością
        Dynamic   // Pasek animuje się
    };

private:
    sf::RectangleShape background;
    sf::RectangleShape fill;
    Mode mode;
    float progress; // Wartość od 0 do 1
    float speed;    // Prędkość animacji dynamicznej
    float dynamicOffset; // Pozycja w trybie dynamicznym
    sf::Clock clock;     // Zegar do animacji

public:
    ProgressBar() {}

    void create(int x, int y, sf::Vector2f size, Mode mode = Mode::Static, float speed = 100.f, int color = ColorPalete::Bright)
    {
        background.setSize(size);
        background.setOutlineThickness(2.f);
        background.setOutlineColor(sf::Color::White);

        fill.setSize({0.f, size.y});

        setTheme(color);

        setPosition(sf::Vector2f(x, y));
    }

    void setPosition(const sf::Vector2f& position) {
        background.setPosition(position);
        fill.setPosition(position);
    }

    void setProgress(float value) {
        if (mode == Mode::Static) {
            progress = std::clamp(value, 0.f, 1.f);
            fill.setSize({background.getSize().x * progress, background.getSize().y});
        }
    }

    void setTheme(int color)
    {
        fill.setFillColor(ColorPalete::Palete[color][ColorPalete::checkbox_inactive]);
        background.setFillColor(ColorPalete::Palete[color][ColorPalete::inactive]);
    }

    void setSpeed(float newSpeed) {
        speed = newSpeed;
    }

    void update() {
        if (mode == Mode::Dynamic) {
            float elapsed = clock.restart().asSeconds();
            dynamicOffset += speed * elapsed;

            float width = background.getSize().x / 3.f; // Szerokość paska w dynamicznym trybie
            if (dynamicOffset > background.getSize().x) {
                dynamicOffset = -width;
            }

            fill.setSize({width, background.getSize().y});
            fill.setPosition(background.getPosition().x + dynamicOffset, background.getPosition().y);
        }
    }

    void render(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(fill);
    }
};