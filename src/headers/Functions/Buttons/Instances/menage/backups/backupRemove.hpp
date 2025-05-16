void backupRemove(const std::string& instance_id, const std::string& backup_id, int backup_type)
{
    int result = MessageBoxA(NULL, "Delete this backup?", "Info", MB_ICONQUESTION | MB_YESNO);

    fs::path source_path;
    if (result == IDYES)
    {
        switch (backup_type)
        {
            case BackupTypes::BBworld_backup:
            {
                source_path = backups_path / "instances" / fs::path(instance_id) / "BBW" / fs::path(backup_id + ".world");
                break;
            }
            case BackupTypes::BBsave_backup:
            {
                source_path = backups_path / "instances" / fs::path(instance_id) / "BBS" / fs::path(backup_id + ".sav");
                break;
            }
            case BackupTypes::Vanillaworld_backup:
            {
                source_path = backups_path / "instances" / fs::path(instance_id) / "VANILLA" / fs::path(backup_id + ".sav");
                break;
            }
        }

        try
        {
            log_message(source_path.string(), LOG_INFO);
            fs::remove(source_path);
            MessageBoxA(NULL, "Backup successfully removed", "Info", MB_ICONINFORMATION | MB_OK);
            instance_manage(instance_id);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, "Backup remove FAIL", "Info", MB_ICONERROR | MB_OK);
        }
    }
}

/**
 * Initial function
 */
void backupRemoveAsk()
{
    for (const auto& pair : Backups_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (Backups_list[pair.first].getRemoveButtonHitbox().contains(mouse))
        {
            backupRemove(selected_instance, Backups_list[pair.first].getData().filename, Backups_list[pair.first].getData().type);
        }
    }
}