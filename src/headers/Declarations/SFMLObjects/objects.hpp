sf::RenderWindow window;
sf::Event event;
sf::Font font;

sf::Texture bg_texture;
sf::Sprite background;

sf::Image window_icon_img;

sf::RectangleShape progress_bg;
sf::RectangleShape progress_moveing;

sf::RectangleShape debugWorking;
sf::Text debugIpcElapsedText;

ProgressBar downloadingProgress;

std::map <std::string, sf::Texture> instance_icons_textures;