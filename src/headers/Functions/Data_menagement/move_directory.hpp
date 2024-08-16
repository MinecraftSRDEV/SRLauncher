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
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
}