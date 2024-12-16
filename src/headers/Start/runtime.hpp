void checkUpdate();

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
            directory_auto(components_path);
            directory_auto(downloader_path);
            directory_auto(cmd_path);
            directory_auto(logs_path);
            directory_auto(mods_path);

            directory_auto(UMFmodsFolder_path);
            directory_auto(SMTFolder_path);
            directory_auto(SMLFolder_path);
            directory_auto(SRMLmodsFolder_path);

            if (fs::is_empty(downloader_path))
            {
                copy_directory(fs::path("./assets/components/downloader"), downloader_path);
                log_message("Installed DepotDownloader", LogTypes::LOG_INFO);
            }
            else
            {
                try
                {
                    MD5 calculateMd5;

                    std::string installedMD5 = calculateMd5.calculateFromFile(downloader_path.string() + "/DepotDownloader.exe");
                    std::string includedMD5 = calculateMd5.calculateFromFile("./assets/components/downloader/DepotDownloader.exe");

                    if (installedMD5 != includedMD5)
                    {
                        fs::remove_all(downloader_path);
                        copy_directory(fs::path("./assets/components/downloader"), downloader_path);
                        log_message("Included downloader MD5 wrong", LogTypes::LOG_WARN);
                    }    
                }
                catch (fs::filesystem_error e)
                {
                    
                }
                catch (std::runtime_error e)
                {

                }
            }

            log_message("Loading config", LogTypes::LOG_INFO);
            if (load_config_file(configuration_path.string() + "/config.json") == true)
            {
                log_message("Launcher config load OK", LogTypes::LOG_INFO);
            }
            else
            {
                log_message("Launcher config load FAIL", LogTypes::LOG_ERROR);
            }
            
            if (check_updates_when_start == true)
            {
                checkUpdate();
            }

            SlimeRancher_steam_path_textbox.setText(reduceBackslashes(steam_game_dir));
            SlimeRancher_instances_path_textbox.setText(reduceBackslashes(instances_dir));
            steamcmd_path_textbox.setText(reduceBackslashes(steamcmd_dir));

            SteamProfile_name_textbox.setText(decryptor(steam_profile_name));
            SteamProfile_password_textbox.setText(decryptor(steam_profile_passwd));

            Save_logs_files_checkbox.setState(save_log_files);
            Show_prereleases_checkbox.setState(show_prerelease_version);
            Colored_logs_checkbox.setState(display_log_colors);
            automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);
            do_not_show_warnings_checkbox.setState(show_warnings);
            use_secure_ipc_checkbox.setState(use_secure_ipc);

            log_message("Loading versions list", LogTypes::LOG_INFO);
            if (load_versions_list() == true)
            {
                log_message("Versions list load OK", LogTypes::LOG_INFO);
            }
            else
            {
                log_message("Versions list load FAIL", LogTypes::LOG_ERROR);
            }

            if (mounted_instance.empty())
            {
                rename_orginal_dir();
                log_message("No instance mounted", LogTypes::LOG_INFO);
                mounted_instance = UNMOUNTED_INSTANCE;
                Mounted_instance_info_text.setString("No instance mounted");
                mounted_instance_version.setString("");
            }
            else
            {
                if (mounted_instance == UNMOUNTED_INSTANCE)
                {
                    Mounted_instance_info_text.setString("No instance mounted");
                    mounted_instance_version.setString("");
                }
                else
                {
                    Mounted_instance_info_text.setString(mounted_instance);
                }
                log_message("Mounted instance: " + mounted_instance, LogTypes::LOG_INFO);
            }


            if (downloader_selected == steamcmd)
            {
                steamcmd_path_textbox.setLabelText(settmaindi::CMDPATH_TEXT);
                if (SteamCMDCheck() == true)
                {
                    log_message("SteamCMD is not installed", LogTypes::LOG_WARN);
                } 
            }
            else
            {
                steamcmd_path_textbox.setLabelText(settmaindi::CMDPATH_DISABLED);
            }

            theme_list_ddl.setFromResult(std::to_string(theme_selected));
            downloaders_ddl.setFromResult(std::to_string(downloader_selected));

            loadLicences();

            checkSession();
        }
        else
        {
            if (create_dir(defaultDir) == true)
            {
                log_message("Launcher directory created in: " + defaultDir.string(), LogTypes::LOG_INFO);
            }
            else
            {
                log_message("Cannot create launcher directory", LogTypes::LOG_ERROR);
                MessageBoxA(NULL, "Cannot create launcher directory", "Error", MB_ICONERROR | MB_OK);
                close_launcher();
            }

            setAllSettingsAsDefault();
            mounted_instance = "";

            steam_profile_name = "";
            steam_profile_passwd = "";
            saved_version = launcher_version;
            update_config_file();

            SteamProfile_name_textbox.setText(steam_profile_name);
            SteamProfile_password_textbox.setText(steam_profile_passwd);

            goto restart_runtime;
        }    
    }
    
}