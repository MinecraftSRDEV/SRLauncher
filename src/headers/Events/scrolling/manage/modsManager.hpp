void scrollInstanceMods(sf::Event& event, sf::Vector2f& mouse_pos)
{
    if (event.type == sf::Event::MouseWheelMoved)
    {
        int mouse_scroll = event.mouseWheel.delta;

        if (mouse_scroll > 0)
        {
            int mp = event.mouseWheel.delta;
            while (mp > 0)
            {
                if (InstanceMods_list[InstanceModsIndexing[0]].getPOsition().y < 0)
                {
                    int pos = 0;
                    while (pos < InstanceModsIndexing.size())
                    {
                        InstanceMods_list[InstanceModsIndexing[pos]].changePosition(InstanceMods_list[InstanceModsIndexing[pos]].getPOsition().x, InstanceMods_list[InstanceModsIndexing[pos]].getPOsition().y + 95);
                        pos++;
                    }
                }
                mp--;
            }
        }
        else
        {
            int mp = event.mouseWheel.delta;
            while (mp < 0)
            {
                int last = InstanceModsIndexing.size() - 1;
                if (InstanceMods_list[InstanceModsIndexing[last]].getPOsition().y + InstanceMods_list[InstanceModsIndexing[last]].getHitbox().height > 800)
                {
                    int pos = 0;
                    while (pos < InstanceModsIndexing.size())
                    {
                        InstanceMods_list[InstanceModsIndexing[pos]].changePosition(InstanceMods_list[InstanceModsIndexing[pos]].getPOsition().x, InstanceMods_list[InstanceModsIndexing[pos]].getPOsition().y - 95);
                        pos++;
                    }
                }
                mp++;
            }
        }
    }
}

void scrollLauncherMods(sf::Event& event, sf::Vector2f& mouse_pos)
{
    if (event.type == sf::Event::MouseWheelMoved)
    {
        int mouse_scroll = event.mouseWheel.delta;

        if (mouse_scroll > 0)
        {
            int mp = event.mouseWheel.delta;
            while (mp > 0)
            {
                if (LauncherMods_list[LauncherModsIndexing[0]].getPOsition().y < 0)
                {
                    int pos = 0;
                    while (pos < LauncherModsIndexing.size())
                    {
                        LauncherMods_list[LauncherModsIndexing[pos]].changePosition(LauncherMods_list[LauncherModsIndexing[pos]].getPOsition().x, LauncherMods_list[LauncherModsIndexing[pos]].getPOsition().y + 95);
                        pos++;
                    }    
                }
                mp--;
            }
        }
        else
        {
            int mp = event.mouseWheel.delta;
            while (mp < 0)
            {
                int last = LauncherModsIndexing.size() - 1;
                if (LauncherMods_list[LauncherModsIndexing[last]].getPOsition().y + LauncherMods_list[LauncherModsIndexing[last]].getHitbox().height > 800)
                {
                    int pos = 0;
                    while (pos < LauncherModsIndexing.size())
                    {
                        LauncherMods_list[LauncherModsIndexing[pos]].changePosition(LauncherMods_list[LauncherModsIndexing[pos]].getPOsition().x, LauncherMods_list[LauncherModsIndexing[pos]].getPOsition().y - 95);
                        pos++;
                    }
                }
                mp++;
            }
        }
    }
}
