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
}