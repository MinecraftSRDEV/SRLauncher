bool window_actived = true;

int UI_current = 0;
int options_ui = 0;

fs::path defaultDir;

std::string steam_game_dir;
std::string mounted_instance;
std::string instances_dir;

std::string steam_profile_name;
std::string steam_profile_passwd;

std::string temp_mount;
bool is_mouse_pressed = false;
bool is_mouse_rels = false;

bool game_downloading = false;

fs::path instances_path = defaultDir / "instances";
fs::path backups_path = defaultDir / "backups";
fs::path configuration_path = defaultDir / "config";
fs::path temp_path = defaultDir / "temp";
fs::path cmd_path = defaultDir / "SteamCMD";