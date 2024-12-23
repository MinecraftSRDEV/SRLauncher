void renderCategories()
{
    categories_bg.render(window);
    MainCategory_button.render(window);
    InstancesCategory_button.render(window);
    SettingsCategory_button.render(window);
    VersionsCategory_button.render(window);
}

void renderIconBar()
{
    window.draw(InstanceIconBar::selectedBG);
    InstanceIconBar::next_button.render(window);
    InstanceIconBar::prev_button.render(window);
    window.draw(InstanceIconBar::icon_bar_text);
    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        InstanceIconBar::IconBarMap[pair.first].render(window);
    }
}

void window_draw()
{
    window.draw(background);
    
    if (UI_current == UiPages::MainMenu)
    {
        renderCategories();

        console.render(window);
        console_clear_button.render(window);

        main_page_playbar_bg.render(window);
        if (mounted_instance != UNMOUNTED_INSTANCE)
        {
            launch_game_button.render(window);    
        }

        if (game_downloading == true)
        {
            if (downloadInitializing == true)
            {
                window.draw(progress_bg);
                window.draw(progress_moveing);    
            }
            else
            {
                downloadingProgress.render(window);
            }
        }

        window.draw(Mounted_instance_info_text);
        window.draw(Launcher_version_text);
        if (mounted_instance_version.getString() != "")
        {
            window.draw(mounted_instance_version);
        }

        if (display_download_progress == true)
        {
            window.draw(downloading_progress_text);
        }

        if (display_guard_window == true)
        {
            GuardBox.render(window);
        }

        if (game_running == true)
        {
            if (DebugSettingsUI::debuggingEnabledCheckbox.getState() == true)
            {
                window.draw(debugWorking);
                window.draw(debugIpcElapsedText);
            }
        }
    }

    if (UI_current == UiPages::InstancesMenu)
    {
        renderCategories();

        instances_bg.render(window);
        
        if (instancesListLoading == false)
        {
            new_instance_button.render(window);
            import_instnace_button.render(window);  

            if (instances_list.size() > 0)
            {
                for (const auto& pair : instances_list)
                {
                    instances_list[pair.first].render(window);
                }     
            }  
            else
            {
                window.draw(no_instances_text);
                window.draw(instances_vanish_tooltip_text);
            }
        }
        else
        {
            window.draw(dataLoading_text);
        }
    }

    if (UI_current == UiPages::NewInstanceMenu)
    {
        instance_creation_bg.render(window);
        instance_creation_info1_bg.render(window);
        instance_creation_info2_bg.render(window);

        new_instance_name_textbox.render(window);

        if (versions_list_ddl.getState() == false)
        {
            create_button.render(window); 
            instance_creation_cancel.render(window);
            window.draw(CreateInstanceUI::isntance_will_be_created_in_text);

            window.draw(CreateInstanceUI::instance_file_separation_text);

            if (graphics_preset_ddl.getState() == false)
            {
                renderIconBar();
            }
        }

        CreateInstanceUI::automount_checkbox.render(window);
        CreateInstanceUI::create_with_graphics_preset_checkbox.render(window);
        window.draw(CreateInstanceUI::instance_ver_info_text);

        CreateInstanceUI::graphics_preset_ddl.render(window);

        versions_list_ddl.render(window); 
    }

    if (UI_current == UiPages::ImportInstanceMenu)
    {
        instance_creation_bg.render(window);
        instance_creation_info1_bg.render(window);
        instance_creation_info2_bg.render(window);

        import_instance_name_textbox.render(window);

        if (versions_list_ddl.getState() == false)
        {
            import_instance_path_textbox.render(window);
            import_instance_path_browse_button.render(window);
            import_instance_confirm_button.render(window);
            import_instance_cancel_button.render(window);
            window.draw(CreateInstanceUI::instance_file_separation_text);

            renderIconBar();
        }        

        window.draw(CreateInstanceUI::instance_ver_info_text);

        versions_list_ddl.render(window);
    }

    if (UI_current == UiPages::EditInstanceMenu)
    {
        instance_creation_bg.render(window);
        instance_creation_info1_bg.render(window);
        instance_creation_info2_bg.render(window);

        new_instance_name_textbox.render(window);

        if (versions_list_ddl.getState() == false)
        {
            saveEditedButton.render(window); 
            instance_creation_cancel.render(window);    
            window.draw(editInstanceSource);
            renderIconBar();
        }

        window.draw(CreateInstanceUI::instance_ver_info_text);
        versions_list_ddl.render(window); 
    }

    if (UI_current == UiPages::ManageMenu)
    {
        manage_bg.render(window);

        manage_vanilla_saves_button.render(window);
        manage_betterbuild_saves_button.render(window);
        manage_betterbuild_world_button.render(window);
        manage_backups_button.render(window);
        manage_mods_button.render(window);
        manage_main_back_button.render(window);

        manage_cats_separator.render(window);

        if (instanceDataLoading == true)
        {
            window.draw(dataLoading_text);
        }

        switch(manage_ui)
        {
            case MNG_MAIN_PAGE:
            {
                window.draw(MNG_Instance_name_text);
                window.draw(MNG_installed_mods_text);
                window.draw(MNG_Instance_saves_text);
                window.draw(MNG_instance_mods_own_text);
                window.draw(MNG_instance_mods_launcher_text);
                window.draw(tldr_text);
                break;
            }
            case BETTERBUILD_WORLDS:
            {
                for (const auto& pair : betterbuildworlds_list)
                {
                    betterbuildworlds_list[pair.first].render(window);
                }
                window.draw(bbw_tittle_text);
                break;
            }
            case VANILLA_SAVES:
            {
                window.draw(vsc_text);
                for (const auto& pair : vanillasaves_list)
                {
                    vanillasaves_list[pair.first].render(window);
                }
                break;
            }
            case BETTERBUILD_SAVES:
            {
                window.draw(msc_text);
                for (const auto& pair : betterbuildsaves_list)
                {
                    betterbuildsaves_list[pair.first].render(window);
                }
                break;
            }
            case MODS_PAGE:
            {
                if (versionsData_map[instances_list[selected_instance].getVer()].mod_support == true)
                {
                    window.draw(list_mods_instance_text);
                    window.draw(list_mods_launcher_text);
                    mods_separator.render(window);

                    for (const auto& pair : InstanceMods_list)
                    {
                        InstanceMods_list[pair.first].render(window);
                    }
                    for (const auto& pair : LauncherMods_list)
                    {
                        LauncherMods_list[pair.first].render(window);
                    }    
                }
                else
                {
                    window.draw(bbw_tittle_text);
                }
                break;
            }
            case BACKUPS:
            {
                for (const auto& pair : Backups_list)
                {
                    Backups_list[pair.first].render(window);
                }
                break;
            }
        }
    }

    if (UI_current == UiPages::VersionDescriptionMenu)
    {
        ver_desc_bg.render(window);
        window.draw(version_description_text);
        version_back_button.render(window);
    }

    if (UI_current == UiPages::SettingsMenu)
    {
        renderCategories();
        
        settings_bg.render(window);
        Subcat_settings_main_button.render(window);
        Subcat_settings_progile_button.render(window);
        Subcat_settings_downloading_button.render(window);
        Subcat_settings_updates_button.render(window);
        Subcat_settings_debugging_button.render(window);
        Subcat_settings_credits_button.render(window);
        Subcat_settings_licences_button.render(window);

        subcat_separator.render(window);

        if (options_ui == SettingsCategories::MAIN_PAGE)
        {
            if (mounted_instance != UNMOUNTED_INSTANCE)
            {
                window.draw(blockedPaths_text);
            }

            SlimeRancher_steam_path_textbox.render(window);
            SlimeRancher_instances_path_textbox.render(window);
            SlimeRancher_steam_path_getfolder_button.render(window);
            SlimeRancher_instances_path_getfolder_button.render(window);

            Show_prereleases_checkbox.render(window);
            Save_logs_files_checkbox.render(window);
            Colored_logs_checkbox.render(window);

            do_not_show_warnings_checkbox.render(window);
            use_secure_ipc_checkbox.render(window);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);

            window.draw(theme_label_text);
            theme_list_ddl.render(window);
        }
        if (options_ui == SettingsCategories::PROFILE_PAGE)
        {
            SteamProfile_name_textbox.render(window);
            SteamProfile_password_textbox.render(window);
            save_profile_button.render(window);
            window.draw(profile_presonal_data_warning_text);
            window.draw(steam_profile_icon);

            window.draw(Profile_warning_text);

            window.draw(steam_profile_offline_status_text);
            window.draw(steam_profile_AccountName_text);
            window.draw(steam_profile_PersonalName_text);
            window.draw(steam_profile_UID_text);
        }
        if (options_ui == SettingsCategories::DOWNLOADING_PAGE)
        {
            steamcmd_path_textbox.render(window);
            steamcmd_path_getfolder_button.render(window);
            automatically_run_downloaded_instances_checkbox.render(window);
            window.draw(downloaders_list_text);
            downloaders_ddl.render(window);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);
        }
        if (options_ui == SettingsCategories::UPDATES_PAGE)
        {
            check_for_update_button.render(window);
            autocheck_for_update_checkbox.render(window);
            window.draw(update_status_text);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);
        }
        if (options_ui == SettingsCategories::DEBUGGING_PAGE)
        {
            window.draw(DebugSettingsUI::debug_info_text);
            DebugSettingsUI::debuggingEnabledCheckbox.render(window);
            DebugSettingsUI::saveDebugLogsToOtherFileCheckbox.render(window);
            DebugSettingsUI::printDebugLogsCheckbox.render(window);
            DebugSettingsUI::comunicationDelayTextbox.render(window);
            DebugSettingsUI::comunicationPipeBufferSizeTextbox.render(window);
            DebugSettingsUI::saveLogFileButton.render(window);
            DebugSettingsUI::forcePipeCloseButton.render(window);
            DebugSettingsUI::killInstanceButton.render(window);
            DebugSettingsUI::acceptInfoCheckbox.render(window);
            DebugSettingsUI::acceptWarningCheckbox.render(window);
            DebugSettingsUI::acceptErrorCheckbox.render(window);
            DebugSettingsUI::acceptExceptionCheckbox.render(window);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);
        }
        if (options_ui == SettingsCategories::CREDITS_PAGE)
        {
            window.draw(credits_programming_text);
        }
        if (options_ui == SettingsCategories::LICENCES_PAGE)
        {
            LicencesUI::licenseField.render(window);
        }
    }

    if (UI_current == UiPages::VersionsList)
    {
        versions_bg.render(window);
        for (const auto& pair : versions_pachnotes_list)
        {
            versions_pachnotes_list[pair.first].render(window);   
        }

        renderCategories();
    }

    devUiView.render(window);
}