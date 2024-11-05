void move_directory(fs::path source, fs::path destination)
{
    try
    {
        if (!fs::exists(source) || !fs::is_directory(source))
        {
            throw std::runtime_error("Source directory does not exist or is not a directory.");
        }

        if (!fs::exists(destination))
        {
            fs::create_directories(destination);
        }

        for (const auto& entry : fs::directory_iterator(source))
        {
            auto source_path = entry.path();
            auto destination_path = destination / source_path.filename();

            if (fs::is_directory(source_path))
            {
                move_directory(source_path, destination_path);
            }
            else
            {
                try
                {
                    std::string sourceHash = calcFileMD(source_path.string());

                    fs::rename(source_path, destination_path);

                    std::string destHash = calcFileMD(destination_path.string());

                    if (fs::exists(destination_path))
                    {
                        if (sourceHash != destHash)
                        {
                            log_message("File " + destination_path.filename().string() + "checksum wrong!", LogTypes::LOG_ERROR);
                            return;
                        }
                    }
                    else
                    {
                        log_message("File " + destination_path.filename().string() + "not exists!", LogTypes::LOG_ERROR);
                        return;
                    }
                }
                catch (fs::filesystem_error e)
                {
                    log_message(std::string(e.what()), LogTypes::LOG_ERROR);
                    return;
                }
                
            }
        }
        fs::remove(source);

    }
    catch (const fs::filesystem_error& e)
    {
        log_message("Filesystem error: " + std::string(e.what()), LogTypes::LOG_ERROR);
        return;
    }
    catch (const std::exception& e)
    {
        log_message(std::string(e.what()), LogTypes::LOG_ERROR);
        return;
    }
}

bool move_file(const fs::path& source, const fs::path& dest)
{
    try
    {
        if (fs::exists(source) == true && fs::is_regular_file(source))
        {
            if (fs::exists(dest) == false)
            {
                std::string sourceHash = calcFileMD(source.string());
                fs::rename(source, dest);
                std::string destHash = calcFileMD(dest.string());

                if (sourceHash == destHash)
                {
                    return true;    
                }
                else
                {
                    log_message("File " + dest.filename().string() + " checksum wrong!", LogTypes::LOG_ERROR);
                    return false;
                }    
            }
            else
            {
                log_message("File " + dest.filename().string() + " not exists!", LogTypes::LOG_ERROR);
                return false;
            }
        }
    }
    catch(fs::filesystem_error e)
    {
        log_message(std::string(e.what()), LogTypes::LOG_ERROR);
        return false;
    }

    return false;
}

void copy_directory(fs::path source, fs::path destination)
{
    try
    {
        if (!fs::exists(source) || !fs::is_directory(source))
        {
            throw std::runtime_error("Source directory does not exist or is not a directory.");
        }

        if (!fs::exists(destination))
        {
            fs::create_directories(destination);
        }

        for (const auto& entry : fs::directory_iterator(source))
        {
            auto source_path = entry.path();
            auto destination_path = destination / source_path.filename();

            if (fs::is_directory(source_path))
            {
                fs::copy(source_path, destination_path);
            }
            else
            {
                fs::copy_file(source_path, destination_path);
            }
        }

    }
    catch (const fs::filesystem_error& e)
    {
        std::string errormsg = e.what();
        log_message("Filesystem error: " + errormsg, LogTypes::LOG_ERROR);
    }
    catch (const std::exception& e)
    {
        std::string errormsg = e.what();
        log_message(errormsg, LogTypes::LOG_ERROR);
    }
}