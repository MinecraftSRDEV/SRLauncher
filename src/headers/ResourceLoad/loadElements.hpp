void addToIconsList(int x, int y, const std::string& id)
{
    instance_icons_textures[id].loadFromFile("./assets/resources/icons/" + id + ".png");
    InstanceIconBar::IconBarMap[id].create(x, y, instance_icons_textures[id], id);
}

void loadElements()
{
    font.loadFromFile("./assets/resources/arial.ttf");

    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    handCursor.loadFromSystem(sf::Cursor::Hand);
    waitCursor.loadFromSystem(sf::Cursor::ArrowWait);
    notAllowedCursor.loadFromSystem(sf::Cursor::NotAllowed);
    crossCursor.loadFromSystem(sf::Cursor::Cross);

    bg_texture.loadFromFile("./assets/resources/background.png");
    SettingsElemets::subcats::steamAccount::profile_icon_tx.loadFromFile("./assets/resources/unknown_user.png");
    playtime_clock_tx.loadFromFile("./assets/resources/playtime_clock.png");

    int last_x = 50;
    int y = 330;

    addToIconsList(last_x, y, "boom");
    last_x += 80;
    addToIconsList(last_x, y, "crystal");
    last_x += 80;
    addToIconsList(last_x, y, "dervish");
    last_x += 80;
    addToIconsList(last_x, y, "feral");
    last_x += 80;
    addToIconsList(last_x, y, "glitch");
    last_x += 80;
    addToIconsList(last_x, y, "gold");
    last_x += 80;
    addToIconsList(last_x, y, "honey");
    last_x += 80;
    addToIconsList(last_x, y, "hunter");
    last_x += 80;
    addToIconsList(last_x, y, "lucky");
    last_x += 80;
    addToIconsList(last_x, y, "mosaic");
    last_x += 80;
    addToIconsList(last_x, y, "phosphor");
    last_x += 80;
    addToIconsList(last_x, y, "pink");
    last_x += 80;
    addToIconsList(last_x, y, "puddle");
    last_x += 80;
    addToIconsList(last_x, y, "quantum");
    last_x += 80;
    addToIconsList(last_x, y, "rad");
    last_x += 80;
    addToIconsList(last_x, y, "rock");
    last_x += 80;
    addToIconsList(last_x, y, "saber");
    last_x += 80;
    addToIconsList(last_x, y, "tabby");
    last_x += 80;
    addToIconsList(last_x, y, "tangle");
    last_x += 80;
    addToIconsList(last_x, y, "tarr");
    last_x += 80;
}