std::string get_steam_default_path();

namespace settings_defaults
{
    void steam_gamedir_def()
    {
        steam_game_dir = get_steam_default_path();
        SlimeRancher_steam_path_textbox.setText(steam_game_dir);
    }
    void instances_dir_def()
    {
        instances_dir = instances_path.string();
        SlimeRancher_instances_path_textbox.setText(instances_dir);
    }
    void steamcmd_dir_def()
    {
        steamcmd_dir = cmd_path.string();
        steamcmd_path_textbox.setText(steamcmd_dir);
    }
    void show_prerelease_def()
    {
        show_prerelease_version = true;
        Show_prereleases_checkbox.setState(show_prerelease_version);
    }
    void save_logs_def()
    {
        save_log_files = true;
        Save_logs_files_checkbox.setState(save_log_files);
    }
    void logs_color_def()
    {
        display_log_colors = true;
        Colored_logs_checkbox.setState(display_log_colors);
    }
    void autolaunch_instances_def()
    {
        autolaunch_instances = true;
        automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);
    }
    void show_warns_def()
    {
        show_warnings = true;
        do_not_show_warnings_checkbox.setState(show_warnings);
    }
    void autocheck_updates_def()
    {
        check_updates_when_start = true;
        autocheck_for_update_checkbox.setState(check_updates_when_start);
    }

    void use_secure_ipc_def()
    {
        use_secure_ipc = false;
        use_secure_ipc_checkbox.setState(use_secure_ipc);
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
        debuggingEnabledCheckbox.setState(debugging_enable_def);
    }

    void debug_savelogs_def()
    {
        saveDebugLogsToOtherFile = false;
        saveDebugLogsToOtherFileCheckbox.setState(saveDebugLogsToOtherFile);
    }

    void debug_print_all_def()
    {
        printDebugLogs = true;
        printDebugLogsCheckbox.setState(printDebugLogs);
    }

    void debug_com_delay_def()
    {
        communicationDelay = 10;
        comunicationDelayTextbox.setText(std::to_string(communicationDelay));
    }

    void debug_com_buffersize_def()
    {
        comunicationPipeBufferSize = 1024;
        comunicationPipeBufferSizeTextbox.setText(std::to_string(comunicationPipeBufferSize));
    }
}