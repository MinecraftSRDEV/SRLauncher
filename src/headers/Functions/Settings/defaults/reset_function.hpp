void setSettingsDefault()
{
    int result = MessageBoxA(NULL, "Are you sure you want to restore default settings?", "Warning", MB_ICONEXCLAMATION | MB_YESNO);
    switch (result)
    {
        case IDYES:
        {
            setDefault_paths();
            setDefault_checkboxes();
            break;
        }
        case IDNO:
        {
            break;
        }
    }
}