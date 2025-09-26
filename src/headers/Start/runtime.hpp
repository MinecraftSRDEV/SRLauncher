void checkUpdate();

fs::path getRuntimePath()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);

    fs::path exePath = buffer;
    fs::path exeDir = exePath.parent_path();

    return exeDir;
}

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
            directory_auto(edited_path);

            directory_auto(UMFmodsFolder_path);
            directory_auto(SMTFolder_path);
            directory_auto(SMLFolder_path);
            directory_auto(SRMLmodsFolder_path);

            runtime_directory = getRuntimePath();

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

            SettingsElemets::subcats::general::steam_path_textbox.setText(reduceBackslashes(steam_game_dir));
            SettingsElemets::subcats::general::instances_path_textbox.setText(reduceBackslashes(instances_dir));
            SettingsElemets::subcats::downloading::steamcmd_path_textbox.setText(reduceBackslashes(steamcmd_dir));

            SettingsElemets::subcats::steamAccount::profileName_textbox.setText(decryptor(steam_profile_name));
            SettingsElemets::subcats::steamAccount::profilePassword_textbox.setText(decryptor(steam_profile_passwd));

            SettingsElemets::subcats::general::Save_logs_files_checkbox.setState(save_log_files);
            SettingsElemets::subcats::general::Show_prereleases_checkbox.setState(show_prerelease_version);
            SettingsElemets::subcats::general::Colored_logs_checkbox.setState(display_log_colors);
            SettingsElemets::subcats::downloading::automatically_run_downloaded_instances_checkbox.setState(autolaunch_instances);
            SettingsElemets::subcats::general::do_not_show_warnings_checkbox.setState(show_warnings);
            SettingsElemets::subcats::general::use_secure_ipc_checkbox.setState(use_secure_ipc);
            SettingsElemets::subcats::general::mount_only_data_checkbox.setState(mountOnlyData);

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
                displayNonEmptyDataAlert();
                rename_orginal_dir();
                log_message("No instance mounted", LogTypes::LOG_INFO);
                mounted_instance = UNMOUNTED_INSTANCE;
                MainpageElements::playbar::infoText.setString(tr("IDS_NO_INSTANCE_MOUNTED"));
                MainpageElements::playbar::versionText.setString("");
            }
            else
            {
                if (mounted_instance == UNMOUNTED_INSTANCE)
                {
                    displayNonEmptyDataAlert();
                    MainpageElements::playbar::infoText.setString(tr("IDS_NO_INSTANCE_MOUNTED"));
                    MainpageElements::playbar::versionText.setString("");
                }
                else
                {
                    MainpageElements::playbar::infoText.setString(mounted_instance);
                }
                log_message("Mounted instance: " + mounted_instance, LogTypes::LOG_INFO);
            }


            if (downloader_selected == steamcmd)
            {
                SettingsElemets::subcats::downloading::steamcmd_path_textbox.setLabelText(settmaindi::CMDPATH_TEXT);
                if (SteamCMDCheck() == true)
                {
                    log_message("SteamCMD is not installed", LogTypes::LOG_WARN);
                } 
            }
            else
            {
                SettingsElemets::subcats::downloading::steamcmd_path_textbox.setLabelText(settmaindi::CMDPATH_DISABLED);
            }

            createLanguageDdl();

            SettingsElemets::subcats::general::theme_list_ddl.setFromResult(std::to_string(theme_selected));
            SettingsElemets::subcats::downloading::downloaders_ddl.setFromResult(std::to_string(downloader_selected));
            SettingsElemets::subcats::general::languages_list_ddl.setFromResult(launcher_language);

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

            SettingsElemets::subcats::steamAccount::profileName_textbox.setText(steam_profile_name);
            SettingsElemets::subcats::steamAccount::profilePassword_textbox.setText(steam_profile_passwd);

            goto restart_runtime;
        }    
    }
    
}