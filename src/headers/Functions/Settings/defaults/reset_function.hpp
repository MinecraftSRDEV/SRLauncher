void setSettingsDefault()
{
    int result = MessageBoxA(NULL, tr("IDS_MSG_RESTORE_SETTINGS").c_str(), "Warning", MB_ICONEXCLAMATION | MB_YESNO);
    switch (result)
    {
        case IDYES:
        {
            setAllSettingsAsDefault();
            break;
        }
        case IDNO:
        {
            break;
        }
    }
}