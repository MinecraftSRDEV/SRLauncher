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

std::string launcher_version = "inDev 0.2";

fs::path instances_path = defaultDir / "instances";
fs::path backups_path = defaultDir / "backups";
fs::path configuration_path = defaultDir / "config";
fs::path temp_path = defaultDir / "temp";
fs::path cmd_path = defaultDir / "SteamCMD";
fs::path logs_path = defaultDir / "logs";

std::map <int, std::string> logs;

int run_YEAR;
int run_MONTH;
int run_DAY;
int run_H;
int run_M;
int run_S;

#define Cyan "\e[1;36m"
#define Yellow "\e[1;33m"
#define Red "\e[1;31m"
#define Clear "\e[0m"