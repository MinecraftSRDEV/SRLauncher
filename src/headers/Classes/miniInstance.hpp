class miniInstanceClass {
public:
miniInstanceClass () {}

void create(const miniInstanceList::attributes& attr)
{
    version_string = attr.version;
    name_string = attr.name;
    size_y_global = attr.size_y;
    number_on_list = attr.it_number;
    playtime = attr.playtime_count;
    lastPlayed = attr.lastPlayed;

    icon_spr_tx = attr.icon_texture;
    playtime_clock_tx = attr.clock_texture;

    icon_sprite.setTexture(icon_spr_tx);

    playtime_clock.setTexture(playtime_clock_tx);

    playtime_clock.setColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);

    backgorund.setSize(sf::Vector2f(attr.size_x, attr.size_y));
    backgorund.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::semitransparrent]);
    backgorund.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    backgorund.setOutlineThickness(1);
    backgorund.setPosition(attr.x, attr.y);

    instance_name_text.setString(nameCheck());
    instance_name_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    instance_name_text.setCharacterSize(26);
    instance_name_text.setFont(attr.font);

    version_text.setString("v." + attr.version);
    version_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    version_text.setCharacterSize(26);
    version_text.setFont(attr.font);

    playtime_text.setString(buildPlaytimeString());
    playtime_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    playtime_text.setCharacterSize(16);
    playtime_text.setFont(attr.font);

    Function_button.create(0,0, 60, 30, attr.font, "Mount", false, theme_selected);

    mods_attributes = attr.modsAtrb;

    reposition();
}

void hilight(bool state = false)
{
    if (state == false)
    {
        backgorund.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::semitransparrent]);
    }
    else
    {
        backgorund.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::halftransparrent]);
    }
}

std::string getLastPlayed()
{
    return lastPlayed;
}

void render(sf::RenderWindow& window)
{
    window.draw(backgorund);
    window.draw(icon_sprite);
    window.draw(instance_name_text);
    window.draw(playtime_clock);
    window.draw(playtime_text);
    window.draw(version_text);

    Function_button.render(window);
}

void update(sf::Vector2f& mouse)
{
    Function_button.update(mouse);
}

bool getInstalledStatus()
{
    return installed;
}

int getItNumber()
{
    return number_on_list;
}

void changePosition(int x, int y)
{
    backgorund.setPosition(x, y);
    reposition();
}

enum status {
    Unmounted,
    Mounted
};

sf::Vector2f getPosition()
{
    return backgorund.getPosition();
}

std::string getID()
{
    return name_string;
}
std::string getVer()
{
    return version_string;
}

void updateStatus(int status)
{
    switch (status)
    {
        case status::Unmounted:
        {
            Function_button.setText("Mount");
            break;
        }
        case status::Mounted:
        {
            Function_button.setText("Unmount");
            break;
        }
    }
}

sf::Texture& getIconTexture()
{
    return icon_spr_tx;
}

sf::FloatRect getHitbox()
{
    return backgorund.getGlobalBounds();
}

sf::FloatRect getMountButtonHitbox()
{
    return Function_button.hitbox();
}

InstanceModAttributes getModAttributes()
{
    return mods_attributes;
}

std::string getPlaytime()
{
    return playtime;
}

Playtime getTime()
{
    return time;
}

std::string name_string;

private:

void reposition()
{
    icon_sprite.setPosition(sf::Vector2f(backgorund.getPosition().x + 5, backgorund.getPosition().y + 10));
    instance_name_text.setPosition(backgorund.getPosition().x + 70, backgorund.getPosition().y + 5);
    version_text.setPosition(backgorund.getPosition().x + 70, backgorund.getPosition().y + 35);

    sf::FloatRect higestXsize;

    sf::FloatRect name_text_rect = instance_name_text.getLocalBounds();
    sf::FloatRect version_text_rect = version_text.getLocalBounds();

    higestXsize = name_text_rect;
    if (version_text_rect.width > version_text_rect.width)
    {
        higestXsize = version_text_rect;
    }

    if (higestXsize.width < 270)
    {
        higestXsize.width = 270;
    }

    playtime_clock.setPosition(higestXsize.width + 30, backgorund.getPosition().y + 30);
    playtime_text.setPosition(higestXsize.width + 56, backgorund.getPosition().y + 33);

    Function_button.changePosition(backgorund.getPosition().x + (640 - 80), backgorund.getPosition().y + 25);
}

std::string nameCheck()
{
    std::string output = name_string;
    if (name_string.length() > 15)
    {
        output = output.substr(0, 15) + "...";
    }

    return output;
}

std::string buildPlaytimeString()
{
    std::string output;

    sf::Int64 value;
    try
    {
        value = std::stoll(playtime);
    }
    catch (std::exception e) {};

    time = calcPlaytime(value);

    if (time.miliseconds < sf::Int64(1))
    {
        output = "Never";
    }
    else if (time.minutes < sf::Int64(1))
    {
        output = "Less than 1 minute";
    }
    else if (time.hours < sf::Int64(1))
    {
        output = std::to_string(time.minutes) + " m";
    }
    else
    {
        output = std::to_string(time.hours);
        if (time.minutes > sf::Int64(0))
        {
            output += "," + std::to_string(time.minutes).substr(0, 1);
        }
        output += " h";
    }

    return output;
}

std::string version_string;
std::string inst_name;
int size_y_global;

int number_on_list = 0;
std::string playtime = "0";

bool installed;

Playtime time;

std::string lastPlayed;

sf::RectangleShape backgorund;
sf::Text instance_name_text;
sf::Text version_text;
sf::Sprite icon_sprite;
sf::Sprite playtime_clock;
sf::Text playtime_text;
sf::Texture icon_spr_tx;
sf::Texture playtime_clock_tx;

InstanceModAttributes mods_attributes;

sfg::Button Function_button;
};