class BackupList {
public:

void create(int x, int y, BackupData& inputData, sf::Font& font)
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

    dateText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    dateText.setCharacterSize(26);
    dateText.setFont(font);

    sourceText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    sourceText.setCharacterSize(16);
    sourceText.setFont(font);

    remove_button.create(0,0, 80, 30, font, "remove", false, theme_selected);
    restore_button.create(0,0, 80, 30, font, "restore", false, theme_selected);
    reveal_button.create(0,0, 120, 30, font, "reveal in explorer", false, theme_selected);

    applyData();
    reposition();
}

sf::Vector2f getPosition()
{
    return background.getPosition();
}

void updateData(BackupData& input)
{
    data = input;
}

void update(sf::Vector2f& mouse)
{
    if (background.getPosition().y >= 5 and background.getPosition().y <= 800)
    {
        remove_button.update(mouse);
        restore_button.update(mouse);
        reveal_button.update(mouse);
    }
}

void render(sf::RenderWindow& window)
{
    if (background.getPosition().y >= -80 and background.getPosition().y <= 800)
    {
        window.draw(background);
        window.draw(nameText);
        window.draw(dateText);
        window.draw(sourceText);

        remove_button.render(window);
        restore_button.render(window);
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

sf::FloatRect getRemoveButtonHitbox()
{
    return remove_button.hitbox();
}

sf::FloatRect getRestoreButtonHitbox()
{
    return restore_button.hitbox();
}

sf::FloatRect getRevealButtonHitbox()
{
    return reveal_button.hitbox();
}

BackupData getData()
{
    return data;
}

void changePosition(int x, int y)
{
    background.setPosition(x, y);
    reposition();
}

enum BUTTON_ID {
    REMOVE,
    RESTORE,
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
        case RESTORE:
        {
            restore_button.setFunction(cachedFunction);
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
    dateText.setString("Creted date: " + data.date);
    sourceText.setString("Created in: " + data.source);
}

void reposition()
{
    nameText.setPosition(background.getPosition().x + 5, background.getPosition().y + 5);
    dateText.setPosition(background.getPosition().x + 5, nameText.getPosition().y + (nameText.getLocalBounds().height + 10));
    sourceText.setPosition(background.getPosition().x + 5, dateText.getPosition().y + (dateText.getLocalBounds().height + 25));

    remove_button.changePosition(background.getPosition().x + (background.getGlobalBounds().width - (remove_button.hitbox().width + 10)), background.getPosition().y + (background.getGlobalBounds().height - (remove_button.hitbox().height + 10)));
    restore_button.changePosition(remove_button.getPosition().x - (restore_button.hitbox().width + 10), remove_button.getPosition().y);
    reveal_button.changePosition(restore_button.getPosition().x - (restore_button.hitbox().width + 50), restore_button.getPosition().y);
}
BackupData data;

sf::RectangleShape background;
sf::Text nameText;
sf::Text dateText;
sf::Text sourceText;

int size_x_global = 1140;
int size_y_global = 120;

sfg::Button remove_button;
sfg::Button restore_button;
sfg::Button reveal_button;

FunctionType cachedFunction = nullptr;
};