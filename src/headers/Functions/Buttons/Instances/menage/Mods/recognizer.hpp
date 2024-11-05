int add_mod_to_list(int last_mod_ir_pos, const auto& entry, const fs::path& folderName, int loaderType, const std::string& instanceID, std::map <std::string, ModClass>& mods_list, std::vector <ModAttribs>& attribs, int Xposition)
{
    ModAttribs mod;
    std::string output = entry.path().filename().replace_extension().string();
    log_message(output, LogTypes::LOG_INFO);
    mod.modName = output;
    mod.SRmodVersion = folderName.filename().string();
    
    switch (loaderType)
    {
        case 0:
        {
            mod.modType = "Saty' s mod tool Mod";
            break;
        }
        case 1:
        {
            mod.modType = "Saty' s mod loader Mod";
            break;
        }
        case 2:
        {
            mod.modType = "SRML Mod";
            break;
        }
        case 3:
        {
            mod.modType = "UMF Mod";
            break;
        }
        case 4:
        {
            mod.modType = "Unknown";
            mod.SRmodVersion = "Unknown";
            break;
        }

        if (mod.SRmodVersion == instances_list[instanceID].getVer())
        {
            mod.compatybile = true;
        }
        else
        {
            mod.compatybile = false;
        }
    }
    
    mods_list[output].create(Xposition, last_mod_ir_pos, mod, font, theme_selected);

    attribs.emplace_back(mod);

    return 60;
}