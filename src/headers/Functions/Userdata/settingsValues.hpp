void saveConfigWithCurrents()
{
    if (update_config_file() == true)
    {
        MessageBoxA(NULL, tr("IDS_MSG_SAVECONFIG_OK").c_str(), "Info", MB_ICONINFORMATION | MB_OK);
    }
    else
    {
        MessageBoxA(NULL, tr("IDS_SOMETHINGWENTWRONG").c_str(), "Error", MB_ICONERROR | MB_OK);
    }
}

void getSettingsValuesAndSave()
{
    steam_game_dir = SettingsElemets::subcats::general::steam_path_textbox.getText();
    instances_dir = SettingsElemets::subcats::general::instances_path_textbox.getText();
    steamcmd_dir = SettingsElemets::subcats::downloading::steamcmd_path_textbox.getText();

    save_log_files = SettingsElemets::subcats::general::Save_logs_files_checkbox.getState();
    display_log_colors = SettingsElemets::subcats::general::Colored_logs_checkbox.getState();
    autolaunch_instances = SettingsElemets::subcats::downloading::automatically_run_downloaded_instances_checkbox.getState();
    show_warnings = SettingsElemets::subcats::general::do_not_show_warnings_checkbox.getState();
    show_prerelease_version = SettingsElemets::subcats::general::Show_prereleases_checkbox.getState();
    use_secure_ipc = SettingsElemets::subcats::general::use_secure_ipc_checkbox.getState();
    mountOnlyData = SettingsElemets::subcats::general::mount_only_data_checkbox.getState();

    check_updates_when_start = SettingsElemets::subcats::updates::autocheck_for_update_checkbox.getState();

    std::string result = SettingsElemets::subcats::general::theme_list_ddl.getRResult();
    theme_selected = std::stoi(result);

    result = SettingsElemets::subcats::downloading::downloaders_ddl.getRResult();
    downloader_selected = std::stoi(result);

    enableDebugging = SettingsElemets::subcats::debug::debuggingEnabledCheckbox.getState();
    saveDebugLogsToOtherFile = SettingsElemets::subcats::debug::saveDebugLogsToOtherFileCheckbox.getState();
    printDebugLogs = SettingsElemets::subcats::debug::printDebugLogsCheckbox.getState();

    try
    {
        communicationDelay = std::stoi(SettingsElemets::subcats::debug::comunicationDelayTextbox.getText());    
    }
    catch (std::exception e) {}
    try
    {
        comunicationPipeBufferSize = std::stoi(SettingsElemets::subcats::debug::comunicationPipeBufferSizeTextbox.getText());
    }
    catch (std::exception e) {}

    saveConfigWithCurrents();

    srlBackgroundPath = SettingsElemets::subcats::general::SRL_background_img_path_textbox.getText();
}

void getProfileSettingsValuesAndSave()
{
    steam_profile_name = encryptor(SettingsElemets::subcats::steamAccount::profileName_textbox.getText());
    steam_profile_passwd = encryptor(SettingsElemets::subcats::steamAccount::profilePassword_textbox.getText());
    saveConfigWithCurrents();
}