/**
 * This function will create main launcher SFML window.
 * Default framerate is 15 FPS in VideoMode without Vsync.
 *
 * Required parametrs: window size X, Y.
*/
void create_window(int size_x, int size_y)
{
    int screenX = sf::VideoMode::getDesktopMode().width;
    int screenY = sf::VideoMode::getDesktopMode().height;

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

    HWND windowHandle = window.getSystemHandle();

    bool flag1 = false;
    bool flag2 = false;

    if (screenX <= size_x)
    flag1 = true;
    
    if (screenY <= size_y)
    flag2 = true;

    if (flag1 or flag2)
    {
        ShowWindow(windowHandle, SW_MAXIMIZE);
    }
}