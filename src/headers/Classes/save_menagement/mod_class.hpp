class ModClass {
public:

ModClass () {}

void create(int x, int y, const ModAttribs& modAttribs, sf::Font& font, int color = ColorPalete::Bright)
{
    attribs = modAttribs;
    colorSet = color;

    background.setPosition(x, y);
    background.setSize(sf::Vector2f(560, 60));
    background.setOutlineThickness(1);

    setAttributes();

    mod_name.setFont(font);
    mod_name.setCharacterSize(20);
    mod_name.setPosition(x + 10, y + 10);
    
    mod_type.setFont(font);
    mod_type.setCharacterSize(20);
    mod_type.setPosition(x + 10, y + 30);

    mod_srversion.setFont(font);
    mod_srversion.setCharacterSize(20);
    mod_srversion.setPosition(x + background.getGlobalBounds().width - (mod_srversion.getLocalBounds().width + 10), y + 10);

    compatybile_text.setFont(font);
    compatybile_text.setCharacterSize(20);
    compatybile_text.setPosition(x + background.getGlobalBounds().width - (compatybile_text.getLocalBounds().width + 10), y + 30);

    setTheme(color);
}

void setTheme(int color)
{
    background.setFillColor(ColorPalete::Palete[color][ColorPalete::semitransparrent]);
    background.setOutlineColor(ColorPalete::Palete[color][ColorPalete::outline]);
    mod_name.setFillColor(ColorPalete::Palete[color][ColorPalete::font]);
    mod_type.setFillColor(ColorPalete::Palete[color][ColorPalete::font]);
    mod_srversion.setFillColor(ColorPalete::Palete[color][ColorPalete::font]);
    compatybile_text.setFillColor(ColorPalete::Palete[color][ColorPalete::font]);
    move_button.setTheme(color);
}

void render(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(mod_name);
    window.draw(mod_type);
    window.draw(mod_srversion);
    window.draw(compatybile_text);
    move_button.render(window);
}

void update(sf::Vector2f& mouse)
{
    move_button.update(mouse);
}

ModAttribs getAttribs()
{
    return attribs;
}

private:

void setAttributes()
{
    if (!attribs.modName.empty())
    {
        mod_name.setString(attribs.modName);
    }
    else
    {
        mod_name.setString("Unknown name");
    }

    if (!attribs.modType.empty())
    {
        mod_type.setString(attribs.modType);
    }
    else
    {
        mod_type.setString("Unknown type");
    }

    if (!attribs.SRmodVersion.empty())
    {
        mod_srversion.setString(attribs.SRmodVersion);
    }
    else
    {
        mod_srversion.setString("Unknown Slime Rancher version");
    }

    if (attribs.compatybile == true)
    {
        compatybile_text.setString("Compatybile");
    }
    else
    {
        compatybile_text.setString("Incompatybile/unknown");
    }
}

int colorSet;

ModAttribs attribs;

sf::RectangleShape background;
sf::Text mod_name;
sf::Text mod_type;
sf::Text mod_srversion;
sf::Text compatybile_text;

sfg::Button move_button;
};