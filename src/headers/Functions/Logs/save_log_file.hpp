void save_log_file()
{
    if (save_log_files == true)
    {
        std::string file_name = "log_" + std::to_string(run_YEAR) + "_" + std::to_string(run_DAY) + "_" + std::to_string(run_MONTH) + "_" + std::to_string(run_H) + "_" + std::to_string(run_M) + "_" + std::to_string(run_S) + ".txt";

        std::ofstream log_file;
        log_file.open(logs_path.string() + "/" + file_name);

        for (const auto& pair : logs)
        {
            log_file << pair.second << std::endl;
        }
        log_file.close();    
    }   
}