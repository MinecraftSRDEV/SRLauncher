void setRuntimeTexts()
{
    Mounted_instance_info_text.setFont(font);
    Mounted_instance_info_text.setCharacterSize(36);
    Mounted_instance_info_text.setFillColor(sf::Color::Black);
    Mounted_instance_info_text.setPosition(10, 725);

    Launcher_version_text.setFont(font);
    Launcher_version_text.setCharacterSize(36);
    Launcher_version_text.setFillColor(sf::Color::Black);
    Launcher_version_text.setString(launcher_version);
    Launcher_version_text.setPosition((window.getSize().x - 10) - Launcher_version_text.getLocalBounds().width, 725);
}

void setShapesAttributes()
{
    progress_bg.setSize(sf::Vector2f(1280, 20));
    progress_bg.setPosition(sf::Vector2f(0, 780));
    progress_bg.setFillColor(sf::Color::White);

    progress_moveing.setSize(sf::Vector2f(70, 20));
    progress_moveing.setPosition(sf::Vector2f(-70, 780));
    progress_moveing.setFillColor(sf::Color::Blue);
}