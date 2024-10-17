void checkUpdate()
{
    std::string HTMLbuffer = fetchHTML("https://raw.githubusercontent.com/MinecraftSRDEV/SRLauncher/refs/heads/main/src/headers/Declarations/varriables.hpp");

    std::string target = "std::string launcher_version =";
    size_t found = HTMLbuffer.find(target);

    if (found != std::string::npos)
    {
        try
        {
            size_t start = HTMLbuffer.find('"', found);
            if (start != std::string::npos)
            {
                start++;
                size_t end = HTMLbuffer.find('"', start);
                if (end != std::string::npos)
                {
                    std::string launcherVersion = HTMLbuffer.substr(start, end - start);
                    if (launcher_version != launcherVersion)
                    {
                        std::string text = "New Launcher version is available: " + launcherVersion + "\n\nYou have: " + launcher_version;
                        update_status_text.setString(text);
                        MessageBoxA(NULL, text.c_str(), "Update Available", MB_ICONINFORMATION | MB_OK);
                    }
                    else
                    {
                        update_status_text.setString("You have latest version");
                    }
                }
            }
        }
        catch (std::out_of_range e)
        {
            std::string err = e.what();
            update_status_text.setString("Cannot check for updates: \n" + err);
        }
    }
    else
    {
        update_status_text.setString("Cannot check for updates");
    }    
}