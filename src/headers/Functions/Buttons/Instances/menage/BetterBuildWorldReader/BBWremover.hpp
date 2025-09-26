void removeBBWorld(const std::string& instance_id, const std::string& world_id)
{
    fs::path source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "mods" / "BetterBuild" / fs::path(std::string(world_id + ".world"));

    int result = MessageBoxA(NULL, tr("IDS_MSG_BBW_REMOVE_ASK").c_str(), "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        try
        {
            fs::remove(source);
            MessageBoxA(NULL, tr("IDS_MSG_BBW_REMOVE_OK").c_str(), "Info", MB_ICONINFORMATION | MB_OK);
            instance_manage(instance_id, ManageCategories::BETTERBUILD_WORLDS);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, tr("IDS_MSG_BBW_REMOVE_FAIL").c_str(), "Info", MB_ICONERROR | MB_OK);
        }
    }
}

void removeBBWAsk()
{
    for (const auto& pair : betterbuildworlds_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (betterbuildworlds_list[pair.first].getRemoveButtonHitbox().contains(mouse))
        {
            removeBBWorld(selected_instance, betterbuildworlds_list[pair.first].getData().levelname);
        }
    }
}

void removeBBSave(const std::string& instance_id, const std::string& world_id)
{
    fs::path source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "mods" / "BetterBuild" / fs::path(std::string(world_id + ".sav"));

    int result = MessageBoxA(NULL, tr("IDS_MSG_BBS_REMOVE_ASK").c_str(), "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        try
        {
            fs::remove(source);
            MessageBoxA(NULL, tr("IDS_MSG_BBS_REMOVE_OK").c_str(), "Info", MB_ICONINFORMATION | MB_OK);
            instance_manage(instance_id, ManageCategories::BETTERBUILD_SAVES);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, tr("IDS_MSG_BBS_REMOVE_FAIL").c_str(), "Info", MB_ICONERROR | MB_OK);
        }
    }
}

void removeBBSAsk()
{
    for (const auto& pair : betterbuildsaves_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (betterbuildsaves_list[pair.first].getRemoveButtonHitbox().contains(mouse))
        {
            removeBBSave(selected_instance, betterbuildsaves_list[pair.first].getData().name);
        }
    }
}