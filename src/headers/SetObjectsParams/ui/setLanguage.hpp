void changeLanguage()
{
    MessageBoxA(NULL, tr("IDS_MSG_SETTINGS_LANGCHANGEINFO").c_str(), "Info", MB_ICONINFORMATION | MB_OK);
    launcher_language = SettingsElemets::subcats::general::languages_list_ddl.getRResult();
    UIElements.setElementsLanguage();
}