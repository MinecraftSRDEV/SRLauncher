void createDDListFromVersionsMap()
{
    for (const auto& pair : versionsData_map)
    {
        std::map <std::string, std::string>tempmap;
        tempmap[pair.first] = pair.first;
        versions_list_ddl.add_options(tempmap); /* send versions list to add_option function in DropDownList class */
        tempmap.clear();
    }
}