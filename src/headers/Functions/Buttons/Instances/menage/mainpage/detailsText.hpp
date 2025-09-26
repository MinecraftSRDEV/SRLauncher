/**
 * Set and center details texts
 * 
 * @param m2 Instance name
 * @param m3 Vanilla saves count
 * @param m4 Installed mods count
 * @param m5 Launcher mods count
 */
void setAndPositionMngMainTexts(ManageResult results)
{
    MNG_Instance_name_text.setString(tr("IDS_MNGMAIN_INSTNAME") + results.name);

    MNG_Instance_saves_text.setText(tr("IDS_MNGMAIN_VSAVESCOUNT") + results.vSavesCount);
    MNG_instance_installed_mods_text.setText(tr("IDS_MNGMAIN_MODSCOUNT") + results.installedModsCount);
    MNG_instance_mods_saves_text.setText(tr("IDS_MNGMAIN_MSAVESCOUNT") + results.modSavesCount);
    MNG_instance_mods_launcher_text.setText(tr("IDS_MNGMAIN_LAUNCHERMODSCOUNT") + results.launcherModsCount);

    if (results.bb_status == true)
    {
        MNG_betterBuild_status.setString(tr("IDS_MNGMAIN_BBSTATUS_INST"));
        MNG_instance_mods_saves_text.setBlockState(false);
    }
    else
    {
        MNG_betterBuild_status.setString(tr("IDS_MNGMAIN_BBSTATUS_NINST"));
        MNG_instance_mods_saves_text.setBlockState(true);
    }

    if (results.bb_uid.empty())
    MNG_betterBuild_UID.setString(tr("IDS_MNGMAIN_BBUID_UNKNOWN"));
    else
    MNG_betterBuild_UID.setString(tr("IDS_MNGMAIN_BBUID") + results.bb_uid);

    MNG_instance_icon.setTexture(results.iconTx);

    MNG_Instance_name_text.setPosition(130 + (575 - MNG_Instance_name_text.getLocalBounds().width / 2), 5);
    bbw_tittle_text.setPosition(130 + (575 - bbw_tittle_text.getLocalBounds().width / 2), 300);

    MNG_instance_icon.setPosition(140, 5); 
}

/**
 * Removing string from all instance details texts
 */
void eraseMngMainTexts()
{
    MNG_Instance_name_text.setString("");
    MNG_Instance_saves_text.setText("");
    MNG_instance_installed_mods_text.setText("");
    MNG_instance_mods_saves_text.setText("");
    MNG_instance_mods_launcher_text.setText("");
}