void getfolder_steamdir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        steam_game_dir = input_path;
        SlimeRancher_steam_path_textbox.setText(steam_game_dir);
    }
}

void getfolder_instancesdir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        instances_dir = input_path;
        SlimeRancher_instances_path_textbox.setText(instances_dir);    
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