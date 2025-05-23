SavegameData deserializeGameData(const fs::path& filepath)
{
    SavegameData data;

    data.name = filepath.filename().replace_extension().string();

    try
    {
        data.last_played = convertTmToString(convertStringToDate(data.name.substr(0, 15)));
        data.name = data.name.substr(15);
    }
    catch (std::exception e) {
        data.last_played = UNKNOWN;
    }

    std::vector <std::string> fileContains;
    fileContains.clear();

    std::ifstream file;
    file.open(filepath);
    std::string readed;
    while (getline(file, readed))
    {
        fileContains.emplace_back(readed);
    }
    file.close();

    for (const auto& pair : versionsData_map)
    {
        for (const auto& filecon : fileContains)
        {
            size_t position = filecon.find(pair.second.version_name);
            if (position != std::string::npos)
            {
                try
                {
                    data.version = filecon.substr(position, pair.second.version_name.length());
                }
                catch (std::out_of_range e)
                {
                    data.version = UNKNOWN;
                }
            }
        }
    }

    if (data.version.empty())
    {
        data.version = UNKNOWN;
    }

    return data;
}