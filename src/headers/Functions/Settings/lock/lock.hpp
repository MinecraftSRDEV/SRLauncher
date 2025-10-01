void lock_profile_textboxes()
{
    SettingsElemets::subcats::steamAccount::profileName_textbox.setReadOnlyMode(true);
    SettingsElemets::subcats::steamAccount::profilePassword_textbox.setReadOnlyMode(true);

    SettingsElemets::subcats::general::instances_path_textbox.setReadOnlyMode(true);
    SettingsElemets::subcats::general::steam_path_textbox.setReadOnlyMode(true);
    SettingsElemets::subcats::downloading::steamcmd_path_textbox.setReadOnlyMode(true);
}