void remove_instnace_function(std::string instnace_id)
{
    fs::path path;
    if (mounted_instance == instances_list[instnace_id].getID())
    {
        MessageBoxA(NULL, "Unmount this instance first!", "Error", MB_ICONERROR | MB_OK);
    }
    else
    {
        path = (instances_dir + "\\Slime Rancher_" + instances_list[instnace_id].getID());
        int result = MessageBoxA(NULL, "Delete this instance and all files?", "Warning", MB_ICONEXCLAMATION | MB_YESNO);

        switch (result)
        {
            case IDNO:
            {
                break;
            }
            case IDYES:
            {
                if (check_directory_exists(path) == true)
                {
                    try
                    {
                        fs::remove_all(path);
                        log_message("instance deleted", LOG_TYPES::LOG_INFO);
                        refresh_instances_list();
                    }
                    catch (const fs::filesystem_error& e)
                    {
                        std::string errormsg = e.what();
                        log_message("cannot delete instnace: " + errormsg, LOG_TYPES::LOG_ERROR);
                        MessageBoxA(NULL, "Cannot delete instnace!", "Error", MB_ICONERROR | MB_OK);
                    }
                }
                else
                {
                    log_message("Directory \"" + path.string() + "\" not found", LOG_TYPES::LOG_ERROR);
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
}