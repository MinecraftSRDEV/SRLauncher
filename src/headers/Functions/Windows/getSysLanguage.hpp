void GetSystemLanguageA()
{
    LANGID langId = GetUserDefaultUILanguage();  // np. 0x0415 dla pl-PL
    char localeName[LOCALE_NAME_MAX_LENGTH] = {0};

    // Pobierz kod jak "pl-PL", "en-US"
    if (GetLocaleInfoA(langId, LOCALE_SNAME, localeName, LOCALE_NAME_MAX_LENGTH)) {
        windowsInfo.sysLang = localeName;
    }

    try
    {
        windowsInfo.sysLang = windowsInfo.sysLang.substr(0, 2);
        return;
    }
    catch(const std::exception& e) {}
    

    windowsInfo.sysLang = "Unknown";
    return;
}