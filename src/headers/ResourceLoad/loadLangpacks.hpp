fs::path getRuntimePath();

void loadLangpacks()
{
    fs::path langpacks_path = getRuntimePath() / "assets" / "langpacks";

    if (fs::exists(langpacks_path))
    {
        for (auto const& dir_entry : fs::directory_iterator(langpacks_path))
        {
            std::string language = dir_entry.path().filename().replace_extension().string();;
            try
            {
                const auto json = JSON::parseFromFile(langpacks_path.string() + "/" + dir_entry.path().filename().string());

                const auto stringsObject = json.getObject().at("strings");

                for (auto it = stringsObject.getObject().begin(); it != stringsObject.getObject().end(); ++it)
                {
                    const std::string& name = it->first;
                    const JSON& stringObject = it->second;

                    UIlangpacks[language][name] = it->second.getString();
                }

                listOfAvailableLanguages[json.getObject().at("metadata").getObject().at("globalName").getString()] = language;
            }
            catch(const std::exception& e)
            {
               log_message("Langpack \"" + language + " loading error: " + std::string(e.what()), LOG_ERROR);
            }
        } 
    }
}

std::string fixNewlines(const std::string& input) {
    std::string output;
    output.reserve(input.size());

    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == '\\' && i + 1 < input.size() && input[i + 1] == 'n') {
            output.push_back('\n');
            i++;
        } else {
            output.push_back(input[i]);
        }
    }

    return output;
}

std::string tr(const std::string& key)
{
    std::string get = "";
    if (UIlangpacks[launcher_language].count(key) > 0)
    {
        get = UIlangpacks[launcher_language][key];    
    }
    else if (UIlangpacks["en"].count(key) > 0)
    {
        get = UIlangpacks["en"][key];
    }
    else
    {
        get = "STRING NOT FOUND";
    }

    if (!get.empty())
    {
        try
        {
            get = fixNewlines(get);
        }
        catch(std::exception e) {}
    }

    return get;
}