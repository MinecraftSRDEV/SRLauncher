void scanBackupsIn(const fs::path& dirEntry, int& itr, int& lasty, int datatype)
{
    BackupData data;

    fs::path filesAt;

    switch (datatype)
    {
        case BackupTypes::BBworld_backup:
        {
            filesAt = dirEntry / "BBW";
            break;
        }
        case BackupTypes::BBsave_backup:
        {
            filesAt = dirEntry / "BBS";
            break;
        }
        case BackupTypes::Vanillaworld_backup:
        {
            filesAt = dirEntry / "VANILLA";
            break;
        }
    }

    for (const auto& entry : fs::directory_iterator(filesAt))
    {
        std::string filename = entry.path().filename().replace_extension().string();

        data.source = dirEntry.filename().string();
        data.type = datatype;

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
        Backups_list[itr].transportFunction(backupRestoreAsk, Backups_list[itr].RESTORE);
        Backups_list[itr].transportFunction(backupRevealAsk, Backups_list[itr].REVEAL);
        lasty += 120;
        itr++;
    }
}

void scanBackups(const std::string& instance_id)
{
    int iteration = 0;
    int posY = 10;

    fs::path directory = backups_path / "instances";

    Backups_list.clear();
    try {scanBackupsIn(directory / fs::path(instance_id), iteration, posY, BackupTypes::BBworld_backup);}
    catch (fs::filesystem_error e) {log_message("Backups BBW loading error: " + std::string(e.what()), LogTypes::LOG_ERROR);}
    try {scanBackupsIn(directory / fs::path(instance_id), iteration, posY, BackupTypes::BBsave_backup);}
    catch (fs::filesystem_error e) {log_message("Backups BBS loading error: " + std::string(e.what()), LogTypes::LOG_ERROR);}
    try {scanBackupsIn(directory / fs::path(instance_id), iteration, posY, BackupTypes::Vanillaworld_backup);}
    catch (fs::filesystem_error e) {log_message("Backups VANILLA loading error: " + std::string(e.what()), LogTypes::LOG_ERROR);}
}