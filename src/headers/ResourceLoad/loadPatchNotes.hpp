void positionListElements()
{
    int ver_last_x = 113;
    int ver_last_y = 85;
    for (const auto& pair : versions_pachnotes_list)
    {
        if (show_prerelease_version == false)
        {
            if (versionsData_map[versions_pachnotes_list[pair.first].getVersion()].version_type == "pre-release")
            {
                continue;
            }    
        }
        
        versions_pachnotes_list[pair.first].reposition(ver_last_x, ver_last_y);
        ver_last_x += 266;
        if (ver_last_x > 940)
        {
            ver_last_x = 113;
            ver_last_y += 190;
        }
    }
}

void loadVersionPachnotes(const std::string& name, int iteration)
{
    std::string path_toNotes = "./assets/resources/pachNotes/" + name + ".txt";
    std::string path_toImg = "./assets/resources/pachNotes/" + name + ".png";
    std::ifstream file;
    file.open(path_toNotes.c_str());
    if (file)
    {
        std::string full;
        full.erase();
        std::string line;
        while(getline(file, line))
        {
            std::vector <std::string> lines;
            while (line.length() > 100)
            {
                std::string output = line.substr(0, 89);
                lines.emplace_back(output);
                line = line.substr(89);
            }
            lines.emplace_back(line);

            for (auto& it : lines)
            {
                full += it;
                full += "\n";
            }
            lines.clear();
            
        }

        sf::Texture imageTx;
        if (fs::exists(fs::path(path_toImg)))
        {
            imageTx.loadFromFile(path_toImg.c_str());
        }
        else
        {
            imageTx.loadFromFile("./assets/resources/pachNotes/noImage.png");
        }
        
        versions_pachnotes_list[iteration].create(0, 0, font, imageTx, name, full, theme_selected);
    }
    file.close();
    positionListElements();
}