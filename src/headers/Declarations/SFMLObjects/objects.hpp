sf::RenderWindow window;
sf::Event event;
sf::Font font;

sf::Texture bg_texture;
sf::Sprite background;

sf::Texture vanilla_saves_icon_tx;
sf::Texture mods_saves_icon_tx;
sf::Texture instance_mods_icon_tx;
sf::Texture launcher_mods_icon_tx;

sf::Image window_icon_img;

sf::Cursor arrowCursor;
sf::Cursor handCursor;
sf::Cursor waitCursor;
sf::Cursor notAllowedCursor;
sf::Cursor crossCursor;

std::map <std::string, sf::Texture> instance_icons_textures;

sf::Sprite loading_icon;