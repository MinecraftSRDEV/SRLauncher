class BetterBuildSave {
public:

void create(int x, int y, WorldData& inputData, sf::Font& font)
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

    ObjectsCountText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    ObjectsCountText.setCharacterSize(26);
    ObjectsCountText.setFont(font);
    
    SpawnersCountText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    SpawnersCountText.setCharacterSize(26);
    SpawnersCountText.setFont(font);

    saveVersionText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    saveVersionText.setCharacterSize(26);
    saveVersionText.setFont(font);

    saveLockPasswordText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    saveLockPasswordText.setCharacterSize(26);
    saveLockPasswordText.setFont(font);

    remove_lock_button.create(0,0, 80, 30, font, "remove lock", false, theme_selected);
    remove_button.create(0,0, 80, 30, font, "remove", false, theme_selected);
    gamesaves_slots_button.create(0,0, 100, 30, font, "gamesaves slots", false, theme_selected);
    make_backup_button.create(0,0, 80, 30, font, "make backup", false, theme_selected);

    applyData();
    reposition();
}

sf::Vector2f getPosition()
{
    return background.getPosition();
}

void updateData(WorldData& input)
{
    data = input;
}

void update(sf::Vector2f& mouse)
{
    if (background.getPosition().y >= 5 and background.getPosition().y <= 800)
    {
        remove_lock_button.update(mouse);
        remove_button.update(mouse);
        gamesaves_slots_button.update(mouse);
        make_backup_button.update(mouse);

        remove_lock_button.setBlockState(!data.levelLocked);
    }
}

void render(sf::RenderWindow& window)
{
    if (background.getPosition().y >= -80 and background.getPosition().y <= 800)
    {
        window.draw(background);
        window.draw(nameText);
        window.draw(ObjectsCountText);
        window.draw(SpawnersCountText);
        window.draw(saveVersionText);
        window.draw(saveLockPasswordText);

        remove_lock_button.render(window);
        remove_button.render(window);
        gamesaves_slots_button.render(window);
        make_backup_button.render(window);
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

sf::FloatRect getBackupButtonHitbox()
{
    return make_backup_button.hitbox();
}

WorldData getData()
{
    return data;
}

void changePosition(int x, int y)
{
    background.setPosition(x, y);
    reposition();
}

void event(sf::Event& event)
{
    
}
typedef void (*FunctionType)();

void transportFunction(FunctionType function, FunctionType backup)
{
    cachedFunction = function;
    backupFunction = backup;

    remove_lock_button.setFunction(cachedFunction);     //placeholder
    remove_button.setFunction(cachedFunction);      //placeholder
    gamesaves_slots_button.setFunction(cachedFunction);     //placeholder
    make_backup_button.setFunction(backupFunction);
}

private:

void applyData()
{
    ObjectsCountText.setString("Placed objects: " + std::to_string(data.objectCount));
    SpawnersCountText.setString("Spawners count: " + std::to_string(data.spawnerCount));
    nameText.setString(data.levelname);
    saveVersionText.setString("Version: " + std::to_string(data.version));
    if (data.levelLocked == true)
    {
        saveLockPasswordText.setString("World locked by password: " + data.levelPassword);
        saveLockPasswordText.setFillColor(sf::Color(255,0,0));
    }
    else
    {
        saveLockPasswordText.setString("Unlocked");
        saveLockPasswordText.setFillColor(sf::Color(0,255,0));
    }
}

void reposition()
{
    nameText.setPosition(background.getPosition().x + 5, background.getPosition().y + 5);
    saveVersionText.setPosition(background.getPosition().x + 5, nameText.getPosition().y + (nameText.getLocalBounds().height + 10));
    saveLockPasswordText.setPosition(background.getPosition().x + 5, saveVersionText.getPosition().y + (saveVersionText.getLocalBounds().height + 10));

    ObjectsCountText.setPosition(background.getPosition().x + (background.getGlobalBounds().width - (ObjectsCountText.getLocalBounds().width + 10)), background.getPosition().y + 15);
    SpawnersCountText.setPosition(background.getPosition().x + (background.getGlobalBounds().width - (SpawnersCountText.getLocalBounds().width + 10)), ObjectsCountText.getPosition().y + (ObjectsCountText.getLocalBounds().height + 10));

    make_backup_button.changePosition(background.getPosition().x + (background.getGlobalBounds().width - (make_backup_button.hitbox().width + 10)), background.getPosition().y + (background.getGlobalBounds().height - (make_backup_button.hitbox().height + 10)));
    remove_button.changePosition(make_backup_button.getPosition().x - (remove_button.hitbox().width + 10), make_backup_button.getPosition().y);
    remove_lock_button.changePosition(remove_button.getPosition().x - (remove_lock_button.hitbox().width + 10), make_backup_button.getPosition().y);
    gamesaves_slots_button.changePosition(remove_lock_button.getPosition().x - (gamesaves_slots_button.hitbox().width + 10), make_backup_button.getPosition().y);
}
WorldData data;

sf::RectangleShape background;
sf::Text nameText;
sf::Text ObjectsCountText;
sf::Text SpawnersCountText;
sf::Text saveVersionText;
sf::Text saveLockPasswordText;

int size_x_global = 1140;
int size_y_global = 120;

sfg::Button remove_lock_button;
sfg::Button remove_button;
sfg::Button gamesaves_slots_button;
sfg::Button make_backup_button;

FunctionType cachedFunction = nullptr;
FunctionType backupFunction = nullptr;
};