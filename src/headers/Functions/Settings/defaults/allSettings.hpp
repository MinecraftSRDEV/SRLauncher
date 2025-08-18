void setAllSettingsAsDefault()
{
    settings_defaults::show_prerelease_def();
    settings_defaults::save_logs_def();
    settings_defaults::logs_color_def();
    settings_defaults::autolaunch_instances_def();
    settings_defaults::show_warns_def();
    settings_defaults::autocheck_updates_def();
    settings_defaults::use_secure_ipc_def();
    settings_defaults::mount_only_data_def();
    
    unlock_profile_textboxes();

    settings_defaults::theme_def();
    settings_defaults::downloader_def();

    settings_defaults::debug_com_buffersize_def();
    settings_defaults::debug_com_delay_def();
    settings_defaults::debug_print_all_def();
    settings_defaults::debug_savelogs_def();
    settings_defaults::debugging_enable_def();

    settings_defaults::debug_acc_info_def();
    settings_defaults::debug_acc_warn_def();
    settings_defaults::debug_acc_err_def();
    settings_defaults::debug_acc_excp_def();

    settings_defaults::steam_gamedir_def();
    settings_defaults::instances_dir_def();
    settings_defaults::steamcmd_dir_def();
    settings_defaults::background_path_def();
}