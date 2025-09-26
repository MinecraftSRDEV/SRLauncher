typedef LONG(WINAPI* RtlGetVersionPtr)(OSVERSIONINFOEXW*);

WindowsInfo windowsInfo;

WindowsInfo getWindowsVersion() {
    WindowsInfo output;

    HMODULE hMod = GetModuleHandleA("ntdll.dll");
    if (!hMod) return output;

    auto func = (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");
    if (func) {
        OSVERSIONINFOEXW osInfo = { 0 };
        osInfo.dwOSVersionInfoSize = sizeof(osInfo);
        if (func(&osInfo) == 0) {
            output.BuildNumber = osInfo.dwBuildNumber;
            output.MajorVersion = osInfo.dwMajorVersion;
            output.MinorVersion = osInfo.dwMinorVersion;
        }
    }
    return output;
}

bool isOnWindows10()
{
    if (windowsInfo.MajorVersion >= 10)
    {
        return true;
    }

    return false;
}