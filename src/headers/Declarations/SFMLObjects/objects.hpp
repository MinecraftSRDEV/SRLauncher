sf::RenderWindow window;
sf::Event event;
sf::Font font;

sf::Texture bg_texture;
sf::Sprite background;

sf::RectangleShape progress_bg;
sf::RectangleShape progress_moveing;

std::map <std::string, sf::Texture> instance_icons_textures;