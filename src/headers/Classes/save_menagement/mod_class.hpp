class ModClass {
public:

ModClass () {}

bool canBeInstalled = true;

void create(int x, int y, const ModAttribs& modAttribs, sf::Font& font, sf::RenderWindow& window, int color = ColorPalete::Bright)
{
    attribs = modAttribs;
    colorSet = color;

    background.setSize(sf::Vector2f(560, 95));
    background.setOutlineThickness(1);

    setAttributes();

    mod_name.setFont(font);
    mod_name.setCharacterSize(20);
    
    mod_type.setFont(font);
    mod_type.setCharacterSize(20);
    
    mod_srversion.setFont(font);
    mod_srversion.setCharacterSize(20);

    compatybile_text.setFont(font);
    compatybile_text.setCharacterSize(20);

    move_button.create(0,0, 80, 30, font, "move", false, theme_selected);
    
    changePosition(x, y);
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
    if (background.getPosition().y >= -18 and background.getPosition().y <= 800)
    {
        window.draw(background);
        window.draw(mod_name);
        window.draw(mod_type);
        window.draw(mod_srversion);
        window.draw(compatybile_text);
        move_button.render(window);    
    }
    
}

void update(sf::Vector2f& mouse)
{
    move_button.update(mouse);

    move_button.setBlockState(!canBeInstalled);
}

typedef void (*FunctionType)();

void setFunction(FunctionType function)
{
    cachedFunction = function;
    move_button.setFunction(cachedFunction);
}

void changeButtonType(int type)
{
    if (type == 0)
    move_button.setText("Install");
    else
    move_button.setText("Remove");
}

sf::Vector2f getPOsition()
{
    return background.getPosition();
}

sf::FloatRect getHitbox()
{
    return background.getGlobalBounds();
}

sf::FloatRect getMoveButtonHitbox()
{
    return move_button.hitbox();
}

ModAttribs getAttribs()
{
    return attribs;
}

void changePosition(int x, int y)
{
    background.setPosition(x, y);

    mod_name.setPosition(x + 10, y + 10);
    mod_type.setPosition(x + 10, y + 30);

    mod_srversion.setPosition(x + background.getGlobalBounds().width - (mod_srversion.getLocalBounds().width + 10), y + 10);
    compatybile_text.setPosition(x + background.getGlobalBounds().width - (compatybile_text.getLocalBounds().width + 10), y + 30);

    move_button.changePosition(x + background.getGlobalBounds().width - 90, y + 55);
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

FunctionType cachedFunction = nullptr;
};