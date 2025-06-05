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

std::string BrowseFile()
{    
    char szFile[MAX_PATH] = { 0 };

    OPENFILENAMEA ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = "All Files\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.lpstrTitle = "Select image";

    if (GetOpenFileNameA(&ofn))
    {
        return std::string(szFile);
    }

    return std::string();
}