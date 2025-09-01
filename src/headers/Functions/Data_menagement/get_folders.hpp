void getfolder_steamdir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        steam_game_dir = input_path;
        steam_path_textbox.setText(steam_game_dir);
    }
}

void getfolder_instancesdir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        instances_dir = input_path;
        instances_path_textbox.setText(instances_dir);    
    }
}

void getfolder_steamcmddir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        steamcmd_dir = input_path;
        steamcmd_path_textbox.setText(steamcmd_dir);
    }
}

void getfolder_background_path()
{
    std::string input_path = BrowseFile();
    if (!input_path.empty())
    {
        srlBackgroundPath = input_path;
        SRL_background_img_path_textbox.setText(srlBackgroundPath);
        reloadLauncherBackground();
    }
}