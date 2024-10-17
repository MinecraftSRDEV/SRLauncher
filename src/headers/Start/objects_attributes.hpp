void setRuntimeTexts()
{
    Mounted_instance_info_text.setFont(font);
    Mounted_instance_info_text.setCharacterSize(36);
    Mounted_instance_info_text.setPosition(10, 725);

    mounted_instance_version.setFont(font);
    mounted_instance_version.setCharacterSize(16);
    mounted_instance_version.setPosition(10, 765);

    Launcher_version_text.setFont(font);
    Launcher_version_text.setCharacterSize(36);
    Launcher_version_text.setString(launcher_version);
    Launcher_version_text.setPosition((window.getSize().x - 10) - Launcher_version_text.getLocalBounds().width, 725);

    bbw_tittle_text.setFont(font);
    bbw_tittle_text.setCharacterSize(26);

    update_status_text.setFont(font);
    update_status_text.setCharacterSize(26);
    update_status_text.setPosition(130, 380);
    update_status_text.setString("No update data");

    theme_label_text.setFont(font);
    theme_label_text.setCharacterSize(26);
    theme_label_text.setPosition(130, 520);
    theme_label_text.setString("Launcher theme (experimental)\n\n\nRequire restart");

    credits_programming_text.setFont(font);
    credits_programming_text.setCharacterSize(32);
    credits_programming_text.setPosition(130, 380);
    credits_programming_text.setString("Programming: MCSR");

    dataLoading_text.setFont(font);
    dataLoading_text.setCharacterSize(32);
    dataLoading_text.setPosition(130, 380);

    downloading_progress_text.setFont(font);
    downloading_progress_text.setCharacterSize(20);
    downloading_progress_text.setPosition(130, 380);

    downloaders_list_text.setFont(font);
    downloaders_list_text.setCharacterSize(26);
    downloaders_list_text.setPosition(680, 520);
    downloaders_list_text.setString("Selected depot downloader");

    version_description_text.setFont(font);
    version_description_text.setCharacterSize(26);
    version_description_text.setPosition(10, 10);

    Profile_warning_text.setFont(font);
    Profile_warning_text.setCharacterSize(26);
    Profile_warning_text.setPosition(130, 600);

    steam_profile_offline_status_text.setFont(font);
    steam_profile_offline_status_text.setCharacterSize(26);
    steam_profile_offline_status_text.setPosition(320, 270);

    steam_profile_AccountName_text.setFont(font);
    steam_profile_AccountName_text.setCharacterSize(26);
    steam_profile_AccountName_text.setPosition(320, 300);

    steam_profile_PersonalName_text.setFont(font);
    steam_profile_PersonalName_text.setCharacterSize(26);
    steam_profile_PersonalName_text.setPosition(320, 330);

    steam_profile_UID_text.setFont(font);
    steam_profile_UID_text.setCharacterSize(26);
    steam_profile_UID_text.setPosition(320, 360);

    list_mods_instance_text.setFont(font);
    list_mods_instance_text.setCharacterSize(19);
    list_mods_instance_text.setString("Installed mods");
    list_mods_instance_text.setPosition(130 + (280 - (list_mods_instance_text.getLocalBounds().width / 2)), 0);

    list_mods_launcher_text.setFont(font);
    list_mods_launcher_text.setCharacterSize(19);
    list_mods_launcher_text.setString("Launcher mods");
    list_mods_launcher_text.setPosition((130 + 560) + ((10 + 280) - (list_mods_launcher_text.getLocalBounds().width / 2)), 0);

    MNG_Instance_name_text.setFont(font);
    MNG_Instance_name_text.setCharacterSize(26);
    MNG_Instance_name_text.setPosition(0, 0);
    MNG_Instance_name_text.setString("Instance name: ");

    bbw_tittle_text.setFont(font);
    bbw_tittle_text.setCharacterSize(26);
    bbw_tittle_text.setPosition(0, 0);

    MNG_Instance_saves_text.setFont(font);
    MNG_Instance_saves_text.setCharacterSize(26);
    MNG_Instance_saves_text.setPosition(0, 0);
    MNG_Instance_saves_text.setString("Game saves count");

    MNG_instance_mods_own_text.setFont(font);
    MNG_instance_mods_own_text.setCharacterSize(26);
    MNG_instance_mods_own_text.setPosition(0, 0);
    MNG_instance_mods_own_text.setString("Installed mods: ");

    MNG_instance_mods_launcher_text.setFont(font);
    MNG_instance_mods_launcher_text.setCharacterSize(26);
    MNG_instance_mods_launcher_text.setPosition(0, 0);
    MNG_instance_mods_launcher_text.setString("Launcher mods: ");
}

void setShapesAttributes()
{
    steam_profile_icon.setPosition(sf::Vector2f(130, 260));

    progress_bg.setSize(sf::Vector2f(1280, 20));
    progress_bg.setPosition(sf::Vector2f(0, 780));
    progress_bg.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::inactive]);

    progress_moveing.setSize(sf::Vector2f(70, 20));
    progress_moveing.setPosition(sf::Vector2f(-70, 780));
    progress_moveing.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::checkbox_inactive]);
}