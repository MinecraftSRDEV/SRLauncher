std::string deformatDate(int value, int max)
{
    if (value < max)
    {
        return "0" + std::to_string(value);
    }
    return std::to_string(value);
}

void backupRestore(const std::string& instance_id, const BackupData data)
{
    fs::path source;
    std::string backup_text;
    std::string backup_directory;
    std::string file_extension;

    switch (data.type)
    {
        case BackupTypes::BBworld_backup:
        {
            source = backups_path / "instances" / instance_id / "mods" / "BetterBuild" / fs::path(std::string(data.filename + ".world"));
            backup_text = tr("IDS_MSG_BACKUP_RESTORE_WORLD_ASK") + std::to_string(fs::file_size(source)) + " bytes";
            backup_directory = "BBW";
            file_extension = ".world";
            break;
        }
        case BackupTypes::BBsave_backup:
        {
            source = backups_path / "instances" / instance_id / "mods" / "BetterBuild" / fs::path(std::string(data.filename + ".sav"));
            backup_text = tr("IDS_MSG_BACKUP_RESTORE_SAVE_ASK") + std::to_string(fs::file_size(source)) + " bytes";
            backup_directory = "BBS";
            file_extension = ".sav";
            break;
        }
        case BackupTypes::Vanillaworld_backup:
        {
            source = backups_path / "instances" / instance_id/ "data" / "saves" / fs::path(std::string(data.filename + ".sav"));
            backup_text = tr("IDS_MSG_BACKUP_RESTORE_SAVE_ASK") + std::to_string(fs::file_size(source)) + " bytes";
            backup_directory = "VANILLA";
            file_extension = ".sav";
            break;
        }
    }

    int result = MessageBoxA(NULL, backup_text.c_str(), "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        

        try
        {
            // fs::copy_file(source, fs::path(instances_dir) / "instances" / fs::path(instance_id) / fs::path(backup_directory) / fs::path(world_id + date + file_extension));
            // MessageBoxA(NULL, "Backup created successfully", "Info", MB_ICONINFORMATION | MB_OK);
            // instance_manage(instance_id, ManageCategories::BACKUPS);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, tr("IDS_MSG_BACKUP_RESTORE_FAIL").c_str(), "Info", MB_ICONERROR | MB_OK);
        }
    }
}

/**
 * Initial function
 */
void backupRestoreAsk()
{
    for (const auto& pair : Backups_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (Backups_list[pair.first].getRestoreButtonHitbox().contains(mouse))
        {
            backupRestore(selected_instance, Backups_list[pair.first].getData());
        }
    }
}