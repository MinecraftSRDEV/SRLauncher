/**
 * This function scan InstanceMods_list map for specyfic mod name
 * 
 * @param id Mod name
 * 
 * @return TRUE if found
 */
int findModInMap(const std::string& id)
{
    for (const auto& pair : InstanceMods_list)
    {
        if (InstanceMods_list[pair.first].getAttribs().modName == id)
        {
            return 1;
        }
    }
    return 0;
}