void scanBbwBackups(const fs::path& dirEntry, int& itr, int& lasty)
{
    Backups_list.clear();

    BackupData data;

    data.type = betterbuild_save_backup;

    for (const auto& entry : fs::directory_iterator(dirEntry / "BBW"))
    {
        std::string filename = entry.path().filename().replace_extension().string();

        data.source = dirEntry.filename().string();
        data.type = BackupTypes::BBworld_backup;

        size_t datePositionBegin = filename.find("(");
        size_t datePositionEnd = filename.find(")");
        if (datePositionBegin != std::string::npos && datePositionEnd != std::string::npos)
        {
            try
            {
                data.name = filename.substr(0, datePositionBegin);
                data.date = filename.substr(datePositionBegin + 1);
                data.date = convertTmToString(convertStringToDate(data.date));
                data.filename = filename;
            }
            catch (std::out_of_range e)
            {
                data.name = filename;
                data.filename = filename;
                data.date = UNKNOWN;
            }
        }

        Backups_list[itr].create(130, lasty, data, font);
        Backups_list[itr].transportFunction(backupRemoveAsk, Backups_list[itr].REMOVE);
        // Backups_list[itr].transportFunction(noFunction, Backups_list[itr].RESTORE);
        // Backups_list[itr].transportFunction(noFunction, Backups_list[itr].REVEAL);
        lasty += 120;
        itr++;
    }
}

void scanBackups(const std::string& instance_id)
{
    int iteration = 0;
    int posY = 10;

    fs::path directory = backups_path / "instances";

    try
    {
        // for (const auto& entry : fs::directory_iterator(directory))
        // {
            // scanBbwBackups(entry.path(), iteration, posY);
        // }
        scanBbwBackups(directory / fs::path(instance_id), iteration, posY);
    }
    catch (fs::filesystem_error e)
    {
        log_message("Backups loading error: " + std::string(e.what()), LogTypes::LOG_ERROR);
    }
}