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
    temp_path = defaultDir / "temp";
    cmd_path = defaultDir / "SteamCMD";
    logs_path = defaultDir / "logs";
}