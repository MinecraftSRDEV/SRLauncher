void setSettingsDefault()
{
    int result = MessageBoxA(NULL, "Are you sure you want to restore default settings?", "Warning", MB_ICONEXCLAMATION | MB_YESNO);
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