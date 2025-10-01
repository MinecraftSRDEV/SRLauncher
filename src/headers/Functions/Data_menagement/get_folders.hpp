void getfolder_steamdir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        steam_game_dir = input_path;
        SettingsElemets::subcats::general::steam_path_textbox.setText(steam_game_dir);
    }
}

void getfolder_instancesdir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        instances_dir = input_path;
        SettingsElemets::subcats::general::instances_path_textbox.setText(instances_dir);    
    }
}

void getfolder_steamcmddir()
{
    std::string input_path = BrowseFolder();
    if (!input_path.empty())
    {
        steamcmd_dir = input_path;
        SettingsElemets::subcats::downloading::steamcmd_path_textbox.setText(steamcmd_dir);
    }
}

void getfolder_background_path()
{
    std::string input_path = BrowseFile();
    if (!input_path.empty())
    {
        srlBackgroundPath = input_path;
        SettingsElemets::subcats::general::SRL_background_img_path_textbox.setText(srlBackgroundPath);
        reloadLauncherBackground();
    }
}