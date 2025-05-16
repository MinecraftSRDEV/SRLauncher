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

void removeVanillaWorld(const std::string& instance_id, const std::string& world_id)
{
    fs::path source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "data" / "saves" / fs::path(std::string(world_id + ".sav"));

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

void removeVanillaWorldAsk()
{
    for (const auto& pair : vanillasaves_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (vanillasaves_list[pair.first].getRemoveButtonHitbox().contains(mouse))
        {
            removeVanillaWorld(selected_instance, vanillasaves_list[pair.first].getData().name);
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
            containerPointer[itr].transportFunction(backupVSaveAsk, containerPointer[itr].MAKE_BACKUP);
            containerPointer[itr].transportFunction(removeVanillaWorldAsk, containerPointer[itr].REMOVE);
            ir_pos += 120;
            itr++;
        }
    }

    return itr;
}