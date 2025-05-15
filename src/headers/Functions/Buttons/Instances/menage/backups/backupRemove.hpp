void backupRemove(const std::string& instance_id, const std::string& backup_id)
{
    int result = MessageBoxA(NULL, "Delete this backup?", "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        try
        {
            fs::path source = backups_path / "instances" / fs::path(instance_id) / "BBW" / fs::path(backup_id + ".world");
            log_message(source.string(), LOG_INFO);
            fs::remove(source);
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
            backupRemove(selected_instance, Backups_list[pair.first].getData().filename);
        }
    }
}

// here must be added backup types
// BBW if betterbuild OLD