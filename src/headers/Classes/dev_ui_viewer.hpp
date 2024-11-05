class UiViewer {
public:

void update(sf::Vector2f& mouse, sf::Font& font)
{
    if (enabled == true)
    {
        

        if (getClickPos == false)
        {
            clickPos = mouse;
            getClickPos = true;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            pos_text.setPosition(clickPos.x, (clickPos.y - 14));
            pos_text.setFont(font);
            pos_text.setCharacterSize(12);
            pos_text.setFillColor(sf::Color::Black);
            pos_text.setString("x: " + std::to_string(clickPos.x) + " y: " + std::to_string(clickPos.y) + " dx: " + std::to_string(view.getGlobalBounds().width) + " dy: " + std::to_string(view.getGlobalBounds().height));

            view.setFillColor(sf::Color::Black);
            view.setSize(mouse - clickPos);
            view.setPosition(clickPos);

        }
        else
        {
            getClickPos = false;
        } 
    }
}

void enable()
{
    enabled = true;
}

void disable()
{
    enabled = false;
}

void render(sf::RenderWindow& window)
{
    if (enabled == true)
    {
        window.draw(view);
        window.draw(pos_text); 
    }
}

private:

bool enabled = false;

bool getClickPos = false;
sf::RectangleShape view;

sf::Vector2f clickPos;

sf::Text pos_text;
};