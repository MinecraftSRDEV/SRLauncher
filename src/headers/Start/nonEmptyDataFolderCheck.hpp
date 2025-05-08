bool checkDataFolderIsEmpty()
{
    try
    {
        return fs::is_empty(local_save_path);
    }
    catch(std::exception e)
    {
    }
    return true;
}

void displayNonEmptyDataAlert()
{
    if (checkDataFolderIsEmpty() == false)
    {
        int alertResult = MessageBoxA(NULL, "You have some data in your local saves directory.\n\n If you played Slime Rancher beforehand using different launcher or Steam its recommended to empty this directory first. Running the launcher without it can mess with the files, and in the ekect it can break the saved data, instances or make it impossible to mount or unmount!\n\nDo you want to continue?", "Warning", MB_ICONEXCLAMATION | MB_YESNO);
        switch(alertResult)
        {
            case IDYES:
            {
                break;
            }
            case IDNO:
            {
                exit(0);
                break;
            }
        }
    }
}