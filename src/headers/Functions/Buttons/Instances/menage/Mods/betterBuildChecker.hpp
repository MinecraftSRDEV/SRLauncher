/**
 * Universal function responsible for check if BetterBuild mod is installed.
 * 
 * TRUE:
 * Run scanBetterBuildWordls function.
 * 
 * FALSE:
 * Set bbw_tittle_text to not installed.
 * 
 * @param modName Name of BetterBuild mod file
 * @param instance_mods_directory Pointer to directory for scanner
 * @param loader Pointer to loader for scanner
 */
bool checkBetterBuildInstalled(const std::string& modName, const fs::path& instance_mods_directory)
{
    if (findModInMap(modName) > 0)
    {
        bbw_tittle_text.setString("");
        log_message("BetterBuildMod installed", LogTypes::LOG_INFO);
        fs::path instance_betterbuild_directory = instance_mods_directory / "BetterBuild";
        directory_auto(instance_betterbuild_directory);
        return true;
    }
    else
    {
        bbw_tittle_text.setString(tr("IDS_TEXT_BBCHECKER_NOTINSTALLED"));
        bbw_tittle_text.setPosition(window.getSize().x / 2 - (bbw_tittle_text.getLocalBounds().width / 2) + 130, 380);
    }
    return false;
}