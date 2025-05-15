void instance_manage(std::string instance_id);

std::string formatDate(int value, int max)
{
    if (value < max)
    {
        return "0" + std::to_string(value);
    }
    return std::to_string(value);
}

void backupWorld(const std::string& instance_id, const std::string& world_id)
{
    fs::path source = instances_dir / fs::path("Slime Rancher_" + instance_id) / "mods" / "BetterBuild" / fs::path(std::string(world_id + ".world"));
    std::string backup_text = "Backup this world?\nfile size: " + std::to_string(fs::file_size(source)) + " bytes";

    int result = MessageBoxA(NULL, backup_text.c_str(), "Info", MB_ICONQUESTION | MB_YESNO);

    if (result == IDYES)
    {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        
        std::string date = "(" + std::to_string(now->tm_year + 1900) + formatDate(now->tm_mon + 1, 10) + formatDate(now->tm_mday, 10) + formatDate(now->tm_hour, 10) + formatDate(now->tm_min, 10) + formatDate(now->tm_sec, 10) + ")";

        directory_auto(backups_path / "instances");
        directory_auto(backups_path / "instances" / fs::path(instance_id));
        directory_auto(backups_path / "instances" / fs::path(instance_id) / "BBW");
        try
        {
            fs::copy_file(source, backups_path / "instances" / fs::path(instance_id) / "BBW" / fs::path(world_id + date + ".world"));
            MessageBoxA(NULL, "Backup created successfully", "Info", MB_ICONINFORMATION | MB_OK);
            instance_manage(instance_id);
        }
        catch (fs::filesystem_error e)
        {
            MessageBoxA(NULL, "Backup create FAIL", "Info", MB_ICONERROR | MB_OK);
        }
    }
}

/**
 * Initial function
 */
void backupWorldAsk()
{
    for (const auto& pair : betterbuildworlds_list)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (betterbuildworlds_list[pair.first].getBackupButtonHitbox().contains(mouse))
        {
            backupWorld(selected_instance, betterbuildworlds_list[pair.first].getData().levelname);
        }
    }
}