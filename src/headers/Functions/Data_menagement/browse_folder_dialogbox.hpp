std::string BrowseFolder()
{
    char szFolderPath[MAX_PATH] = { 0 };
    
    BROWSEINFOA bi = { 0 };
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);

    if (pidl != NULL)
    {
        if (SHGetPathFromIDListA(pidl, szFolderPath))
        {
            CoTaskMemFree(pidl);
            return std::string(szFolderPath);
        }
        CoTaskMemFree(pidl);
    }

    return std::string();
}