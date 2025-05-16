void BBSRevealFunction()
{
    for (const auto& pair : betterbuildsaves_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (betterbuildsaves_list[pair.first].getRevealButtonHitbox().contains(mouse))
        {
            openFolder(selected_instance);
        }
    }
}

void removeBBS(const std::string& instance_id, const std::string& world_id)
{
    fs::path source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "mods" / "BetterBuild" / fs::path(std::string(world_id + ".sav"));

    int result = MessageBoxA(NULL, "Delete this savegame permanently?", "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        try
        {
            fs::remove(source);
            MessageBoxA(NULL, "Savegame successfully removed", "Info", MB_ICONINFORMATION | MB_OK);
            instance_manage(instance_id);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, "Savegame remove FAIL", "Info", MB_ICONERROR | MB_OK);
        }
    }
}

int scanModSaves(const fs::path& dir, int loader,  std::map <int, VanillaSave>& containerPointer)
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
            containerPointer[itr].transportFunction(BBSRevealFunction, containerPointer[itr].REVEAL);
            containerPointer[itr].transportFunction(backupBBSaveAsk, containerPointer[itr].MAKE_BACKUP);
            containerPointer[itr].transportFunction(removeBBSAsk, containerPointer[itr].REMOVE);
            ir_pos += 120;
            itr++;
        }
    }

    return itr;
}