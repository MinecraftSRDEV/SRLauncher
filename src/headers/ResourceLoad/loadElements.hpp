void addToIconsList(int& x, int y, const std::string& id)
{
    instance_icons_textures[id].loadFromFile("./assets/resources/icons/" + id + ".png");
    InstanceIconBar::IconBarMap[id].create(x, y, instance_icons_textures[id], id);
    x += 80;
}

void loadIconsListTextures()
{
    int last_x = 50;
    int y = 330;

    std::vector <std::string> iconsNames = {
        {"boom"},{"crystal"},{"dervish"},{"feral"},
        {"glitch"},{"gold"},{"honey"},{"hunter"},
        {"lucky"},{"mosaic"},{"phosphor"},{"pink"},
        {"puddle"},{"quantum"},{"rad"},{"rock"},
        {"saber"},{"tabby"},{"tangle"},{"tarr"}
    };

    for (const auto& itr : iconsNames)
    {
        addToIconsList(last_x, y, itr);
    }
}

void loadElements()
{
    font.loadFromFile("./assets/resources/OpenSans.ttf");

    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    handCursor.loadFromSystem(sf::Cursor::Hand);
    waitCursor.loadFromSystem(sf::Cursor::ArrowWait);
    notAllowedCursor.loadFromSystem(sf::Cursor::NotAllowed);
    crossCursor.loadFromSystem(sf::Cursor::Cross);

    bg_texture.loadFromFile("./assets/resources/background.png");
    SettingsElemets::subcats::steamAccount::profile_icon_tx.loadFromFile("./assets/resources/unknown_user.png");
    playtime_clock_tx.loadFromFile("./assets/resources/playtime_clock.png");

    vanilla_saves_icon_tx.loadFromFile("./assets/resources/vanilla_saves.png");
    mods_saves_icon_tx.loadFromFile("./assets/resources/mods_saves.png");
    instance_mods_icon_tx.loadFromFile("./assets/resources/instance_mods.png");
    launcher_mods_icon_tx.loadFromFile("./assets/resources/launcher_mods.png");

    loadIconsListTextures();
}