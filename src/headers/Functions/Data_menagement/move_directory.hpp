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
                fs::rename(source_path, destination_path);
            }
        }
        fs::remove(source);

    }
    catch (const fs::filesystem_error& e)
    {
        std::string errormsg = e.what();
        log_message("Filesystem error: " + errormsg, LOG_TYPES::LOG_ERROR);
    }
    catch (const std::exception& e)
    {
        std::string errormsg = e.what();
        log_message(errormsg, LOG_TYPES::LOG_ERROR);
    }
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
        log_message("Filesystem error: " + errormsg, LOG_TYPES::LOG_ERROR);
    }
    catch (const std::exception& e)
    {
        std::string errormsg = e.what();
        log_message(errormsg, LOG_TYPES::LOG_ERROR);
    }
}