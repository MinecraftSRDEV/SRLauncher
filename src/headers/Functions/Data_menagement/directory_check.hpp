bool check_file_exists(fs::path path, bool log = true)
{
    if (fs::exists(path))
    {
        return true;
    }

    if (log == true)
    {
        log_message("File: \"" + path.string() + "\" Not exists", LogTypes::LOG_WARN);
    }
    return false;
}

bool check_directory_exists(fs::path path, bool log = true)
{
    if (fs::exists(path) && fs::is_directory(path))
    {
        return true;
    }

    if (log == true)
    {
        log_message("Directory: \"" + path.string() + "\" Not exists", LogTypes::LOG_WARN);    
    }
    return false;
}

bool create_dir(fs::path path, bool log = true)
{
    if (fs::create_directory(path))
    {
        if (log == true)
        {
            log_message("Directory: \"" + path.string() + "\" created successfully", LogTypes::LOG_INFO);    
        }
        return true;
    }
    
    if (log == true)
    {
        log_message("Directory: \"" + path.string() + "\" cannot be created", LogTypes::LOG_ERROR);    
    }
    return false;
}

void directory_auto(fs::path path, bool log = true)
{
    if (check_directory_exists(path) == false)
    {
        create_dir(path, log);
    }
}