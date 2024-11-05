class InstanceIconBarOption {
public:

void create(int x, int y, sf::Texture& tx, std::string id, int color = ColorPalete::Bright)
{
    icon_tx = tx;
    icon_id = id;
    
    icon.setTexture(icon_tx);

    background.setSize(sf::Vector2f(80, 80));
    background.setOutlineThickness(1);

    reposition(x, y);
    setTheme(color);
}

void setTheme(int color)
{
    colorSel = color;

    background.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::halftransparrent]);
    background.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::outline]);
}

void render(sf::RenderWindow& window)
{
    if (background.getPosition().x > 49 && background.getPosition().x < 870)
    {
        window.draw(background);
        window.draw(icon);    
    }
}

sf::Vector2f getPosition()
{
    return background.getPosition();
}

void update(sf::Vector2f& mouse)
{
    if (background.getGlobalBounds().contains(mouse))
    {

    }
}

std::string getId()
{
    return icon_id;
}

void reposition(int x, int y)
{
    background.setPosition(x,y);
    icon.setPosition(x + 10, y + 10);
}

private:

sf::Sprite icon;
sf::RectangleShape background;
sf::Texture icon_tx;

std::string icon_id;

int colorSel;
};