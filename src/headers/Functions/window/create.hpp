/**
 * This function will create main launcher SFML window.
 * Default framerate is 15 FPS in VideoMode without Vsync.
 *
 * Required parametrs: window size X, Y.
*/
void create_window(int size_x, int size_y)
{
    if (window.isOpen())
    {
        window.close();
    }

    window.create(sf::VideoMode(size_x, size_y), "SRLauncher");
	window.setFramerateLimit(15);
    window.setActive(true);
    window.setVisible(true);

    window_icon_img.loadFromFile("./assets/resources/icon.png");
    window.setIcon(window_icon_img.getSize().x, window_icon_img.getSize().y, window_icon_img.getPixelsPtr());
}