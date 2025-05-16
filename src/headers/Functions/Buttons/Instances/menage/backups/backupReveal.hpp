void backupReveal(const std::string& instance_id, int backup_type)
{
    std::string command = "explorer ";

    fs::path source_path;

    switch (backup_type)
    {
        case BackupTypes::BBworld_backup:
        {
            source_path = backups_path / "instances" / fs::path(instance_id) / "BBW";
            break;
        }
        case BackupTypes::BBsave_backup:
        {
            source_path = backups_path / "instances" / fs::path(instance_id) / "BBS";
            break;
        }
        case BackupTypes::Vanillaworld_backup:
        {
            source_path = backups_path / "instances" / fs::path(instance_id) / "VANILLA";
            break;
        }
    }

    if (check_directory_exists(source_path) == true)
    {
        command += source_path.string();
        command = reduceBackslashes(command);
        log_message("Executing command: " + command, LogTypes::LOG_INFO);
        WinExec(command.c_str(), SW_SHOWDEFAULT);
    }
    else
    {
        log_message("Directory \"" + source_path.string() + "\" not found", LogTypes::LOG_ERROR);
    }
}

/**
 * Initial function
 */
void backupRevealAsk()
{
    for (const auto& pair : Backups_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (Backups_list[pair.first].getRevealButtonHitbox().contains(mouse))
        {
            backupReveal(selected_instance, Backups_list[pair.first].getData().type);
        }
    }
}