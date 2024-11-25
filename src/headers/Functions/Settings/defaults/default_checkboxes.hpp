void setDefault_checkboxes()
{
    settings_defaults::show_prerelease_def();
    settings_defaults::save_logs_def();
    settings_defaults::logs_color_def();
    settings_defaults::autolaunch_instances_def();
    settings_defaults::show_warns_def();
    settings_defaults::autocheck_updates_def();
    settings_defaults::use_secure_ipc_def();
    
    unlock_profile_textboxes();

    settings_defaults::theme_def();
    settings_defaults::downloader_def();
}