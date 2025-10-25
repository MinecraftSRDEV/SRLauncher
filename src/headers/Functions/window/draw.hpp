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

        MainpageElements::playbar::background.render(window);
        MainpageElements::lastPlayed::background.render(window);
        MainpageElements::details::background.render(window);

        if (miniInstanceList::dataLoading)
        {
            window.draw(MainpageElements::lastPlayed::loadingMiniInstancesText);
        }
        else
        {
            if (miniInstancesListMap.size() > 0)
            {
                for (const auto& pair : miniInstancesListMap)
                {
                    miniInstancesListMap[pair.first].render(window);
                }     
            }  
            else
            {
                window.draw(MainpageElements::lastPlayed::noLastPlayedInstancesText);
            }    
        }

        if (miniInstanceList::instanceHilighted)
        {
            window.draw(MainpageElements::details::lastPlayedDateText);
            window.draw(MainpageElements::details::totalPlayTimeInstanceText);
        }
        else
        {
            window.draw(MainpageElements::details::totalLauncherPlaytimeText);
        }

        if (mounted_instance != UNMOUNTED_INSTANCE)
        {
            MainpageElements::playbar::launchGameButton.render(window);    
        }

        if (game_downloading == true)
        {
            if (downloadInitializing == true)
            {
                window.draw(MainpageElements::playbar::progress_bg);
                window.draw(MainpageElements::playbar::progress_moveing);    
            }
            else
            {
                MainpageElements::playbar::downloadingProgress.render(window);
            }
        }

        window.draw(MainpageElements::playbar::infoText);
        window.draw(MainpageElements::playbar::LauncherVersionText);
        if (MainpageElements::playbar::versionText.getString() != "")
        {
            window.draw(MainpageElements::playbar::versionText);
        }

        if (display_download_progress == true)
        {
            window.draw(MainpageElements::playbar::downloadingProgressText);
        }

        if (display_guard_window == true)
        {
            MainpageElements::GuardBox.render(window);
        }

        if (game_running == true)
        {
            if (SettingsElemets::subcats::debug::debuggingEnabledCheckbox.getState() == true)
            {
                window.draw(MainpageElements::debuger::working);
                window.draw(MainpageElements::debuger::ipcElapsedText);
            }
        }

        if (SettingsElemets::subcats::debug::debuggingEnabledCheckbox.getState() == true)
        {
            window.draw(MainpageElements::details::debugWarnText);
        }

        MainpageElements::console::console.render(window);
        MainpageElements::console::clearButton.render(window);
    }

    if (UI_current == UiPages::InstancesMenu)
    {
        renderCategories();

        instances_bg.render(window);
        
        if (instancesLoader::instancesListLoading == false)
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

    if (UI_current == UiPages::InstanceDetailsMenu)
    {
        InstanceDetailsElements::bg.render(window);
        InstanceDetailsElements::head::separation.render(window);
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

        ManageSubcatListUI::vanilla_saves_button.render(window);
        ManageSubcatListUI::betterbuild_saves_button.render(window);
        ManageSubcatListUI::betterbuild_world_button.render(window);
        ManageSubcatListUI::backups_button.render(window);
        ManageSubcatListUI::mods_button.render(window);
        ManageSubcatListUI::main_back_button.render(window);
        ManageSubcatListUI::informations_button.render(window);
        ManageSubcatListUI::debug_button.render(window);

        ManageSubcatListUI::cats_separator.render(window);

        if (instancesLoader::instanceDataLoading == true)
        {
            window.draw(dataLoading_text);
        }

        switch(manage_ui)
        {
            case ManageCategories::MNG_MAIN_PAGE:
            {
                if (instancesLoader::instanceDataLoading == false)
                {
                    window.draw(MNG_instance_icon);
                    window.draw(MNG_Instance_name_text);
                    MNG_Instance_saves_text.render(window);
                    MNG_instance_installed_mods_text.render(window);
                    MNG_instance_mods_saves_text.render(window);
                    MNG_instance_mods_launcher_text.render(window);
                    window.draw(MNG_betterBuild_status);
                    window.draw(MNG_betterBuild_UID);
                }
                
                window.draw(tldr_text);
                break;
            }
            case ManageCategories::BETTERBUILD_WORLDS:
            {
                for (const auto& pair : betterbuildworlds_list)
                {
                    betterbuildworlds_list[pair.first].render(window);
                }
                window.draw(bbw_tittle_text);
                break;
            }
            case ManageCategories::VANILLA_SAVES:
            {
                window.draw(vsc_text);
                for (const auto& pair : vanillasaves_list)
                {
                    vanillasaves_list[pair.first].render(window);
                }
                break;
            }
            case ManageCategories::BETTERBUILD_SAVES:
            {
                window.draw(msc_text);
                for (const auto& pair : betterbuildsaves_list)
                {
                    betterbuildsaves_list[pair.first].render(window);
                }
                break;
            }
            case ManageCategories::MODS_PAGE:
            {
                window.draw(instanceModsMouseWorkingBox);
                window.draw(launcherModsMouseWorkingBox);
                
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
            case ManageCategories::BACKUPS:
            {
                for (const auto& pair : Backups_list)
                {
                    Backups_list[pair.first].render(window);
                }
                break;
            }
            case ManageCategories::DEBUG_PAGE:
            {
                ManageDebug::assemblyInfoBg.render(window);
                window.draw(ManageDebug::assemblyDataText);
                window.draw(ManageDebug::debugPatchStatusText);
                ManageDebug::debugPatchButton.render(window);
                window.draw(ManageDebug::selectedFrameworkLabelText);
                ManageDebug::selectedFramework.render(window);
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
        using namespace SettingsElemets;
        
        settings_bg.render(window);
        subcatsBar::generalCat_button.render(window);
        subcatsBar::profileCat_button.render(window);
        subcatsBar::downloadingCat_button.render(window);
        subcatsBar::updatesCat_button.render(window);
        subcatsBar::debuggingCat_button.render(window);
        subcatsBar::creditsCat_button.render(window);
        subcatsBar::licencesCat_button.render(window);

        subcatsBar::subcat_separator.render(window);

        using namespace SettingsElemets::subcats;
        using namespace SettingsElemets::bottomBar;

        if (options_ui == SettingsCategories::MAIN_PAGE)
        {
            if (mounted_instance != UNMOUNTED_INSTANCE)
            {
                window.draw(general::blockedPaths_text);
            }

            general::steam_path_textbox.render(window);
            general::instances_path_textbox.render(window);
            general::steam_path_getfolder_button.render(window);
            general::instances_path_getfolder_button.render(window);

            general::Show_prereleases_checkbox.render(window);
            general::Save_logs_files_checkbox.render(window);
            general::Colored_logs_checkbox.render(window);

            general::do_not_show_warnings_checkbox.render(window);
            general::use_secure_ipc_checkbox.render(window);
            general::mount_only_data_checkbox.render(window);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);

            save_config_separator.render(window);

            window.draw(general::theme_label_text);
            window.draw(general::language_labet_text);
            general::theme_list_ddl.render(window);
            general::languages_list_ddl.render(window);

            general::SRL_background_img_path_textbox.render(window);
            general::SRL_background_img_path_getfolder_button.render(window);
        }
        if (options_ui == SettingsCategories::PROFILE_PAGE)
        {
            steamAccount::profileName_textbox.render(window);
            steamAccount::profilePassword_textbox.render(window);
            steamAccount::save_profile_button.render(window);
            window.draw(steamAccount::profilePresonal_data_warning_text);
            window.draw(steamAccount::profileIcon);

            window.draw(steamAccount::Profile_warning_text);

            window.draw(steamAccount::profileOffline_status_text);
            window.draw(steamAccount::profileAccountName_text);
            window.draw(steamAccount::profilePersonalName_text);
            window.draw(steamAccount::profileUID_text);

            save_config_separator.render(window);
        }
        if (options_ui == SettingsCategories::DOWNLOADING_PAGE)
        {
            SettingsElemets::subcats::downloading::steamcmd_path_textbox.render(window);
            SettingsElemets::subcats::downloading::steamcmd_path_getfolder_button.render(window);
            SettingsElemets::subcats::downloading::automatically_run_downloaded_instances_checkbox.render(window);
            window.draw(SettingsElemets::subcats::downloading::downloaders_list_text);
            SettingsElemets::subcats::downloading::downloaders_ddl.render(window);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);

            save_config_separator.render(window);
        }
        if (options_ui == SettingsCategories::UPDATES_PAGE)
        {
            SettingsElemets::subcats::updates::check_for_update_button.render(window);
            SettingsElemets::subcats::updates::autocheck_for_update_checkbox.render(window);
            window.draw(SettingsElemets::subcats::updates::update_status_text);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);

            save_config_separator.render(window);
        }
        if (options_ui == SettingsCategories::DEBUGGING_PAGE)
        {
            window.draw(SettingsElemets::subcats::debug::debug_info_text);
            SettingsElemets::subcats::debug::debuggingEnabledCheckbox.render(window);
            SettingsElemets::subcats::debug::saveDebugLogsToOtherFileCheckbox.render(window);
            SettingsElemets::subcats::debug::printDebugLogsCheckbox.render(window);
            SettingsElemets::subcats::debug::comunicationDelayTextbox.render(window);
            SettingsElemets::subcats::debug::comunicationPipeBufferSizeTextbox.render(window);
            SettingsElemets::subcats::debug::saveLogFileButton.render(window);
            SettingsElemets::subcats::debug::forcePipeCloseButton.render(window);
            SettingsElemets::subcats::debug::killInstanceButton.render(window);
            SettingsElemets::subcats::debug::acceptInfoCheckbox.render(window);
            SettingsElemets::subcats::debug::acceptWarningCheckbox.render(window);
            SettingsElemets::subcats::debug::acceptErrorCheckbox.render(window);
            SettingsElemets::subcats::debug::acceptExceptionCheckbox.render(window);

            RestoreSettings_button.render(window);
            SaveConfig_button.render(window);

            save_config_separator.render(window);
        }
        if (options_ui == SettingsCategories::CREDITS_PAGE)
        {
            window.draw(SettingsElemets::subcats::credits::credits_programming_text);
            window.draw(SettingsElemets::subcats::credits::github_page_link_text);
            window.draw(SettingsElemets::subcats::credits::repos_page_link_text);
            window.draw(SettingsElemets::subcats::credits::issules_page_link_text);
        }
        if (options_ui == SettingsCategories::LICENCES_PAGE)
        {
            SettingsElemets::subcats::licences::licenseField.render(window);
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

    if (loadingAnimationDisplay)
    {
        window.draw(loading_icon);    
    }
}