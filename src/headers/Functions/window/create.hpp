void create_window(int size_x, int size_y)
{
    if (window.isOpen())
    {
        window.close();
    }

    window.create(sf::VideoMode(size_x, size_y), "SRLauncher");
	window.setFramerateLimit(15);
}