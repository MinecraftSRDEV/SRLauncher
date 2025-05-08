class versionClass
{
public:

void create(int x, int y, sf::Font& font, sf::Texture& image, const std::string& version, const std::string& description, int color)
{
    setTheme(color);
    descriptionString = description;
    versionSet = version;
    imageTexture = image;
    versionImage.setTexture(imageTexture);

    version_text.setFont(font);
    version_text.setCharacterSize(26);
    version_text.setString(version);

    background.setSize(sf::Vector2f(256, 180));
    background.setOutlineThickness(2);

    reposition(x,y);
}

void setTheme(int color)
{
    colorSet = color;

    background.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::semitransparrent]);
    background.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::outline]);
    version_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
}

void reposition(int x, int y)
{
    background.setPosition(x, y);
    versionImage.setPosition(x, y);
    version_text.setPosition(x + 5, y + 150);
}

void repositionScroll()
{
    int x = background.getPosition().x;
    int y = background.getPosition().y;
    versionImage.setPosition(x, y);
    version_text.setPosition(x + 5, y + 150);
}

void render(sf::RenderWindow& window)
{
    if (show_prerelease_version == false)
    {
        if (versionsData_map[this->versionSet].version_type == "pre-release")
        {
            return;
        }    
    }
    if (background.getPosition().y > -200 and background.getPosition().y <= 800)
    {
        window.draw(background);
        window.draw(versionImage);
        window.draw(version_text);
    }
}

sf::FloatRect hitbox()
{
    return background.getGlobalBounds();
}

std::string getDescription()
{
    return descriptionString;
}

std::string getVersion()
{
    return version_text.getString();
}

void update(sf::Vector2f& mouse)
{
    if (background.getGlobalBounds().contains(mouse))
    {
        background.setOutlineThickness(2);
    }
    else
    {
        background.setOutlineThickness(0);
    }
}

sf::Vector2f getPosition()
{
    return background.getPosition();
}

private:

sf::RectangleShape background;
sf::Sprite versionImage;
sf::Text version_text;
sf::Texture imageTexture;

int colorSet;

std::string descriptionString;
std::string versionSet;
};