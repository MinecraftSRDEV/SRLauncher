void renderCategories()
{
    categories_bg.render(window);
    MainCategory_button.render(window);
    InstancesCategory_button.render(window);
    SettingsCategory_button.render(window);
    VersionsCategory_button.render(window);
}

void window_draw()
{
    window.draw(background);
    
    if (UI_current == UI_PAGES::MainMenu)
    {
        renderCategories();

        console.render(window);
        console_clear_button.render(window);

        last_played_bg.render(window);
        launch_last_instance_button.render(window);

        if (game_downloading == true)
        {
            window.draw(progress_bg);
            window.draw(progress_moveing);
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
    }

    if (UI_current == UI_PAGES::InstancesMenu)
    {
        renderCategories();

        instances_bg.render(window);
        new_instance_button.render(window);
        import_instnace_button.render(window);

        if (instancesListLoading == false)
        {
            for (const auto& pair : instances_list)
            {
                instances_list[pair.first].render(window);
            }    
        }
        else
        {
            window.draw(dataLoading_text);
        }
    }

    if (UI_current == UI_PAGES::NewInstanceMenu)
    {
        new_instance_name_textbox.render(window);

        if (versions_list.getState() == false)
        {
            create_button.render(window); 
            instance_creation_cancel.render(window);    
        }

        versions_list.render(window); 
    }

    if (UI_current == UI_PAGES::ImportInstanceMenu)
    {
        import_instance_name_textbox.render(window);

        if (versions_list.getState() == false)
        {
            import_instance_path_textbox.render(window);
            import_instance_path_browse_button.render(window);
            import_instance_confirm_button.render(window);
            import_instance_cancel_button.render(window);    
        }        

        versions_list.render(window);
    }

    if (UI_current == UI_PAGES::ManageMenu)
    {
        manage_bg.render(window);

        manage_vanilla_saves_button.render(window);
        manage_mod_saves_button.render(window);
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
                break;
            }
            case BETTERBUILD_WORLDS:
            {
                for (const auto& pair : betterbuildworlds_list)
                {
                    betterbuildworlds_list[pair.first].render(window);
                    window.draw(bbw_tittle_text);
                }    
                break;
            }
            case MODS_PAGE:
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
                break;
            }
        }
    }

    if (UI_current == UI_PAGES::VersionDescriptionMenu)
    {
        ver_desc_bg.render(window);
        window.draw(version_description_text);
        version_back_button.render(window);
    }

    if (UI_current == UI_PAGES::SettingsMenu)
    {
        renderCategories();
        
        settings_bg.render(window);
        Subcat_settings_main_button.render(window);
        Subcat_settings_progile_button.render(window);
        Subcat_settings_updates_button.render(window);
        Subcat_settings_credits_button.render(window);

        subcat_separator.render(window);

        if (options_ui == SETTIGNS_CATEGORIES::MAIN_PAGE)
        {
            SlimeRancher_steam_path_textbox.render(window);
            SlimeRancher_instances_path_textbox.render(window);
            SlimeRancher_steam_path_getfolder_button.render(window);
            SlimeRancher_instances_path_getfolder_button.render(window);
            steamcmd_path_textbox.render(window);
            steamcmd_path_getfolder_button.render(window);

            Show_older_instances_checkbox.render(window);
            Save_logs_files_checkbox.render(window);
            Colored_logs_checkbox.render(window);

            automatically_run_downloaded_instances_checkbox.render(window);
            do_not_show_warnings_checkbox.render(window);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);

            window.draw(theme_label_text);
            theme_list_ddl.render(window);
            window.draw(downloaders_list_text);
            downloaders_ddl.render(window);
        }
        if (options_ui == SETTIGNS_CATEGORIES::PROFILE_PAGE)
        {
            SteamProfile_name_textbox.render(window);
            SteamProfile_password_textbox.render(window);
            save_profile_button.render(window);
            window.draw(steam_profile_icon);

            window.draw(Profile_warning_text);

            window.draw(steam_profile_offline_status_text);
            window.draw(steam_profile_AccountName_text);
            window.draw(steam_profile_PersonalName_text);
            window.draw(steam_profile_UID_text);
        }
        if (options_ui == SETTIGNS_CATEGORIES::UPDATES_PAGE)
        {
            check_for_update_button.render(window);
            autocheck_for_update_checkbox.render(window);
            window.draw(update_status_text);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);
        }
        if (options_ui == SETTIGNS_CATEGORIES::CREDITS_PAGE)
        {
            window.draw(credits_programming_text);
        }
    }

    if (UI_current == UI_PAGES::VersionsList)
    {
        versions_bg.render(window);
        for (const auto& pair : versions_pachnotes_list)
        {
            if (Show_older_instances_checkbox.getState() == true and versions_map[versions_pachnotes_list[pair.first].getVersion()].version_type != "pre_release")
            {
                versions_pachnotes_list[pair.first].render(window);
            }   
        }

        renderCategories();
    }
}