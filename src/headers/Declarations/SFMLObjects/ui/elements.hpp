namespace CategoriesUI
{
    sfg::TransparrentBackground categories_bg;
    sfg::Button MainCategory_button;
    sfg::Button InstancesCategory_button;
    sfg::Button SettingsCategory_button;
    sfg::Button VersionsCategory_button;
}

namespace MainpageElements
{
    SteamGuardAuthClass GuardBox;

    namespace playbar
    {
        sfg::TransparrentBackground background;
        sfg::Button launchGameButton;
        sf::Text versionText;
        sf::Text infoText;
        sf::Text LauncherVersionText;
        sf::Text downloadingProgressText;
        sf::RectangleShape progress_bg;
        sf::RectangleShape progress_moveing;
        ProgressBar downloadingProgress;
    }
    
    namespace lastPlayed
    {
        sfg::TransparrentBackground background;
        sf::RectangleShape mouseBox;
        sf::Text loadingMiniInstancesText;
        sf::Text noLastPlayedInstancesText;    
    }

    namespace details
    {
        sfg::TransparrentBackground background;
        sf::Text lastPlayedDateText;
        sf::Text totalPlayTimeInstanceText;
        sf::Text debugWarnText;
        sf::Text totalLauncherPlaytimeText;    
    }

    namespace console
    {
        sf::RectangleShape mouseBox;
        sfg::Button clearButton;
        sfg::Checkbox disableCheckbox;
    }    

    namespace debuger
    {
        sf::RectangleShape working;
        sf::Text ipcElapsedText;
    }
}

namespace InstanceslistElements
{
    sfg::Button new_instance_button;
    sfg::Button import_instnace_button;
    sfg::TransparrentBackground instances_bg;
    sf::Text no_instances_text;
    sf::Text instances_vanish_tooltip_text;
    sf::RectangleShape instancesScrollingArea;
}

namespace CreateInstanceUI
{
    sfg::TransparrentBackground instance_creation_bg;
    sfg::TransparrentBackground instance_creation_info1_bg;
    sfg::TransparrentBackground instance_creation_info2_bg;
    sfg::Textbox new_instance_name_textbox;
    sfg::Button create_button;
    sfg::Button instance_creation_cancel;
    sfg::Checkbox create_with_graphics_preset_checkbox;
    sfg::DropDownList graphics_preset_ddl;
    sfg::Checkbox automount_checkbox;
    sf::Text instance_ver_info_text;
    sf::Text isntance_will_be_created_in_text;
    sf::Text instance_file_separation_text;
}

namespace InstanceIconBar
{
    sfg::Button prev_button;
    sfg::Button next_button;
    sf::RectangleShape selectedBG;
    sf::Text icon_bar_text;
}

namespace ImportInstanceUI
{
    sfg::Textbox import_instance_name_textbox;
    sfg::Textbox import_instance_path_textbox;
    sfg::Button import_instance_path_browse_button;
    sfg::Button import_instance_confirm_button;
    sfg::Button import_instance_cancel_button;
    sfg::Checkbox move_imported_instance_files_checkbox;
}

namespace SettingsElemets
{
    sfg::TransparrentBackground settings_bg;
    
    namespace bottomBar
    {
        sfg::Button RestoreSettings_button;
        sfg::Button SaveConfig_button;

        sfg::TransparrentBackground save_config_separator;
    }

    namespace subcatsBar
    {
        sfg::Button generalCat_button;
        sfg::Button profileCat_button;
        sfg::Button updatesCat_button;
        sfg::Button downloadingCat_button;
        sfg::Button debuggingCat_button;
        sfg::Button licencesCat_button;
        sfg::Button creditsCat_button;

        sfg::TransparrentBackground subcat_separator;
    }

    namespace subcats
    {
        namespace general
        {
            sf::Text blockedPaths_text;
            sfg::Textbox steam_path_textbox;
            sfg::Button steam_path_getfolder_button;
            sfg::Textbox instances_path_textbox;
            sfg::Button instances_path_getfolder_button;
            sfg::Checkbox Show_prereleases_checkbox;
            sfg::Checkbox Save_logs_files_checkbox;
            sfg::Checkbox Colored_logs_checkbox;
            sfg::Checkbox do_not_show_warnings_checkbox;
            sfg::Checkbox use_secure_ipc_checkbox;
            sfg::Checkbox mount_only_data_checkbox;
            sf::Text theme_label_text;
            sfg::DropDownList theme_list_ddl;
            sf::Text language_labet_text;
            sfg::DropDownList languages_list_ddl;
            sfg::Textbox SRL_background_img_path_textbox;
            sfg::Button SRL_background_img_path_getfolder_button;
        }

        namespace steamAccount
        {
            sfg::Textbox profileName_textbox;
            sfg::Passwordbox profilePassword_textbox;
            sfg::Button save_profile_button;
            sf::Text Profile_warning_text;
            sf::Sprite profileIcon;
            sf::Texture profile_icon_tx;
            sf::Texture userAvatar_tx;
            sf::Text profileOffline_status_text;
            sf::Text profileAccountName_text;
            sf::Text profilePersonalName_text;
            sf::Text profileUID_text;
            sf::Text profilePresonal_data_warning_text;        
        }

        namespace downloading
        {
            sfg::Textbox steamcmd_path_textbox;
            sfg::Button steamcmd_path_getfolder_button;
            sfg::Checkbox automatically_run_downloaded_instances_checkbox;
            sf::Text downloaders_list_text;
            sfg::DropDownList downloaders_ddl;
        }

        namespace updates
        {
            sf::Text update_status_text;
            sfg::Button check_for_update_button;
            sfg::Checkbox autocheck_for_update_checkbox;    
        }

        namespace debug
        {
            sf::Text debug_info_text;
            sfg::Checkbox debuggingEnabledCheckbox;
            sfg::Checkbox saveDebugLogsToOtherFileCheckbox;
            sfg::Checkbox printDebugLogsCheckbox;
            sfg::Textbox comunicationDelayTextbox;
            sfg::Textbox comunicationPipeBufferSizeTextbox;
            sfg::Button forcePipeCloseButton;
            sfg::Button killInstanceButton;
            sfg::Button saveLogFileButton;
            sfg::Checkbox acceptInfoCheckbox;
            sfg::Checkbox acceptWarningCheckbox;
            sfg::Checkbox acceptErrorCheckbox;
            sfg::Checkbox acceptExceptionCheckbox;
        }

        namespace credits
        {
            sf::Text credits_programming_text;
            sf::Text github_page_link_text;
            sf::Text repos_page_link_text;
            sf::Text issules_page_link_text;
        }     
        
        namespace licences
        {
            sfg::Textfield licenseField;
        }        
    }
}

namespace VersionsElements
{
    sfg::TransparrentBackground versions_bg;
    sf::Text version_description_text;
    sfg::TransparrentBackground ver_desc_bg;
    sfg::Button version_back_button;
}

namespace ManageSubcatListUI
{
    sfg::Button informations_button;
    sfg::Button vanilla_saves_button;
    sfg::Button betterbuild_saves_button;
    sfg::Button betterbuild_world_button;
    sfg::Button backups_button;
    sfg::Button mods_button;
    sfg::Button debug_button;
    sfg::Button main_back_button;
    sfg::TransparrentBackground cats_separator;
}

namespace ManageMainUI
{
    sf::Sprite MNG_instance_icon;
    sf::Text MNG_Instance_name_text;

    ManagementButton MNG_Instance_saves_text;
    ManagementButton MNG_instance_installed_mods_text;
    ManagementButton MNG_instance_mods_saves_text;
    ManagementButton MNG_instance_mods_launcher_text;

    sf::Text MNG_betterBuild_status;
    sf::Text MNG_betterBuild_UID;
    sf::Text tldr_text;
}

namespace ManageModsUI
{
    sf::Text list_mods_instance_text;
    sf::Text list_mods_launcher_text;
    sfg::TransparrentBackground mods_separator;
    sf::RectangleShape instanceModsMouseWorkingBox;
    sf::RectangleShape launcherModsMouseWorkingBox;
}


namespace ManageDebug
{
    sf::Text assemblyDataText;
    sfg::TransparrentBackground assemblyInfoBg;
    sfg::Button debugPatchButton;
    sf::Text debugPatchStatusText;
}

namespace ManageOthers
{
    sf::Text bbw_tittle_text;
    sf::Text vsc_text;
    sf::Text msc_text;
    sfg::TransparrentBackground manage_bg;
}

namespace DebuggerMainmenuLayout
{
    sfg::Checkbox acceptInfoCheckbox;
    sfg::Checkbox acceptWarningCheckbox;
    sfg::Checkbox acceptErrorCheckbox;
    sfg::Checkbox acceptExceptionCheckbox;
    sf::Text messageDuplicatedText;
}

namespace BBGamesavesSlots
{
    sfg::Button A;
    sfg::Button B;
    sfg::Button C;
    sfg::Button back_button;
    sf::Text slotAText;
    sf::Text slotBText;
    sf::Text slotCText;
}

sfg::DropDownList versions_list_ddl;

sf::Text dataLoading_text;

sfg::Button saveEditedButton;
sf::Text editInstanceSource;

sf::Texture playtime_clock_tx;

UiViewer devUiView;