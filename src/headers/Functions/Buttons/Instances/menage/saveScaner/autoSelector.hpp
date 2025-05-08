void scanGamesaves(const fs::path& dir, const std::string& id, std::map <int, VanillaSave>& containerPointer)
{
    if (versionsData_map[instances_list[id].getVer()].version_type == "pre-release")
    {
        scanVanillaSaves(dir, old_loader, containerPointer);
    }
    else
    {
        scanVanillaSaves(dir, new_loader, containerPointer); /// placeholder
    }

    if (vanillasaves_list.size() > 0)
    {
        vsc_text.setString("");
    }
    else
    {
        vsc_text.setString("There is no data.");
        vsc_text.setPosition(window.getSize().x / 2 - (vsc_text.getLocalBounds().width / 2) + 130, 380);
    }

    if (betterbuildsaves_list.size() > 0)
    {
        msc_text.setString("");
    }
    else
    {
        msc_text.setString("There is no data.");
        msc_text.setPosition(window.getSize().x / 2 - (msc_text.getLocalBounds().width / 2) + 130, 380);
    }
}