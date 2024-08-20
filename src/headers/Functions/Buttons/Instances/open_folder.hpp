void instance_open_game_folder(std::string instnace_id)
{
    std::string command = "explorer ";
    fs::path path;
    if (mounted_instance != "Unmounted")
    {
        if (mounted_instance == instances_list[instnace_id].getID())
        {
            path = steam_game_dir + "\\Slime Rancher";
        }
        else
        {
            path = (instances_dir + "\\Slime Rancher_" + instances_list[instnace_id].getID());
        }
    }
    else
    {
        path = (instances_dir + "\\Slime Rancher_" + instances_list[instnace_id].getID());
    }

    if (check_directory_exists(path) == true)
    {
        command += path.string();
        command = reduceBackslashes(command);
        log_message("Executing command: " + command, LOG_TYPES::LOG_INFO);
        WinExec(command.c_str(), SW_SHOWDEFAULT);
    }
    else
    {
        log_message("Directory \"" + path.string() + "\" not found", LOG_TYPES::LOG_ERROR);
    }
}

void instnace_open_saves_folder(std::string instnace_id)
{
    std::string command = "explorer ";
    fs::path path;
    if (mounted_instance != "Unmounted")
    {
        if (mounted_instance == instances_list[instnace_id].getID())
        {
            path = local_save_path;
        }
        else
        {
            path = (instances_dir + "\\Slime Rancher_" + instances_list[instnace_id].getID() + "\\data\\saves");
        }
    }
    else
    {
        path = (instances_dir + "\\Slime Rancher_" + instances_list[instnace_id].getID() + "\\data\\saves");
    }

    if (check_directory_exists(path) == true)
    {
        command += path.string();
        command = reduceBackslashes(command);
        log_message("Executing command: " + command, LOG_TYPES::LOG_INFO);
        WinExec(command.c_str(), SW_SHOWDEFAULT);
    }
    else
    {
        log_message("Directory \"" + path.string() + "\" not found", LOG_TYPES::LOG_ERROR);
    }
}