bool SteamCMDCheck()
{
    try
    {
        if (fs::exists(cmd_path.string() + "\\steamcmd.exe"))
        {
            return true;
        }    
    }
    catch (fs::filesystem_error e)
    {
        
    }
    
    return false;
}