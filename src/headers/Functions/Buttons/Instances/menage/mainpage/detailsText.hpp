/**
 * Set and center details texts
 * 
 * @param m2 Instance name
 * @param m3 Vanilla saves count
 * @param m4 Installed mods count
 * @param m5 Launcher mods count
 */
void setAndPositionMngMainTexts(const std::string& m2, const std::string& m3, const std::string& m4, const std::string& m5)
{
    MNG_Instance_name_text.setString("Instance name: " + m2);
    MNG_Instance_saves_text.setString("Vanilla saves count: " + m3);
    MNG_instance_mods_own_text.setString("Instance installed mods: " + m4);
    MNG_instance_mods_launcher_text.setString("Launcher mods: " + m5);

    MNG_Instance_name_text.setPosition(130 + (575 - MNG_Instance_name_text.getLocalBounds().width / 2), 100);
    MNG_Instance_saves_text.setPosition(130 + (575 - MNG_Instance_saves_text.getLocalBounds().width / 2), 150);
    MNG_instance_mods_own_text.setPosition(130 + (575 - MNG_instance_mods_own_text.getLocalBounds().width / 2), 200);
    MNG_instance_mods_launcher_text.setPosition(130 + (575 - MNG_instance_mods_launcher_text.getLocalBounds().width / 2), 250);
    bbw_tittle_text.setPosition(130 + (575 - bbw_tittle_text.getLocalBounds().width / 2), 300);
}

/**
 * Removing string from all instance details texts
 */
void eraseMngMainTexts()
{
    MNG_Instance_name_text.setString("");
    MNG_Instance_saves_text.setString("");
    MNG_instance_mods_own_text.setString("");
    MNG_instance_mods_launcher_text.setString("");
}