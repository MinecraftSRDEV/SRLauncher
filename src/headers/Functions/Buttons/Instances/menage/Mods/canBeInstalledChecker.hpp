bool checkIfModCanBeInstalled(const std::string& modName, std::map<std::string, ModClass>& from, std::map<std::string, ModClass>& to)
{
    if (to.count(modName) > 0)
    {
        if (to[modName].canBeInstalled == true)
        {
            from[modName].canBeInstalled = false;
            return false;    
        }
    }
    else 
    {
        if (to[modName].canBeInstalled == false)
        {
            from[modName].canBeInstalled = true;       
        }
    }
    return true;
}

void updateModsList()
{
    // for (const auto& pair : InstanceMods_list)
    // {
    //     checkIfModCanBeInstalled(pair.first, LauncherMods_list, InstanceMods_list);
    // }

    // for (const auto& pair : LauncherMods_list)
    // {
    //     checkIfModCanBeInstalled(pair.first, LauncherMods_list, InstanceMods_list);
    // }
}