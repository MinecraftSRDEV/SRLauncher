bool resignWorld(std::string path, std::string at)
{
    try
    {
        std::ifstream inputFile(path, std::ios::binary);
        std::vector<char> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        inputFile.close();

        std::string data(buffer.begin(), buffer.end());
        size_t pos = 7;

        std::copy(instance_UID.begin(), instance_UID.end(), buffer.begin() + pos);

        std::ofstream out(at, std::ios::binary);
        out.write(buffer.data(), buffer.size());
        out.close();

        buffer.clear();
        data.erase();
        return true;
    }
    catch (std::exception e) {}
    return false;
}

void resignBBWorld(const std::string& instance_id, const std::string& world_id)
{
    fs::path source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "mods" / "BetterBuild" / fs::path(std::string(world_id + ".world"));

    int result = MessageBoxA(NULL, "Resign this world to your UID?", "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        try
        {
            fs::path pathToResigned = source;
            pathToResigned = pathToResigned.replace_filename(source.filename().replace_extension("").string() + "_resigned");
            if (resignWorld(source.string(), pathToResigned.string() + ".world"))
            {
                MessageBoxA(NULL, "World resigned successfully\n\n Now you can edit it in game\nTo completly remove lock open world in editor and uncheck \"World locked\" checkbox", "Info", MB_ICONINFORMATION | MB_OK);
            }
            else
            {
                MessageBoxA(NULL, "World resign FAIL", "Error", MB_ICONERROR | MB_OK);
            }
            instance_manage(instance_id, ManageCategories::BETTERBUILD_WORLDS);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, "World resign FAIL", "Info", MB_ICONERROR | MB_OK);
        }
    }
}

void resignBBWAsk()
{
    for (const auto& pair : betterbuildworlds_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (betterbuildworlds_list[pair.first].getUnlockButtonHitbox().contains(mouse))
        {
            resignBBWorld(selected_instance, betterbuildworlds_list[pair.first].getData().levelname);
        }
    }
}