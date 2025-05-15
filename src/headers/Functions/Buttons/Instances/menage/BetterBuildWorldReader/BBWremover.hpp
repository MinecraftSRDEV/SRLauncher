void removeBBWorld(const std::string& instance_id, const std::string& world_id)
{
    fs::path source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "mods" / "BetterBuild" / fs::path(std::string(world_id + ".world"));

    int result = MessageBoxA(NULL, "Delete this world permanently?", "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        try
        {
            fs::remove(source);
            MessageBoxA(NULL, "World successfully removed", "Info", MB_ICONINFORMATION | MB_OK);
            instance_manage(instance_id);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, "World remove FAIL", "Info", MB_ICONERROR | MB_OK);
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