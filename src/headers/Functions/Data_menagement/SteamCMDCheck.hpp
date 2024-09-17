bool SteamCMDCheck()
{
    try
    {
        if (fs::exists(steamcmd_dir + "\\steamcmd.exe"))
        {
            return true;
        }    
    }
    catch (fs::filesystem_error e)
    {
        
    }
    
    return false;
}