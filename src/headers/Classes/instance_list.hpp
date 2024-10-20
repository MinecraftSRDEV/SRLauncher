class instance_list_class {
public:
instance_list_class () {}

void create(int x, int y, int size_x, int size_y, std::string name, std::string version, sf::Font& font, InstanceModAttributes modsAtrb, int it_number)
{
    version_string = version;
    name_string = name;
    size_y_global = size_y;
    number_on_list = it_number;

    backgorund.setSize(sf::Vector2f(size_x, size_y));
    backgorund.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::semitransparrent]);
    backgorund.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    backgorund.setOutlineThickness(1);
    backgorund.setPosition(x, y);

    instance_name_text.setString(name);
    instance_name_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    instance_name_text.setCharacterSize(26);
    instance_name_text.setFont(font);

    version_text.setString(version);
    version_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    version_text.setCharacterSize(26);
    version_text.setFont(font);

    modLoaders_text.setString("Vanilla");
    modLoaders_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    modLoaders_text.setCharacterSize(26);
    modLoaders_text.setFont(font);

    Play_button.create(0,0, 60, 30, font, "Mount", false, theme_selected);
    Edit_button.create(0,0, 60, 30, font, "Edit", false, theme_selected);
    Menage_button.create(0,0, 60, 30, font, "Menage", false, theme_selected);
    OpenGameFolder_button.create(0,0, 100, 30, font, "Open game folder", false, theme_selected);
    OpenSavesFolder_button.create(0,0, 100, 30, font, "Open saves folder", false, theme_selected);
    Remove_button.create(0,0, 70, 30, font, "Remove", false, theme_selected);

    selected_checkbox.create(40, 40, 0, 0, "Selected", 26, font, false, theme_selected);

    mods_attributes = modsAtrb;

    scan_mod_loaders();
    reposition();
}

void render(sf::RenderWindow& window)
{
    if (backgorund.getPosition().y >= 85 and backgorund.getPosition().y <= 800)
    {
        window.draw(backgorund);
        window.draw(instance_name_text);
        window.draw(version_text);
        window.draw(modLoaders_text);

        if (show_selection == false)
        {
            Play_button.render(window);
            Edit_button.render(window);
            Menage_button.render(window);
            OpenGameFolder_button.render(window);
            OpenSavesFolder_button.render(window);
            Remove_button.render(window);    
        }
        else
        {
            selected_checkbox.render(window);
        }
    }
}

void update(sf::Vector2f& mouse)
{
    if (show_selection == false)
    {
        Play_button.update(mouse);
        Edit_button.update(mouse);
        Menage_button.update(mouse);
        OpenGameFolder_button.update(mouse);
        OpenSavesFolder_button.update(mouse);
        Remove_button.update(mouse);    
    }
    else
    {
        selected_checkbox.update(mouse);
    }
}

void setInstalledStatus(bool status)
{
    installed = status;

    if (installed == false)
    {
        modLoaders_text.setString("Game isn't installed");
    }
}

bool getInstalledStatus()
{
    return installed;
}

int getItNumber()
{
    return number_on_list;
}

void event(sf::Event& event)
{
    
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

sf::FloatRect getHitbox()
{
    return backgorund.getGlobalBounds();
}

sf::FloatRect getMountButtonHitbox()
{
    return Play_button.hitbox();
}

sf::FloatRect getEditButtonHitbox()
{
    return Edit_button.hitbox();
}

sf::FloatRect getMenageButtonHitbox()
{
    return Menage_button.hitbox();
}

sf::FloatRect getOpenGameFolderButtonHitbox()
{
    return OpenGameFolder_button.hitbox();
}

sf::FloatRect getOpenSavesFolderButtonHitbox()
{
    return OpenSavesFolder_button.hitbox();
}

sf::FloatRect getRemoveButtonHitbox()
{
    return Remove_button.hitbox();
}

sf::FloatRect getSelectionCheckboxHitbox()
{
    return selected_checkbox.hitbox();
}

InstanceModAttributes getModAttributes()
{
    return mods_attributes;
}

void setShowSelectionState(bool state)
{
    show_selection = state;
}

std::string name_string;

private:

void scan_mod_loaders()
{
    std::string modloaders_list;
    if (mods_attributes.StaysModtool_installed == true)
    {
        modloaders_list = "Saty's mod tool";
    }
    if (mods_attributes.SatysModLoader_installed == true)
    {
        modloaders_list = "Saty's mod loader";
    }
    if (mods_attributes.UMF_installed == true)
    {
        if (!modloaders_list.empty())
        {
            modloaders_list += " | ";
        }
        modloaders_list += "UMF";
    }

    if (!modloaders_list.empty())
    {
        modLoaders_text.setString(modloaders_list);    
    }
}

void reposition()
{
    instance_name_text.setPosition(backgorund.getPosition().x + 5, backgorund.getPosition().y + 5);
    version_text.setPosition(backgorund.getPosition().x + 5, backgorund.getPosition().y + 35);

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

    modLoaders_text.setPosition(higestXsize.width + 30, backgorund.getPosition().y + 20);

    Play_button.changePosition(backgorund.getPosition().x + 670, backgorund.getPosition().y + 25);
    Edit_button.changePosition((Play_button.getPosition().x + Play_button.hitbox().width) + 20, backgorund.getPosition().y + 25);
    Menage_button.changePosition((Edit_button.getPosition().x + Edit_button.hitbox().width) + 20, backgorund.getPosition().y + 25);
    OpenGameFolder_button.changePosition((Menage_button.getPosition().x + Menage_button.hitbox().width) + 20, backgorund.getPosition().y + 25);
    OpenSavesFolder_button.changePosition((OpenGameFolder_button.getPosition().x + OpenGameFolder_button.hitbox().width) + 20, backgorund.getPosition().y + 25);
    Remove_button.changePosition((OpenSavesFolder_button.getPosition().x + OpenSavesFolder_button.hitbox().width) + 20, backgorund.getPosition().y + 25);

    selected_checkbox.changePosition(backgorund.getGlobalBounds().width - 90, backgorund.getPosition().y + 20);
}

std::string version_string;
int size_y_global;

int number_on_list = 0;

bool installed;
bool selected;
bool show_selection = false;

sf::RectangleShape backgorund;
sf::Text instance_name_text;
sf::Text version_text;

sf::Text modLoaders_text;

InstanceModAttributes mods_attributes;

sfg::Button Play_button;
sfg::Button Edit_button;
sfg::Button Menage_button;
sfg::Button OpenGameFolder_button;
sfg::Button OpenSavesFolder_button;
sfg::Button Remove_button;
sfg::Checkbox selected_checkbox;
};