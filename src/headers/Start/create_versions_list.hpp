void createDDListFromVersionsMap()
{
    for (const auto& pair : versions_map)
    {
        std::map <std::string, std::string>tempmap;
        tempmap[pair.first] = pair.first;
        versions_list.add_options(tempmap); /* send versions list to add_option function in DropDownList class */
        tempmap.clear();
    }
}