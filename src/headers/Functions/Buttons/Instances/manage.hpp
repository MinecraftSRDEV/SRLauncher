namespace DebugBridge
{
    void installDebugPath();
    void uninstallDebugPath();
}

/**
 * Async main function responsible for all loaders
 * 
 * @param instance_id name of selected instance
 * @param instance_directory directory of selected instance
 */
void loadInstanceData(std::string instance_id, fs::path instance_directory, int scene)
{
    window.setMouseCursor(waitCursor);
    InstanceModAttributes attribs = instances_list[instance_id].getModAttributes();

    fs::path instance_mods_directory;
    fs::path instance_save_directory = instance_directory / "data" / "saves";
    fs::path instance_managed_directory = instance_directory / "SlimeRancher_Data" / "Managed";
    fs::path instance_modsave_directory;

    ManageDebug::assemblyDataText.setString("");

    instance_mods_folder_list.clear();
    mods_folder_data_list.clear();
    InstanceMods_list.clear();
    LauncherMods_list.clear();
    InstanceModsIndexing.clear();
    LauncherModsIndexing.clear();
    betterbuildworlds_list.clear();
    betterbuildsaves_list.clear();
    vanillasaves_list.clear();
    
    bool betterBuildStatus = false;
    std::string betterBuildUid = "Unknown";

    int last_mod_ir_pos = 20;
    int last_mod_index = 0;


    if (versionsData_map[instances_list[instance_id].getVer()].version_type == "pre-release")
    {
        instance_mods_directory = instance_directory / "mods";
        instance_modsave_directory = instance_mods_directory / "BetterBuild";
        try
        {
            scanModsFolder(instance_mods_directory, ".dll", last_mod_ir_pos, instance_id, 5, InstanceMods_list, instance_mods_folder_list, 130, InstanceModsIndexing, last_mod_index, 1);
            
            betterBuildStatus = checkBetterBuildInstalled("BetterBuildMod", instance_mods_directory);
            if (betterBuildStatus)
            {
                scanBetterBuildWorlds(instance_modsave_directory, old_loader);
                betterBuildUid = getBetterBuildUID(instance_modsave_directory);    

            }
            else
            {
                betterBuildUid = "Not installed";
            }

            instance_UID = betterBuildUid;

            scanModSaves(instance_modsave_directory, old_loader, betterbuildsaves_list);
        }
        catch (fs::filesystem_error e) {}

        loadLauncherMods(instance_id);
    }
    else
    {
        try
        {
            instance_mods_directory = instance_directory / "Mods";
            instance_modsave_directory = instance_directory / "BetterBuild";
            scanModsFolder(instance_mods_directory, ".dll", last_mod_ir_pos, instance_id, 5, InstanceMods_list, instance_mods_folder_list, 130, InstanceModsIndexing, last_mod_index, 1);
            betterBuildStatus = checkBetterBuildInstalled("BetterBuild", instance_mods_directory);
            if (betterBuildStatus)
            {
                scanBetterBuildWorlds(instance_modsave_directory, new_loader);
                betterBuildUid = "Not available in this mod version";    
            }
            else
            {
                betterBuildUid = "Not installed";
            }
            scanModSaves(instance_modsave_directory, new_loader, betterbuildsaves_list);
        }
        catch (fs::filesystem_error e) {}

        try
        {
            instance_mods_directory = instance_directory / "SRML" / "Mods";
            scanModsFolder(instance_mods_directory, ".dll", last_mod_ir_pos, instance_id, 5, InstanceMods_list, instance_mods_folder_list, 130, InstanceModsIndexing, last_mod_index, 1);
        }
        catch (fs::filesystem_error e) {}

        try
        {
            instance_mods_directory = instance_directory / "uModFramework" / "Mods";
            scanModsFolder(instance_mods_directory, ".umfmod", last_mod_ir_pos, instance_id, UMF_ld, InstanceMods_list, instance_mods_folder_list, 130, InstanceModsIndexing, last_mod_index, 1);
        }
        catch (fs::filesystem_error e) {}

        loadLauncherMods(instance_id);
    }
    

    correctModsIndexesPosition(LauncherMods_list, LauncherModsIndexing);
    correctModsIndexesPosition(InstanceMods_list, InstanceModsIndexing);

    ManageDebug::debugPatchStatusText.setString("Patch status: Not installed");
    ManageDebug::debugPatchButton.setText("Apply patch");
    ManageDebug::debugPatchButton.setFunction(DebugBridge::installDebugPath);
    ManageDebug::assemblyDataText.setString(runAssemblyReader(instance_managed_directory.string() + "/Assembly-CSharp.dll"));
    try
    {
        size_t count = ManageDebug::assemblyDataText.getString().find("DebugBridge");
        if (count != std::string::npos)
        {
            ManageDebug::debugPatchStatusText.setString("Patch status: Installed");
            ManageDebug::debugPatchButton.setText("Uninstall patch");
            ManageDebug::debugPatchButton.setFunction(DebugBridge::uninstallDebugPath);
        }
    } catch(std::exception e) {}

    updateModsList();

    scanGamesaves(instance_save_directory, instance_id, vanillasaves_list);

    scanBackups(instance_id);

    setAndPositionMngMainTexts({instance_id, instances_list[instance_id].getIconTexture(), std::to_string(InstanceMods_list.size()), std::to_string(vanillasaves_list.size()), std::to_string(betterbuildsaves_list.size()), std::to_string(LauncherMods_list.size()), betterBuildStatus, betterBuildUid});

    instancesLoader::instanceDataLoading = false;
    loadingAnimationDisplay = false;
    
    manage_ui = scene;
    window.setMouseCursor(arrowCursor);
}

/**
 * Main function triggered when manage button on instance was clicked.
 * 
 * @param instance_id clicked instance name
 */
void instance_manage(std::string instance_id, int scene)
{
    if (mounted_instance == instances_list[instance_id].getID())
    {
        MessageBoxA(NULL, instdi::UNMOUNT_MSG.c_str(), "Error", MB_ICONERROR | MB_OK);
    }
    else
    {
        eraseMngMainTexts();
        bbw_tittle_text.setString("");
        selected_instance = instances_list[instance_id].getID();

        UI_current = ManageMenu;
        manage_ui = MNG_MAIN_PAGE;

        fs::path instance_directory = instances_dir / fs::path("Slime Rancher_" + instances_list[instance_id].getID());

        dataLoading_text.setString("Loading instance data...");
        dataLoading_text.setPosition((window.getSize().x / 2) - (SettingsElemets::subcats::credits::credits_programming_text.getLocalBounds().width / 2), 320);
        instancesLoader::instanceDataLoading = true;
        loadingAnimationDisplay = true;
        loadingAnimation::setupLoadingAnimation(dataLoading_text.getPosition(), "pink");

        std::thread loadDataThr(loadInstanceData, instance_id, instance_directory, scene);
        loadDataThr.detach();
    }
}