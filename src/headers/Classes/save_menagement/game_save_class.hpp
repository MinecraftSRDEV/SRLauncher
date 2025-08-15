class VanillaSave {
public:

void create(int x, int y, SavegameData& inputData, sf::Font& font)
{
    data = inputData;

    background.setSize(sf::Vector2f(size_x_global, size_y_global));
    background.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::semitransparrent]);
    background.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    background.setOutlineThickness(1);
    background.setPosition(x, y);

    nameText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    nameText.setCharacterSize(26);
    nameText.setFont(font);

    saveVersionText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    saveVersionText.setCharacterSize(26);
    saveVersionText.setFont(font);

    last_played_text.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    last_played_text.setCharacterSize(26);
    last_played_text.setFont(font);

    remove_button.create(0,0, 80, 30, font, "remove", false, theme_selected);
    make_backup_button.create(0,0, 80, 30, font, "make backup", false, theme_selected);
    reveal_button.create(0,0, 120, 30, font, "reveal in explorer", false, theme_selected);

    applyData();
    reposition();
}

sf::Vector2f getPosition()
{
    return background.getPosition();
}

void updateData(SavegameData& input)
{
    data = input;
}

void update(sf::Vector2f& mouse)
{
    if (background.getPosition().y >= 5 and background.getPosition().y <= 800)
    {
        remove_button.update(mouse);
        make_backup_button.update(mouse);
        reveal_button.update(mouse);
    }
}

void render(sf::RenderWindow& window)
{
    if (background.getPosition().y >= -80 and background.getPosition().y <= 800)
    {
        window.draw(background);
        window.draw(nameText);
        window.draw(saveVersionText);
        window.draw(last_played_text);

        remove_button.render(window);
        make_backup_button.render(window);
        reveal_button.render(window);
    }
}

sf::Vector2f getPOsition()
{
    return background.getPosition();
}

sf::FloatRect getHitbox()
{
    return background.getGlobalBounds();
}

sf::FloatRect getRevealButtonHitbox()
{
    return reveal_button.hitbox();
}

sf::FloatRect getRemoveButtonHitbox()
{
    return remove_button.hitbox();
}

sf::FloatRect getMakeBackupButtonHitbox()
{
    return make_backup_button.hitbox();
}

SavegameData getData()
{
    return data;
}

void changePosition(int x, int y)
{
    background.setPosition(x, y);
    reposition();
}

void changeDisplayedName(std::string newName)
{
    data.name = newName;
    applyData();
    reposition();
}

enum BUTTON_ID {
    REMOVE,
    MAKE_BACKUP,
    REVEAL
};

void event(sf::Event& event)
{
    
}
typedef void (*FunctionType)();

void transportFunction(FunctionType function, int button_id)
{
    cachedFunction = function;

    switch (button_id)
    {
        case REMOVE:
        {
            remove_button.setFunction(cachedFunction);
            break;
        }
        case MAKE_BACKUP:
        {
            make_backup_button.setFunction(cachedFunction);
            break;
        }
        case REVEAL:
        {
            reveal_button.setFunction(cachedFunction);
            break;
        }
    }
}

private:

void applyData()
{
    nameText.setString(data.name);
    saveVersionText.setString("Version: " + data.version);
    last_played_text.setString("Last played: " + data.last_played);
}

void reposition()
{
    nameText.setPosition(background.getPosition().x + 5, background.getPosition().y + 5);
    saveVersionText.setPosition(background.getPosition().x + 5, nameText.getPosition().y + (nameText.getLocalBounds().height + 10));
    last_played_text.setPosition(background.getPosition().x + 5, saveVersionText.getPosition().y + (saveVersionText.getLocalBounds().height + 10));

    make_backup_button.changePosition(background.getPosition().x + (background.getGlobalBounds().width - (make_backup_button.hitbox().width + 10)), background.getPosition().y + (background.getGlobalBounds().height - (make_backup_button.hitbox().height + 10)));
    remove_button.changePosition(make_backup_button.getPosition().x - (remove_button.hitbox().width + 10), make_backup_button.getPosition().y);
    reveal_button.changePosition(remove_button.getPosition().x - (remove_button.hitbox().width + 50), remove_button.getPosition().y);
}
SavegameData data;

sf::RectangleShape background;
sf::Text nameText;
sf::Text saveVersionText;
sf::Text last_played_text;

int size_x_global = 1140;
int size_y_global = 120;

sfg::Button remove_button;
sfg::Button make_backup_button;
sfg::Button reveal_button;

FunctionType cachedFunction = nullptr;
};