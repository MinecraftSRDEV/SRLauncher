void remove_instnace_function(std::string instnace_id)
{
    fs::path path;
    if (mounted_instance == instances_list[instnace_id].getID())
    {
        MessageBoxA(NULL, tr("IDS_DICT_INST_UNMOUNT_MSG").c_str(), "Error", MB_ICONERROR | MB_OK);
    }
    else
    {
        path = (instances_dir + "\\Slime Rancher_" + instances_list[instnace_id].getID());
        int result = MessageBoxA(NULL, tr("IDS_MSG_INSTANCE_REMOVE_ASK").c_str(), "Warning", MB_ICONEXCLAMATION | MB_YESNO);

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
                        log_message(tr("IDS_MSG_INSTANCE_REMOVE_OK").c_str(), LogTypes::LOG_INFO);
                        refresh_instances_list();
                    }
                    catch (const fs::filesystem_error& e)
                    {
                        std::string errormsg = e.what();
                        log_message("cannot delete instnace: " + errormsg, LogTypes::LOG_ERROR);
                        MessageBoxA(NULL, tr("IDS_MSG_INSTANCE_REMOVE_FAIL").c_str(), "Error", MB_ICONERROR | MB_OK);
                    }
                }
                else
                {
                    log_message("Directory \"" + path.string() + "\" not found", LogTypes::LOG_ERROR);
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