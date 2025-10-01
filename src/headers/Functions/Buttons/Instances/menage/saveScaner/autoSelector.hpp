void scanGamesaves(const fs::path& dir, const std::string& id, std::map <int, VanillaSave>& containerPointer)
{
    if (versionsData_map[instances_list[id].getVer()].version_type == "pre-release")
    {
        scanVanillaSaves(dir, versionsData_map[instances_list[id].getVer()].savegame_info, containerPointer);
    }
    else
    {
        scanVanillaSaves(dir, versionsData_map[instances_list[id].getVer()].savegame_info, containerPointer); /// placeholder
    }

    if (vanillasaves_list.size() > 0)
    {
        vsc_text.setString("");
    }
    else
    {
        vsc_text.setString(tr("IDS_TEXT_NODATA"));
        vsc_text.setPosition(window.getSize().x / 2 - (vsc_text.getLocalBounds().width / 2) + 130, 380);
    }

    if (betterbuildsaves_list.size() > 0)
    {
        msc_text.setString("");
    }
    else
    {
        msc_text.setString(tr("IDS_TEXT_NODATA"));
        msc_text.setPosition(window.getSize().x / 2 - (msc_text.getLocalBounds().width / 2) + 130, 380);
    }
}