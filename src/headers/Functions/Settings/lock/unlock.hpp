void unlock_profile_textboxes()
{
    SettingsElemets::subcats::steamAccount::profileName_textbox.setReadOnlyMode(false);
    SettingsElemets::subcats::steamAccount::profilePassword_textbox.setReadOnlyMode(false);

    SettingsElemets::subcats::general::instances_path_textbox.setReadOnlyMode(false);
    SettingsElemets::subcats::general::steam_path_textbox.setReadOnlyMode(false);
    SettingsElemets::subcats::downloading::steamcmd_path_textbox.setReadOnlyMode(false);
}