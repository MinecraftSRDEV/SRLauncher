void getWindowsInfo()
{
    windowsInfo = getWindowsVersion();

    GetSystemLanguageA();

    windowsInfo.sysTheme = IsAppLightTheme();

    isWindows10 = isOnWindows10();
}