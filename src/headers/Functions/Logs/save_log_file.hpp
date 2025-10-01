void save_log_file()
{
    if (save_log_files == true)
    {
        std::string file_name = "log_" + dateFormat::getStringfiedDateString() + ".txt";

        std::ofstream log_file;
        log_file.open(logs_path.string() + "/" + file_name);

        for (const auto& pair : logs)
        {
            log_file << pair.second << std::endl;
        }
        log_file.close();    
    }   
}