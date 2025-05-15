void display_window()
{
    window.display();

    if (screen_refresh_count < 100)
    {
        screen_refresh_count++;    
    }
}