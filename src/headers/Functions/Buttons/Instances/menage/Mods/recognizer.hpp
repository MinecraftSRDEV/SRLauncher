modMeta readModMeta(std::string path)
{
    modMeta meta;

    std::string command = fs::path(runtime_directory / "assets" / "components" / "mods_recognizer" / "SRLmodsRecognizer" / "bin" / "Release" / "net8.0" / "SRLmodsRecognizer.exe").string() + " \"" +path+ "\"";

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return meta;
    }

    std::vector<std::string> List;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        List.emplace_back(buffer);
    }

    try
    {
        const auto& Json = JSON::parse(List[0]);

        // log_message(List[0], LOG_INFO);

        meta.hasOnLoad = Json.getObject().at("hasOnload").getBool();
        meta.hasOnUnload = Json.getObject().at("hasOnUnload").getBool();
        meta.conSRML = Json.getObject().at("conSRML").getBool();
    }
    catch (std::exception e) {}

    return meta;
}

int add_mod_to_list(int last_mod_ir_pos, const auto& entry, const fs::path& folderName, int loaderType, const std::string& instanceID, std::map <std::string, ModClass>& mods_list, std::vector <ModAttribs>& attribs, int Xposition, std::map <int, std::string>& modsIndex, int& index, int listType)
{
    ModAttribs mod;
    modMeta meta;
    std::string output = entry.path().filename().replace_extension().string();
    if (!output.empty())
    {
        // log_message(output, LogTypes::LOG_INFO);
        mod.modName = output;
        mod.SRmodVersion = folderName.filename().string();

        try
        {
            if (entry.path().filename().extension() == ".dll")
            meta = readModMeta(entry.path().string());    
        }
        catch (std::exception e) {}

        mod.compatybile = false;
        mod.modListType = listType;
        
        switch (loaderType)
        {
            case 0:
            {
                mod.modType = "Saty' s mod tool Mod";
                if (instances_list[instanceID].getModAttributes().StaysModtool_installed)
                mod.compatybile = true;
                break;
            }
            case 1:
            {
                mod.modType = "Saty' s mod loader Mod";
                if (instances_list[instanceID].getModAttributes().SatysModLoader_installed)
                mod.compatybile = true;
                break;
            }
            case 2:
            {
                mod.modType = "SRML Mod";
                if (instances_list[instanceID].getModAttributes().SRML_installed)
                mod.compatybile = true;
                break;
            }
            case 3:
            {
                mod.modType = "UMF Mod";
                if (instances_list[instanceID].getModAttributes().UMF_installed)
                mod.compatybile = true;
                break;
            }
            case 4:
            {
                mod.modType = "Unknown";
                mod.SRmodVersion = "Unknown";
                break;
            }
            case 5:
            {
                if (meta.conSRML)
                {
                    mod.modType = "SRML Mod";
                    if (instances_list[instanceID].getModAttributes().SRML_installed)
                    mod.compatybile = true;
                    break;
                }
                if (meta.hasOnLoad)
                {
                    if (meta.hasOnUnload)
                    {
                        mod.modType = "Saty' s mod tool Mod";
                        if (instances_list[instanceID].getModAttributes().StaysModtool_installed)
                        mod.compatybile = true;
                    }
                    else
                    {
                        mod.modType = "? Saty' s mod tool Mod ?";
                        if (instances_list[instanceID].getModAttributes().StaysModtool_installed)
                        mod.compatybile = true;
                    }
                }
                else
                {
                    mod.modType = "Unknown";
                }
                break;
            }
        }

        mod.spoofedName = mod.modName;
        if (mods_list.count(mod.modName) != 0)
        {
            mod.spoofedName = mod.modName + "(" + std::to_string(mods_list.count(mod.modName) + 1) + (")");
        }

        mods_list[mod.spoofedName].create(Xposition, last_mod_ir_pos, mod, font, window, theme_selected);
        mods_list[mod.spoofedName].setFunction(modsManager::moveFunction);
        mods_list[mod.spoofedName].changeButtonType(listType);

        modsIndex[index] = mod.spoofedName;

        // std::string indexpos = std::to_string(index);

        // log_message("mod.modName: " + mod.modName, LOG_INFO);
        // log_message("mod.index: " + indexpos, LOG_INFO);

        index++;

        attribs.emplace_back(mod);

        return 95;    
    }
    
    log_message("Unrecognizable mod index", LogTypes::LOG_ERROR);
    return 0;
}