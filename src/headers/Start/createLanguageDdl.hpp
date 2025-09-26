void createLanguageDdl()
{
    for (const auto& pair : listOfAvailableLanguages)
    {
        if (pair.second != "en")
        {
            std::map <std::string, std::string>tempmap;
            tempmap[pair.first] = pair.second;
            SettingsElemets::subcats::general::languages_list_ddl.add_options(tempmap);
            tempmap.clear();    
        }
    }
}