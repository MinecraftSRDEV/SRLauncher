void instance_manage(std::string instance_id, int scene);

std::string formatDate(int value, int max)
{
    if (value < max)
    {
        return "0" + std::to_string(value);
    }
    return std::to_string(value);
}

void backupWorld(const std::string& instance_id, const std::string& world_id, int backup_type)
{
    fs::path source;
    std::string backup_text;
    std::string backup_directory;
    std::string file_extension;

    switch (backup_type)
    {
        case BackupTypes::BBworld_backup:
        {
            source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "mods" / "BetterBuild" / fs::path(std::string(world_id + ".world"));
            backup_text = tr("IDS_MSG_BACKUP_MAKE_WORLD_ASK") + std::to_string(fs::file_size(source)) + " bytes";
            backup_directory = "BBW";
            file_extension = ".world";
            break;
        }
        case BackupTypes::BBsave_backup:
        {
            source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "mods" / "BetterBuild" / fs::path(std::string(world_id + ".sav"));
            backup_text = tr("IDS_MSG_BACKUP_MAKE_SAVE_ASK") + std::to_string(fs::file_size(source)) + " bytes";
            backup_directory = "BBS";
            file_extension = ".sav";
            break;
        }
        case BackupTypes::Vanillaworld_backup:
        {
            source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "data" / "saves" / fs::path(std::string(world_id + ".sav"));
            backup_text = tr("IDS_MSG_BACKUP_MAKE_SAVE_ASK") + std::to_string(fs::file_size(source)) + " bytes";
            backup_directory = "VANILLA";
            file_extension = ".sav";
            break;
        }
    }

    int result = MessageBoxA(NULL, backup_text.c_str(), "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        
        std::string date = "(" + std::to_string(now->tm_year + 1900) + formatDate(now->tm_mon + 1, 10) + formatDate(now->tm_mday, 10) + formatDate(now->tm_hour, 10) + formatDate(now->tm_min, 10) + formatDate(now->tm_sec, 10) + ")";

        directory_auto(backups_path / "instances");
        directory_auto(backups_path / "instances" / fs::path(instance_id));
        directory_auto(backups_path / "instances" / fs::path(instance_id) / fs::path(backup_directory));
        try
        {
            fs::copy_file(source, backups_path / "instances" / fs::path(instance_id) / fs::path(backup_directory) / fs::path(world_id + date + file_extension));
            MessageBoxA(NULL, tr("IDS_MSG_BACKUP_MAKE_OK").c_str(), "Info", MB_ICONINFORMATION | MB_OK);
            instance_manage(instance_id, ManageCategories::BACKUPS);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, tr("IDS_MSG_BACKUP_MAKE_FAIL").c_str(), "Info", MB_ICONERROR | MB_OK);
        }
    }
}

/**
 * Initial functions
 */


void backupBBWorldAsk()
{
    for (const auto& pair : betterbuildworlds_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (betterbuildworlds_list[pair.first].getBackupButtonHitbox().contains(mouse))
        {
            backupWorld(selected_instance, betterbuildworlds_list[pair.first].getData().levelname, BackupTypes::BBworld_backup);
        }
    }
}

void backupBBSaveAsk()
{
    for (const auto& pair : betterbuildsaves_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (betterbuildsaves_list[pair.first].getMakeBackupButtonHitbox().contains(mouse))
        {
            backupWorld(selected_instance, betterbuildsaves_list[pair.first].getData().name, BackupTypes::BBsave_backup);
        }
    }
}

void backupVSaveAsk()
{
    for (const auto& pair : vanillasaves_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (vanillasaves_list[pair.first].getMakeBackupButtonHitbox().contains(mouse))
        {
            backupWorld(selected_instance, vanillasaves_list[pair.first].getData().name, BackupTypes::Vanillaworld_backup);
        }
    }
}