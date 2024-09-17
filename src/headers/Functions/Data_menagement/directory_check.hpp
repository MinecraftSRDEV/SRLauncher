bool check_file_exists(fs::path path)
{
    if (fs::exists(path))
    {
        return true;
    }
    log_message("File: \"" + path.string() + "\" Not exists", LOG_TYPES::LOG_WARN);
    return false;
}

bool check_directory_exists(fs::path path)
{
    if (fs::exists(path) && fs::is_directory(path))
    {
        return true;
    }
    log_message("Directory: \"" + path.string() + "\" Not exists", LOG_TYPES::LOG_WARN);
    return false;
}

bool create_dir(fs::path path)
{
    if (fs::create_directory(path))
    {
        log_message("Directory: \"" + path.string() + "\" created successfully", LOG_TYPES::LOG_INFO);
        return true;
    }
    
    log_message("Directory: \"" + path.string() + "\" cannot be created", LOG_TYPES::LOG_ERROR);
    return false;
}

void directory_auto(fs::path path)
{
    if (check_directory_exists(path) == false)
    {
        create_dir(path);
    }
}