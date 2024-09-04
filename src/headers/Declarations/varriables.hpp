bool window_actived = true;

int UI_current = 0;
int options_ui = 0;

std::string steam_game_dir;
std::string mounted_instance;
std::string instances_dir;

std::string steam_profile_name;
std::string steam_profile_passwd;

bool save_log_files = true;
bool loging_manualy = false;

bool show_prerelease_version = true;

std::string temp_mount;
bool is_mouse_pressed = false;
bool is_mouse_rels = false;

bool game_downloading = false;
bool game_running = false;

std::string launcher_version = "inDev 0.5";
std::string saved_version;

/// Launcher Paths ////

fs::path defaultDir;

fs::path instances_path;
fs::path backups_path;
fs::path configuration_path;
fs::path temp_path;
fs::path cmd_path;
fs::path logs_path;

///////////////////////

fs::path autobackup_path;

fs::path local_save_path;
fs::path prf_file_path;

std::map <int, std::string> logs;
std::vector <fs::path> external_instances;

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