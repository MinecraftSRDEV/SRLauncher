namespace modsManager
{
    void moveMod(const std::string& instance, const ModAttribs& attribs)
    {
        fs::path source;
        fs::path dest;

        if (attribs.modListType == 0)
        {
            dest = instances_path / fs::path("Slime Rancher_" + instance);
            if (attribs.modType == "Saty' s mod tool Mod")
            {
                source = SMLFolder_path;
                dest = dest / "mods";
            }
            else if (attribs.modType == "Saty' s mod loader Mod")
            {
                source = SMLFolder_path;
                dest = dest / "Mods";
            }
            else if (attribs.modType == "SRML Mod")
            {
                source = SRMLmodsFolder_path;
                dest = dest / "SRML" / "Mods";
            }
            else if (attribs.modType == "UMF Mod")
            {
                source = UMFmodsFolder_path;
                dest = dest / "uModFramework" / "mods";
            }
            else if (attribs.modType == "? Saty' s mod tool Mod ?")
            {
                source = SMTFolder_path;
                dest = dest / "mods";
            }
            else
            {
                MessageBoxA(NULL, tr("IDS_MSG_MODMNG_MOVE_LOADERNOTRECOGNIZED").c_str(), "Error", MB_ICONERROR | MB_OK);
                return;
            }

            source = source / fs::path(attribs.SRmodVersion) / fs::path(attribs.modName + ".dll");
            fs::path destPath = dest;
            dest = dest / fs::path(attribs.modName + ".dll");

            if (!fs::exists(source))
            {
                MessageBoxA(NULL, tr("IDS_MSG_MODMNG_MOVE_NOSOURCE").c_str(), "Error", MB_ICONERROR | MB_OK);
                return;
            }
            if (!fs::exists(destPath) || !fs::is_directory(destPath))
            {
                MessageBoxA(NULL, tr("IDS_MSG_MODMNG_MOVE_NODESTYNATION").c_str(), "Error", MB_ICONERROR | MB_OK);
                return;
            }
        }
        else if (attribs.modListType == 1)
        {
            source = instances_path / fs::path("Slime Rancher_" + instance);
            if (attribs.modType == "Saty' s mod tool Mod")
            {
                dest = SMLFolder_path;
                source = source / "mods";
            }
            else if (attribs.modType == "Saty' s mod loader Mod")
            {
                dest = SMLFolder_path;
                source = source / "Mods";
            }
            else if (attribs.modType == "SRML Mod")
            {
                dest = SRMLmodsFolder_path;
                source = source / "SRML" / "Mods";
            }
            else if (attribs.modType == "UMF Mod")
            {
                dest = UMFmodsFolder_path;
                source = source / "uModFramework" / "mods";
            }
            else if (attribs.modType == "? Saty' s mod tool Mod ?")
            {
                dest = SMTFolder_path;
                source = source / "mods";
            }
            else
            {
                MessageBoxA(NULL, tr("IDS_MSG_MODMNG_MOVE_LOADERNOTRECOGNIZED").c_str(), "Error", MB_ICONERROR | MB_OK);
                return;
            }

            source = source / fs::path(attribs.modName + ".dll");

            if (!fs::exists(source))
            {
                MessageBoxA(NULL, tr("IDS_MSG_MODMNG_MOVE_NOSOURCE").c_str(), "Error", MB_ICONERROR | MB_OK);
                return;
            }
        }

        try
        {
            if (attribs.modListType == 0)
            {
                fs::copy_file(source, dest);
            }
            else
            {
                fs::remove(source);
            }
            log_message("Moved mod: " + attribs.modName, LOG_INFO);
            instance_manage(instance, ManageCategories::MODS_PAGE);
            return;
        }
        catch(const fs::filesystem_error& e)
        {
            std::string error(e.what());
            MessageBoxA(NULL, std::string(tr("IDS_MSG_MODMNG_MOVE_FAIL") + error).c_str(), "Error", MB_ICONERROR | MB_OK);
            log_message("This mod can't be moved:" + error, LOG_ERROR);
            return;
        }
        
    }

    void moveFunction()
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        for (const auto& pair : LauncherMods_list)
        {
            if (LauncherMods_list[pair.first].getAttribs().modListType == 0)
            if (LauncherMods_list[pair.first].getMoveButtonHitbox().contains(mouse))
            {
                moveMod(selected_instance, LauncherMods_list[pair.first].getAttribs());
            }
        }

        for (const auto& pair : InstanceMods_list)
        {
            if (InstanceMods_list[pair.first].getAttribs().modListType == 1)
            if (InstanceMods_list[pair.first].getMoveButtonHitbox().contains(mouse))
            {
                moveMod(selected_instance, InstanceMods_list[pair.first].getAttribs());
            }
        }
    }
}