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
        int alertResult = MessageBoxA(NULL, tr("IDS_MSG_DATAINSAVEDIRWARN").c_str(), "Warning", MB_ICONEXCLAMATION | MB_YESNO);
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