/**
 * Function used for construct paths to every directories used by Launcher.
 * First use getUserDir funtion to get user %AppData% path.
 * Finaly results are saved to all paths declareted in "varriables.hpp" as "Launcher".  
 * 
 * This is onetime use function. 
 */
void construct_paths()
{
    fs::path userDir = fs::path(getUserProfile());
    defaultDir = userDir / "AppData" / "Roaming" / "SRLauncher";
    local_save_path = userDir / "AppData" / "LocalLow" / "Monomi Park" / "Slime Rancher";

    instances_path = defaultDir / "instances";
    backups_path = defaultDir / "backups";
    autobackup_path = backups_path / "PreLauncherInstalled";
    configuration_path = defaultDir / "config";
    components_path = defaultDir / "components";
    cmd_path = defaultDir / components_path / "SteamCMD";
    downloader_path = defaultDir / components_path / "depotDownloader";
    logs_path = defaultDir / "logs";
    mods_path = defaultDir/ "mods";
    steam_default_path = fs::path(get_steamLocation_default_path());
    
    UMFmodsFolder_path = mods_path / "UMF";
    SMTFolder_path = mods_path / "SMT";
    SMLFolder_path = mods_path / "SML";
    SRMLmodsFolder_path = mods_path / "SRML";
}