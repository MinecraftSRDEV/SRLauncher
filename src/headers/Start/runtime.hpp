/**
 * This function check if Main Launcher directory exists.
 * 
 * TRUE:
 * - AutoCheck for other Launcher directories.
 * - Load configuration files.
 * - Set UI elements.
 * - Check for orginal game dir.
 * - Load Mounted instance.
 * - Check for SteamCMD installed.
 * 
 * FALSE:
 * - Create default config files.
 * - Set default config.
 * 
 * This is onetime use function 
 */
void runtime_check()
{
    restart_runtime:
    {
        if (check_directory_exists(defaultDir) == true)
        {
            directory_auto(instances_path);
            directory_auto(backups_path);
            directory_auto(autobackup_path);
            directory_auto(configuration_path);
            directory_auto(temp_path);
            directory_auto(cmd_path);
            directory_auto(logs_path);

            log_message("Loading config", LOG_TYPES::LOG_INFO);
            if (load_config_file(configuration_path.string() + "/config.json") == true)
            {
                log_message("Launcher config load OK", LOG_TYPES::LOG_INFO);
            }
            else
            {
                log_message("Launcher config load FAIL", LOG_TYPES::LOG_ERROR);
            }

            SlimeRancher_steam_path_textbox.setText(reduceBackslashes(steam_game_dir));
            SlimeRancher_instances_path_textbox.setText(reduceBackslashes(instances_dir));
            steamcmd_path_textbox.setText(reduceBackslashes(steamcmd_dir));

            SteamProfile_name_textbox.setText(decryptor(steam_profile_name));
            // SteamProfile_password_textbox.setText(decryptor(steam_profile_passwd));

            Save_logs_files_checkbox.setState(save_log_files);
            login_manualy_checkbox.setState(loging_manualy);
            Show_older_instances_checkbox.setState(show_prerelease_version);
            Colored_logs_checkbox.setState(display_log_colors);
            automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);
            do_not_show_warnings_checkbox.setState(show_warnings);
            log_message("Loading versions list", LOG_TYPES::LOG_INFO);
            if (load_versions_list() == true)
            {
                log_message("Versions list load OK", LOG_TYPES::LOG_INFO);
            }
            else
            {
                log_message("Versions list load FAIL", LOG_TYPES::LOG_ERROR);
            }

            if (mounted_instance.empty())
            {
                rename_orginal_dir();
                log_message("No instance mounted", LOG_TYPES::LOG_INFO);
                mounted_instance = "Unmounted";
                Mounted_instance_info_text.setString("No instance mounted");
            }
            else
            {
                if (mounted_instance == "Unmounted")
                {
                    Mounted_instance_info_text.setString("No instance mounted");
                }
                else
                {
                    Mounted_instance_info_text.setString(mounted_instance);
                }
                log_message("Mounted instance: " + mounted_instance, LOG_TYPES::LOG_INFO);
            }

            refresh_instances_list();

            if (SteamCMDCheck() == true)
            {
                log_message("SteamCMD is not installed", LOG_TYPES::LOG_WARN);
            }
        }
        else
        {
            if (create_dir(defaultDir) == true)
            {
                log_message("Launcher directory created in: " + defaultDir.string(), LOG_TYPES::LOG_INFO);
            }
            else
            {
                log_message("Cannot create launcher directory", LOG_TYPES::LOG_ERROR);
                MessageBoxA(NULL, "Cannot create launcher directory", "Error", MB_ICONERROR | MB_OK);
                close_launcher();
            }

            setDefault_paths();
            setDefault_checkboxes();
            mounted_instance = "";

            steam_profile_name = "";
            steam_profile_passwd = "";
            saved_version = launcher_version;
            update_config_file();

            SteamProfile_name_textbox.setText(steam_profile_name);
            // SteamProfile_password_textbox.setText(steam_profile_passwd);

            goto restart_runtime;
        }    
    }
    
}