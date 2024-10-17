template<typename T>
void readBinary(std::ifstream &file, T &value) {
    file.read(reinterpret_cast<char*>(&value), sizeof(T));
}

void noFunction()
{
    MessageBoxA(NULL, "Function not implemated yet", "info", MB_ICONINFORMATION | MB_OK);
}

std::string readString(std::ifstream &file, int length) {
    std::vector<char> buffer(length);
    file.read(buffer.data(), length);
    return std::string(buffer.begin(), buffer.end());
}

WorldData LoadWorld(const std::string& filepath) {
    WorldData worldData = {};
    
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filepath << std::endl;
        return worldData;
    }

    int32_t num;
    
    // Odczyt wersji mapy (int16)
    readBinary(file, worldData.version);
    
    // Odczyt, czy poziom jest zablokowany (bool)
    readBinary(file, worldData.levelLocked);
    
    if (worldData.levelLocked) {
        // Odczyt długości hasła (int32)
        int32_t passwordLength;
        readBinary(file, passwordLength);
        
        // Odczyt hasła (string o długości passwordLength)
        worldData.levelPassword = readString(file, passwordLength);
    }
    
    // Pominięcie wartości RemoveWorld (bool)
    file.seekg(1, std::ios::cur);
    
    // Odczyt ilości obiektów (int32)
    readBinary(file, worldData.objectCount);

    // Pomiń dane dotyczące obiektów
    for (int i = 0; i < worldData.objectCount; ++i) {
        int32_t stringLength, num5;
        readBinary(file, stringLength);
        
        // Pomiń nazwę obiektu
        file.seekg(stringLength, std::ios::cur);
        
        // Pomiń resztę danych o obiekcie
        file.seekg(4 + 12 + 12 + 12, std::ios::cur);
    }

    // Odczyt ilości spawnerów (int32)
    readBinary(file, worldData.spawnerCount);

    // Pomiń dane dotyczące spawnerów
    for (int i = 0; i < worldData.spawnerCount; ++i) {
        // Pomiń pozycję spawnera (Vector3)
        file.seekg(12, std::ios::cur);
        
        // Pomiń MinSpawns, MaxSpawns, SpawnInterval, SpawnIdCount (int32, float, int32)
        file.seekg(4 + 4 + 4 + 4, std::ios::cur);
        
        int32_t spawnIdCount;
        readBinary(file, spawnIdCount);
        
        // Pomiń listę SpawnIds
        file.seekg(4 * spawnIdCount, std::ios::cur);
    }

    file.close();
    return worldData;
}

void setAndPositionMngMainTexts(const std::string& m2, const std::string& m3, const std::string& m4, const std::string& m5)
{
    MNG_Instance_name_text.setString("Instance name: " + m2);
    MNG_Instance_saves_text.setString("Vanilla saves count: " + m3);
    MNG_instance_mods_own_text.setString("Instance installed mods: " + m4);
    MNG_instance_mods_launcher_text.setString("Launcher mods: " + m5);

    MNG_Instance_name_text.setPosition(130 + (575 - MNG_Instance_name_text.getLocalBounds().width / 2), 100);
    MNG_Instance_saves_text.setPosition(130 + (575 - MNG_Instance_saves_text.getLocalBounds().width / 2), 150);
    MNG_instance_mods_own_text.setPosition(130 + (575 - MNG_instance_mods_own_text.getLocalBounds().width / 2), 200);
    MNG_instance_mods_launcher_text.setPosition(130 + (575 - MNG_instance_mods_launcher_text.getLocalBounds().width / 2), 250);
    bbw_tittle_text.setPosition(130 + (575 - bbw_tittle_text.getLocalBounds().width / 2), 300);
}

void eraseMngMainTexts()
{
    MNG_Instance_name_text.setString("");
    MNG_Instance_saves_text.setString("");
    MNG_instance_mods_own_text.setString("");
    MNG_instance_mods_launcher_text.setString("");
}

int add_mod_to_list(int last_mod_ir_pos, const auto& entry, const fs::path& folderName, int loaderType, const std::string& instanceID)
{
    ModAttribs mod;
    std::string output = entry.path().filename().replace_extension().string();
    log_message(output, LOG_TYPES::LOG_INFO);
    mod.modName = output;
    mod.SRmodVersion = folderName.filename().string();
    
    switch (loaderType)
    {
        case 0:
        {
            mod.modType = "Saty' s mod tool Mod";
            break;
        }
        case 1:
        {
            mod.modType = "Saty' s mod loader Mod";
            break;
        }
        case 2:
        {
            mod.modType = "SRML Mod";
            break;
        }
        case 3:
        {
            mod.modType = "UMF Mod";
            break;
        }

        if (mod.SRmodVersion == instances_list[instanceID].getVer())
        {
            mod.compatybile = true;
        }
        else
        {
            mod.compatybile = false;
        }
    }
    
    InstanceMods_list[output].create(700, last_mod_ir_pos, mod, font, theme_selected);

    instance_mods_folder_list.emplace_back(mod);

    return 60;
}

void loadLauncherMods(const std::string& selected_instance_id)
{
    LauncherMods_list.clear();
    try
    {
        int last_mod_ir_pos = 20;
        for (const auto& entry : fs::directory_iterator(SMTFolder_path))
        {
            fs::path folderPath = SMTFolder_path / entry.path();
            if (fs::is_directory(folderPath))
            {
                for (const auto& modEntry : fs::directory_iterator(folderPath))
                {
                    if (modEntry.is_regular_file() and modEntry.path().filename().extension() == ".dll")
                    {
                        last_mod_ir_pos += add_mod_to_list(last_mod_ir_pos, modEntry, folderPath, 0, selected_instance_id);
                    }
                }
                
            }
        }

        for (const auto& entry : fs::directory_iterator(SMLFolder_path))
        {
            fs::path folderPath = SMTFolder_path / entry.path();
            if (fs::is_directory(folderPath))
            {
                for (const auto& modEntry : fs::directory_iterator(folderPath))
                {
                    if (modEntry.is_regular_file() and modEntry.path().filename().extension() == ".dll")
                    {
                        last_mod_ir_pos += add_mod_to_list(last_mod_ir_pos, modEntry, folderPath, 1, selected_instance_id);
                    }
                }
                
            }
        }

        for (const auto& entry : fs::directory_iterator(SRMLmodsFolder_path))
        {
            fs::path folderPath = SMTFolder_path / entry.path();
            if (fs::is_directory(folderPath))
            {
                for (const auto& modEntry : fs::directory_iterator(folderPath))
                {
                    if (modEntry.is_regular_file() and modEntry.path().filename().extension() == ".dll")
                    {
                        last_mod_ir_pos += add_mod_to_list(last_mod_ir_pos, modEntry, folderPath, 2, selected_instance_id);
                    }
                }
                
            }
        }

        for (const auto& entry : fs::directory_iterator(UMFmodsFolder_path))
        {
            fs::path folderPath = SMTFolder_path / entry.path();
            if (fs::is_directory(folderPath))
            {
                for (const auto& modEntry : fs::directory_iterator(folderPath))
                {
                    if (modEntry.is_regular_file() and modEntry.path().filename().extension() == ".umf")
                    {
                        last_mod_ir_pos += add_mod_to_list(last_mod_ir_pos, modEntry, folderPath, 3, selected_instance_id);
                    }
                }
                
            }
        }
    }
    catch (fs::filesystem_error e)
    {

    }
}

void loadInstanceData(std::string instance_id, fs::path instance_directory)
{
    InstanceModAttributes attribs = instances_list[instance_id].getModAttributes();

    fs::path instance_mods_directory;

    instance_mods_folder_list.clear();
    InstanceMods_list.clear();
    LauncherMods_list.clear();
    betterbuildworlds_list.clear();

    if (versions_map[instances_list[instance_id].getVer()].mod_support == true)
    {
        if (versions_map[instances_list[instance_id].getVer()].version_type == "pre-release")
        {
            instance_mods_directory = instance_directory / "mods";
            std::map <std::string, std::string> mods_installed;
            mods_installed.clear();

            InstanceMods_list.clear();

            ModAttribs mod;

            try
            {
                int last_mod_ir_pos = 20;
                for (const auto& entry : fs::directory_iterator(instance_mods_directory))
                {
                    if (entry.is_regular_file() and entry.path().filename().extension() == ".dll")
                    {
                        std::string output = entry.path().filename().replace_extension().string();
                        log_message(output, LOG_TYPES::LOG_INFO);
                        mods_installed[output] = output;
                        mod.modName = output;
                        InstanceMods_list[output].create(130, last_mod_ir_pos, mod, font, theme_selected);
                        last_mod_ir_pos += 60;
                    }
                }

                if (mods_installed.count("BetterBuildMod") > 0)
                {
                    bbw_tittle_text.setString("");
                    log_message("BetterBuildMod installed", LOG_TYPES::LOG_INFO);
                    fs::path instance_betterbuild_directory = instance_mods_directory / "BetterBuild";
                    directory_auto(instance_betterbuild_directory);
                    int last_bbsave_entry_y = 5;
                    int iteration = 0;
                    betterbuildworlds_list.clear();

                    for (const auto& entry : fs::directory_iterator(instance_betterbuild_directory))
                    {
                        if (entry.is_regular_file() and entry.path().filename().extension() == ".world")
                        {
                            std::string output = entry.path().string();
                            log_message(output, LOG_TYPES::LOG_INFO);

                            WorldData worldData = LoadWorld(output);

                            worldData.levelname = entry.path().filename().replace_extension().string();

                            betterbuildworlds_list[iteration].create(130, last_bbsave_entry_y, worldData, font);
                            betterbuildworlds_list[iteration].transportFunction(noFunction);
                            last_bbsave_entry_y += 120;
                            iteration++;
                        }
                    }
                }
                else
                {
                    bbw_tittle_text.setString("BetterBuildMod isn't installed");
                    bbw_tittle_text.setPosition(window.getSize().x / 2 - (bbw_tittle_text.getLocalBounds().width / 2) + 130, 380);
                }

                instance_mods_folder_list.emplace_back(mod);
            }
            catch (fs::filesystem_error e)
            {

            }

            loadLauncherMods(instance_id);
        }
        else
        {
            instance_mods_directory = instance_directory / "Mods";
            std::map <std::string, std::string> mods_installed;
            mods_installed.clear();

            InstanceMods_list.clear();

            ModAttribs mod;
            int last_mod_ir_pos = 20;
            try
            {
                for (const auto& entry : fs::directory_iterator(instance_mods_directory))
                {
                    if (entry.is_regular_file() and entry.path().filename().extension() == ".dll")
                    {
                        std::string output = entry.path().filename().replace_extension().string();
                        log_message(output, LOG_TYPES::LOG_INFO);
                        mods_installed[output] = output;
                        mod.modName = output;
                        InstanceMods_list[output].create(130, last_mod_ir_pos, mod, font, theme_selected);
                        last_mod_ir_pos += 60;
                        instance_mods_folder_list.emplace_back(mod);
                    }
                }

                if (mods_installed.count("BetterBuild") > 0)
                {
                    bbw_tittle_text.setString("");
                    log_message("BetterBuild installed", LOG_TYPES::LOG_INFO);
                    fs::path instance_betterbuild_directory = instance_directory / "BetterBuild";
                    directory_auto(instance_betterbuild_directory);
                    int last_bbsave_entry_y = 5;
                    int iteration = 0;
                    betterbuildworlds_list.clear();

                    for (const auto& entry : fs::directory_iterator(instance_betterbuild_directory))
                    {
                        if (entry.is_regular_file() and entry.path().filename().extension() == ".world")
                        {
                            std::string output = entry.path().string();
                            log_message(output, LOG_TYPES::LOG_INFO);

                            WorldData worldData = LoadWorld(output);

                            worldData.levelname = entry.path().filename().replace_extension().string();

                            betterbuildworlds_list[iteration].create(130, last_bbsave_entry_y, worldData, font);
                            betterbuildworlds_list[iteration].transportFunction(noFunction);
                            last_bbsave_entry_y += 120;
                            iteration++;
                        }
                    }
                }
                else
                {
                    bbw_tittle_text.setString("BetterBuild isn't installed");
                    bbw_tittle_text.setPosition(window.getSize().x / 2 - (bbw_tittle_text.getLocalBounds().width / 2) + 130, 380);
                }
            }
            catch (fs::filesystem_error e)
            {

            }
            try
            {
                mod.compatybile = false;
                mod.modName.erase();
                mod.modType.erase();
                mod.SRmodVersion.erase();

                instance_mods_directory = instance_directory / "SRML" / "Mods";

                for (const auto& entry : fs::directory_iterator(instance_mods_directory))
                {
                    if (entry.is_regular_file() and entry.path().filename().extension() == ".dll")
                    {
                        std::string output = entry.path().filename().replace_extension().string();
                        log_message(output, LOG_TYPES::LOG_INFO);
                        mods_installed[output] = output;
                        mod.modName = output;
                        InstanceMods_list[output].create(130, last_mod_ir_pos, mod, font, theme_selected);
                        last_mod_ir_pos += 60;
                        instance_mods_folder_list.emplace_back(mod);
                    }
                }
            }
            catch (fs::filesystem_error e)
            {

            }
            try
            {
                mod.compatybile = false;
                mod.modName.erase();
                mod.modType.erase();
                mod.SRmodVersion.erase();

                instance_mods_directory = instance_directory / "uModFramework" / "Mods";

                for (const auto& entry : fs::directory_iterator(instance_mods_directory))
                {
                    if (entry.is_regular_file() and entry.path().filename().extension() == ".umfmod")
                    {
                        std::string output = entry.path().filename().replace_extension().string();
                        log_message(output, LOG_TYPES::LOG_INFO);
                        mods_installed[output] = output;
                        mod.modName = output;
                        InstanceMods_list[output].create(130, last_mod_ir_pos, mod, font, theme_selected);
                        last_mod_ir_pos += 60;
                        instance_mods_folder_list.emplace_back(mod);
                    }
                }
            }                
            catch (fs::filesystem_error e)
            {

            }

            loadLauncherMods(instance_id);
        }
    }
    else
    {
        bbw_tittle_text.setString("This instance doesn't support mods");
        bbw_tittle_text.setPosition(window.getSize().x / 2 - (bbw_tittle_text.getLocalBounds().width / 2) + 130, 380);
    }

    setAndPositionMngMainTexts(instance_id, "UNKNOWN", std::to_string(InstanceMods_list.size()), std::to_string(LauncherMods_list.size()));

    instanceDataLoading = false;
}

void instance_manage(std::string instance_id)
{
    eraseMngMainTexts();
    bbw_tittle_text.setString("");
    selected_instance = instances_list[instance_id].getID();
    if (mounted_instance == instances_list[instance_id].getID())
    {
        MessageBoxA(NULL, "Unmount this instance first!", "Error", MB_ICONERROR | MB_OK);
    }
    else
    {
        UI_current = ManageMenu;
        manage_ui = MNG_MAIN_PAGE;

        fs::path instance_directory = instances_dir / fs::path("Slime Rancher_" + instances_list[instance_id].getID());

        dataLoading_text.setString("Loading instance data...");
        dataLoading_text.setPosition((window.getSize().x / 2) - (credits_programming_text.getLocalBounds().width / 2), 320);
        instanceDataLoading = true;
        std::thread loadDataThr(loadInstanceData, instance_id, instance_directory);
        loadDataThr.detach();
    }
}