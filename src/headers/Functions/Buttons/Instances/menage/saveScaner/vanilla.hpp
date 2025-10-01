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

    int result = MessageBoxA(NULL, tr("IDS_MSG_VSAVE_REMOVE_ASK").c_str(), "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        try
        {
            fs::remove(source);
            MessageBoxA(NULL, tr("IDS_MSG_VSAVE_REMOVE_OK").c_str(), "Info", MB_ICONINFORMATION | MB_OK);
            instance_manage(instance_id, ManageCategories::VANILLA_SAVES);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, tr("IDS_MSG_VSAVE_REMOVE_FAIL").c_str(), "Error", MB_ICONERROR | MB_OK);
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

std::string cutFileName(std::string str)
{
    std::string output;
    try
    {
        size_t length = str.length() - 15;
        size_t pos = length - 2;
        output = str.substr(15, pos);
    }
    catch (std::exception e)
    {
        return "";
    }
    return output;
}

int scanVanillaSaves(const fs::path& dir, SRGamesaveInfo& info,  std::map <int, VanillaSave>& containerPointer)
{
    SavegameData saveData;

    int ir_pos = 20;
    int itr = 0;

    std::vector <std::string> blacklistedEntries;
    
    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (entry.is_regular_file() and entry.path().filename().extension() == ".sav")
        {
            std::string output = entry.path().filename().replace_extension().string();
            saveData = deserializeGameData(entry.path(), info);

            if (info.single_file == false)
            {
                if (output.length() > 15)
                {
                    std::string date;
                    std::string name;
                    try
                    {
                        date = output.substr(0, 15);
                        name = cutFileName(output);
                    }
                    catch( std::exception e) {}
                    
                    blacklistedEntries.emplace_back(date + name + "_1");
                    blacklistedEntries.emplace_back(date + name + "_2");
                    blacklistedEntries.emplace_back(date + name + "_3");
                    blacklistedEntries.emplace_back(date + name + "_4");
                    blacklistedEntries.emplace_back(date + name + "_5");
                }    
            }

            for (const auto& it : blacklistedEntries)
            {
                if (output == it)
                {
                    goto skip;
                }
            }
            containerPointer[itr].create(130, ir_pos, saveData, font);
            containerPointer[itr].transportFunction(VSRevealFunction, containerPointer[itr].REVEAL);
            containerPointer[itr].transportFunction(backupVSaveAsk, containerPointer[itr].MAKE_BACKUP);
            containerPointer[itr].transportFunction(removeVanillaWorldAsk, containerPointer[itr].REMOVE);
            ir_pos += 120;
            itr++;
            skip:
            {

            }
        }
        blacklistedEntries.clear();
    }

    return itr;
}