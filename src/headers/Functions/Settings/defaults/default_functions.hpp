std::string get_steam_default_path();

namespace settings_defaults
{
    void steam_gamedir_def()
    {
        steam_game_dir = get_steam_default_path();
        SettingsElemets::subcats::general::steam_path_textbox.setText(steam_game_dir);
    }
    void instances_dir_def()
    {
        instances_dir = instances_path.string();
        SettingsElemets::subcats::general::instances_path_textbox.setText(instances_dir);
    }
    void steamcmd_dir_def()
    {
        steamcmd_dir = cmd_path.string();
        SettingsElemets::subcats::downloading::steamcmd_path_textbox.setText(steamcmd_dir);
    }
    void show_prerelease_def()
    {
        show_prerelease_version = true;
        SettingsElemets::subcats::general::Show_prereleases_checkbox.setState(show_prerelease_version);
    }
    void save_logs_def()
    {
        save_log_files = true;
        SettingsElemets::subcats::general::Save_logs_files_checkbox.setState(save_log_files);
    }
    void logs_color_def()
    {
        display_log_colors = true;
        SettingsElemets::subcats::general::Colored_logs_checkbox.setState(display_log_colors);
    }
    void autolaunch_instances_def()
    {
        autolaunch_instances = true;
        SettingsElemets::subcats::downloading::automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);
    }
    void show_warns_def()
    {
        show_warnings = true;
        SettingsElemets::subcats::general::do_not_show_warnings_checkbox.setState(show_warnings);
    }
    void autocheck_updates_def()
    {
        check_updates_when_start = true;
        SettingsElemets::subcats::updates::autocheck_for_update_checkbox.setState(check_updates_when_start);
    }

    void use_secure_ipc_def()
    {
        use_secure_ipc = false;
        SettingsElemets::subcats::general::use_secure_ipc_checkbox.setState(use_secure_ipc);
    }

    void mount_only_data_def()
    {
        mountOnlyData = false;
        SettingsElemets::subcats::general::mount_only_data_checkbox.setState(mountOnlyData);
    }

    void theme_def()
    {
        theme_selected = ColorPalete::Bright;
    }

    void downloader_def()
    {
        downloader_selected = depotdownloader;
    }

    void debugging_enable_def()
    {
        enableDebugging = false;
        SettingsElemets::subcats::debug::debuggingEnabledCheckbox.setState(enableDebugging);
    }

    void debug_savelogs_def()
    {
        saveDebugLogsToOtherFile = false;
        SettingsElemets::subcats::debug::saveDebugLogsToOtherFileCheckbox.setState(saveDebugLogsToOtherFile);
    }

    void debug_print_all_def()
    {
        printDebugLogs = true;
        SettingsElemets::subcats::debug::printDebugLogsCheckbox.setState(printDebugLogs);
    }

    void debug_com_delay_def()
    {
        communicationDelay = 10;
        SettingsElemets::subcats::debug::comunicationDelayTextbox.setText(std::to_string(communicationDelay));
    }

    void debug_com_buffersize_def()
    {
        comunicationPipeBufferSize = 1024;
        SettingsElemets::subcats::debug::comunicationPipeBufferSizeTextbox.setText(std::to_string(comunicationPipeBufferSize));
    }

    void debug_acc_info_def()
    {
        acceptInfoLogs = true;
    }

    void debug_acc_warn_def()
    {
        acceptWarningLogs = true;
    }
    
    void debug_acc_err_def()
    {
        acceptErrorLogs = true;
    }

    void debug_acc_excp_def()
    {
        acceptExceptionLogs = true;
    }

    void background_path_def()
    {
        srlBackgroundPath = SRL_BG_DEF_PATH;
        SettingsElemets::subcats::general::SRL_background_img_path_textbox.setText(srlBackgroundPath);
        reloadLauncherBackground();
    }
}