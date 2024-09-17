void setDefault_checkboxes()
{
    show_prerelease_version = true;
    Show_older_instances_checkbox.setState(show_prerelease_version);

    save_log_files = true;
    Save_logs_files_checkbox.setState(save_log_files);

    loging_manualy = false;
    login_manualy_checkbox.setState(loging_manualy);

    display_log_colors = true;
    Colored_logs_checkbox.setState(display_log_colors);

    autolaunch_instances = true;
    automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);

    show_warnings = true;
    do_not_show_warnings_checkbox.setState(show_warnings);
    unlock_profile_textboxes();
}