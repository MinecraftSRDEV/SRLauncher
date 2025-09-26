namespace miniInstanceList
{
    struct details
    {
        int index = 0;
        std::string name = "";
        std::string lastPlayed = "";
    };

    struct instanceEntry
    {
        std::string name = "";
        std::string version = "";
        std::string iconId = "";
        std::string path_str = "";
        std::string playTime = "";

        fs::path directory_path;
    };

    int lastEntryY = 55;

    std::mutex loaderMutex;

    void statRefresh()
    {
        for(const auto& itr : miniInstancesListMap)
        {
            if (mounted_instance == miniInstancesListMap[itr.first].getID())
            {
                miniInstancesListMap[itr.first].updateStatus(miniInstanceClass::status::Mounted);
            }
            else
            {
                miniInstancesListMap[itr.first].updateStatus(miniInstanceClass::status::Unmounted);
            }
        }
    }

    details getDetails(const auto& json, int index)
    {
        details det;

        try
        {
            det.index = index;
            det.name = json.getObject().at("index" + std::to_string(index)).getObject().at("name").getString();
            det.lastPlayed = json.getObject().at("index" + std::to_string(index)).getObject().at("last").getString();
        }
        catch (std::exception e)
        {

        }

        return det;
    }

    std::map <int, details> getLastPlayedInstances()
    {
        std::map <int, details> output;

        try
        {
            const auto json = JSON::parseFromFile(fs::path(defaultDir / "instances.json").string());

            for (size_t i = 1; i < 6; i++)
            {
                details newDet = getDetails(json, i);
                
                if (!newDet.name.empty())
                {
                    output[i] = newDet;
                }
            }
            
        }
        catch (std::exception e)
        {

        }   

        return output;
    }

    miniInstanceList::attributes addInstance(fs::path path, int itr, std::string lastPlayed)
    {
        instanceEntry inst;
    
        inst.path_str = path.string();
        inst.directory_path= path;
        
        JSON json = JSON::parseFromFile(inst.path_str + "/info.json");

        inst.name = json.getObject().at("name").getString();
        inst.version = json.getObject().at("version").getString();
        
        try
        {
            inst.iconId = json.getObject().at("icon").getString();
        }
        catch(std::exception){}
        if (inst.iconId.empty())
        {
            inst.iconId = "pink";
        }
        try
        {
            inst.playTime = json.getObject().at("playtime").getString();
        }
        catch(std::exception)
        {
            inst.playTime = "0";
        }

        miniInstanceList::attributes entry = miniInstanceList::attributes(instance_icons_textures[inst.iconId], playtime_clock_tx, font, window);

        entry.x = 40;
        entry.y = lastEntryY;
        entry.size_x = 640;
        entry.size_y = 76;
        entry.name = inst.name;
        entry.version = inst.version;
        entry.it_number = itr;
        entry.playtime_count = inst.playTime;
        entry.lastPlayed = lastPlayed;

        lastEntryY += 76;
        return entry;
    }

    std::vector <miniInstanceList::attributes> dataStorage;

    void loadMiniInstancesList()
    {
        std::map <int, miniInstanceList::details> instances = getLastPlayedInstances();

        for (const auto& pair : instances)
        {
            fs::path entryPath = fs::path(instances_dir / fs::path("Slime Rancher_" + pair.second.name));

            if (check_directory_exists(entryPath, false) == true)
            {
                if (fs::exists(fs::path(entryPath.string() + "/info.json")))
                {
                    dataStorage.emplace_back(addInstance(entryPath.string(), pair.second.index, pair.second.lastPlayed));
                }
            }
            else
            {
                fs::path potentialSteamPath = fs::path(steam_game_dir) / "Slime Rancher";

                if (check_directory_exists(potentialSteamPath, false) == true)
                {
                    if (fs::exists(fs::path(potentialSteamPath.string() + "/info.json")))
                    {
                        dataStorage.emplace_back(addInstance(potentialSteamPath.string(), pair.second.index, pair.second.lastPlayed));
                    }
                }
            }
        }

        miniInstanceList::dataLoading = false;
        miniInstanceList::dataFetched  = false;
        loadingAnimationDisplay = false;
    }

    void prepare()
    {
        MainpageElements::lastPlayed::loadingMiniInstancesText.setString(tr("IDS_TEXT_MINIINST_LOADINGDATA"));
        MainpageElements::lastPlayed::loadingMiniInstancesText.setPosition((MainpageElements::lastPlayed::mouseBox.getSize().x / 2) - (MainpageElements::lastPlayed::loadingMiniInstancesText.getLocalBounds().width / 2), 180);

        loadingAnimationDisplay = true;
        loadingAnimation::setupLoadingAnimation(MainpageElements::lastPlayed::loadingMiniInstancesText.getPosition(), "pink");

        std::lock_guard<std::mutex> lock(miniInstanceList::loaderMutex);
        miniInstanceList::lastEntryY = 55;
        miniInstanceList::dataLoading = true;
        dataStorage.clear();
        miniInstancesListMap.clear();

        std::thread loadThread(loadMiniInstancesList);
        loadThread.detach();
    }

    void ifProcessFinished()
    {
        if (!miniInstanceList::dataFetched)
        {
            if (!miniInstanceList::dataLoading)
            {
                for (const auto& storage : dataStorage)
                {
                    std::lock_guard<std::mutex> lock(miniInstanceList::loaderMutex);
                    miniInstancesListMap[std::to_string(storage.it_number)].create(storage);
                }

                statRefresh();

                miniInstanceList::dataFetched = true;
            }    
        }
    }
}