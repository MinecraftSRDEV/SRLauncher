class instance_list_class {
public:
instance_list_class () {}

void create(int x, int y, int size_x, int size_y, std::string name, std::string version, sf::Font& font)
{
    version_string = version;
    name_string = name;
    size_y_global = size_y;

    backgorund.setSize(sf::Vector2f(size_x, size_y));
    backgorund.setFillColor(sf::Color::White);
    backgorund.setOutlineColor(sf::Color::Black);
    backgorund.setOutlineThickness(1);
    backgorund.setPosition(x, y);

    instance_name_text.setString(name);
    instance_name_text.setFillColor(sf::Color::Black);
    instance_name_text.setCharacterSize(26);
    instance_name_text.setFont(font);

    version_text.setString(version);
    version_text.setFillColor(sf::Color::Black);
    version_text.setCharacterSize(26);
    version_text.setFont(font);

    Play_button.create(0,0, 60, 30, font, "Mount");
    Edit_button.create(0,0, 60, 30, font, "Edit");
    Remove_button.create(0,0, 60, 30, font, "Remove");

    reposition();
}

void render(sf::RenderWindow& window)
{
    if (backgorund.getPosition().y >= 85 and backgorund.getPosition().y <= 700)
    {
        window.draw(backgorund);
        window.draw(instance_name_text);
        window.draw(version_text);

        Play_button.render(window);
        Edit_button.render(window);
        Remove_button.render(window);
    }
}

void update(sf::Vector2f mouse)
{
    Play_button.update(mouse);
    Edit_button.update(mouse);
    Remove_button.update(mouse);
}

void event(sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelMoved)
    {
        int mouse_scroll = event.mouseWheel.delta;

        if (mouse_scroll > 0)
        {
            backgorund.setPosition(backgorund.getPosition().x, backgorund.getPosition().y + size_y_global);
            reposition();
        }
        else
        {
            backgorund.setPosition(backgorund.getPosition().x, backgorund.getPosition().y - size_y_global);
            reposition();
        }
    }
}

enum status {
    Unmounted,
    Mounted
};

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
            Play_button.setText("Mount");
            // Play_button.setFunction(mount_function);
            break;
        }
        case status::Mounted:
        {
            Play_button.setText("Unmount");
            // Play_button.setFunction(unmount_funtcion);
            break;
        }
    }
}

sf::FloatRect getMountButtonHitbox()
{
    return Play_button.hitbox();
}

std::string name_string;

private:

void reposition()
{
    instance_name_text.setPosition(backgorund.getPosition().x + 5, backgorund.getPosition().y + 5);
    version_text.setPosition(backgorund.getPosition().x + 5, backgorund.getPosition().y + 35);

    Play_button.changePosition(backgorund.getPosition().x + 1000, backgorund.getPosition().y + 25);
    Edit_button.changePosition(backgorund.getPosition().x + 1080, backgorund.getPosition().y + 25);
    Remove_button.changePosition(backgorund.getPosition().x + 1180, backgorund.getPosition().y + 25);
}

std::string version_string;
int size_y_global;

sf::RectangleShape backgorund;
sf::Text instance_name_text;
sf::Text version_text;

Button Play_button;
Button Edit_button;
Button Remove_button;
};