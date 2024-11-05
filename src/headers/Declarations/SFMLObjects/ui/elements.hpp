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
    sfg::TransparrentBackground main_page_playbar_bg;
    sfg::Button launch_game_button;
    sf::Text mounted_instance_version;
    sf::Text Mounted_instance_info_text;
    sf::Text Launcher_version_text;
    sf::Text downloading_progress_text;
    SteamGuardAuthClass GuardBox;
    sfg::Button console_clear_button;
}

namespace InstanceslistElements
{
    sfg::Button new_instance_button;
    sfg::Button import_instnace_button;
    sfg::TransparrentBackground instances_bg;
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
    sfg::Button RestoreSettings_button;
    sfg::Button SaveConfig_button;
}

namespace SettingsSubcatsUI
{
    sfg::Button Subcat_settings_main_button;
    sfg::Button Subcat_settings_progile_button;
    sfg::Button Subcat_settings_updates_button;
    sfg::Button Subcat_settings_credits_button;
    sfg::Button Subcat_settings_licences_button;
    sfg::TransparrentBackground subcat_separator;
}

namespace MainSettingsUI
{
    sfg::Textbox SlimeRancher_steam_path_textbox;
    sfg::Button SlimeRancher_steam_path_getfolder_button;
    sfg::Textbox SlimeRancher_instances_path_textbox;
    sfg::Button SlimeRancher_instances_path_getfolder_button;
    sfg::Textbox steamcmd_path_textbox;
    sfg::Button steamcmd_path_getfolder_button;
    sfg::Checkbox Show_prereleases_checkbox;
    sfg::Checkbox Save_logs_files_checkbox;
    sfg::Checkbox Colored_logs_checkbox;
    sfg::Checkbox automatically_run_downloaded_instances_checkbox;
    sfg::Checkbox do_not_show_warnings_checkbox;
    sf::Text theme_label_text;
    sfg::DropDownList theme_list_ddl;
    sf::Text downloaders_list_text;
    sfg::DropDownList downloaders_ddl;

}

namespace SteamAccountSettingsUI
{
    sfg::Textbox SteamProfile_name_textbox;
    sfg::Passwordbox SteamProfile_password_textbox;
    sfg::Button save_profile_button;
    sf::Text Profile_warning_text;
    sf::Sprite steam_profile_icon;
    sf::Texture profile_icon_tx;
    sf::Texture userAvatar_tx;
    sf::Text steam_profile_offline_status_text;
    sf::Text steam_profile_AccountName_text;
    sf::Text steam_profile_PersonalName_text;
    sf::Text steam_profile_UID_text;
    sf::Text profile_presonal_data_warning_text;
}

namespace UpdatesSettingsUI
{
    sf::Text update_status_text;
    sfg::Button check_for_update_button;
    sfg::Checkbox autocheck_for_update_checkbox;    
}

namespace CreditsUI
{
    sf::Text credits_programming_text;
}

namespace LicencesUI
{
    sfg::Textfield licenseField;
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
    sfg::Button manage_vanilla_saves_button;
    sfg::Button manage_betterbuild_saves_button;
    sfg::Button manage_betterbuild_world_button;
    sfg::Button manage_backups_button;
    sfg::Button manage_mods_button;
    sfg::Button manage_main_back_button;
    sfg::TransparrentBackground manage_cats_separator;
}

namespace ManageMainUI
{
    sf::Text MNG_Instance_name_text;
    sf::Text MNG_installed_mods_text;
    sf::Text MNG_Instance_saves_text;
    sf::Text MNG_instance_mods_own_text;
    sf::Text MNG_instance_mods_launcher_text;
    sf::Text tldr_text;
}

namespace ManageModsUI
{
    sf::Text list_mods_instance_text;
    sf::Text list_mods_launcher_text;
    sfg::TransparrentBackground mods_separator;
}

namespace ManageOthers
{
    sf::Text bbw_tittle_text;
    sf::Text vsc_text;
    sf::Text msc_text;
    sfg::TransparrentBackground manage_bg;
}

sfg::DropDownList versions_list_ddl;

sf::Text dataLoading_text;

sfg::Button saveEditedButton;
sf::Text editInstanceSource;

UiViewer devUiView;