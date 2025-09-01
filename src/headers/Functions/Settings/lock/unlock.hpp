void unlock_profile_textboxes()
{
    SteamProfile_name_textbox.setReadOnlyMode(false);
    SteamProfile_password_textbox.setReadOnlyMode(false);

    instances_path_textbox.setReadOnlyMode(false);
    steam_path_textbox.setReadOnlyMode(false);
    steamcmd_path_textbox.setReadOnlyMode(false);
}