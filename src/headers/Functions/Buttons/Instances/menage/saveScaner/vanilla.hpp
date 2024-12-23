void openFolder(const std::string& instance_id)
{
    fs::path source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "data" / "saves";
    std::string command = "explorer " + source.string();
    system(command.c_str());
}

void VSRevealFunction()
{
    for (const auto& pair : vanillasaves_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (vanillasaves_list[pair.first].getRevealButtonHitbox().contains(mouse))
        {
            openFolder(selected_instance);
        }
    }
}

int scanVanillaSaves(const fs::path& dir, int loader,  std::map <int, VanillaSave>& containerPointer)
{
    SavegameData saveData;

    int ir_pos = 20;
    int itr = 0;
    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (entry.is_regular_file() and entry.path().filename().extension() == ".sav")
        {
            std::string output = entry.path().filename().replace_extension().string();
            saveData = deserializeGameData(entry.path());
            containerPointer[itr].create(130, ir_pos, saveData, font);
            containerPointer[itr].transportFunction(VSRevealFunction, containerPointer[itr].REVEAL);
            ir_pos += 120;
            itr++;
        }
    }

    return itr;
}