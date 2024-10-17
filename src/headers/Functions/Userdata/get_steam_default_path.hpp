std::string get_steam_default_path()
{
    wchar_t buffer[MAX_PATH];
    DWORD size = GetEnvironmentVariableW(L"ProgramFiles(x86)", buffer, MAX_PATH);
    std::filesystem::path programFilesX86Path(buffer);
    std::filesystem::path steamPath = programFilesX86Path / "Steam" / "steamapps" / "common";
    return steamPath.string();
}

std::string get_steamLocation_default_path()
{
    wchar_t buffer[MAX_PATH];
    DWORD size = GetEnvironmentVariableW(L"ProgramFiles(x86)", buffer, MAX_PATH);
    std::filesystem::path programFilesX86Path(buffer);
    std::filesystem::path steamPath = programFilesX86Path / "Steam";
    return steamPath.string();
}