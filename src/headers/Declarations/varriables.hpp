bool window_actived = true;

int UI_current = 0;
int options_ui = 0;
int manage_ui = 0;

std::string steam_game_dir;
std::string mounted_instance;
std::string instances_dir;
std::string steamcmd_dir;

std::string steam_profile_name;
std::string steam_profile_passwd;

bool save_log_files = true;
bool display_log_colors = true;

bool show_prerelease_version = true;
bool autolaunch_instances = true;
bool show_warnings = true;

std::string temp_mount;
bool is_mouse_pressed = false;
bool is_mouse_rels = false;

bool game_downloading = false;
bool game_running = false;

bool check_updates_when_start = true;

bool instanceDataLoading = false;
bool instancesListLoading = false;

bool display_download_progress = false;

bool send_guard_code = false;
bool display_guard_window = false;

int user_offline_mode = 2;

std::string guard_code;

std::string launcher_version = "inDev 0.8";
std::string saved_version;

/// Launcher Paths ////

fs::path defaultDir;

fs::path instances_path;
fs::path backups_path;
fs::path configuration_path;
fs::path cmd_path;
fs::path components_path;
fs::path downloader_path;
fs::path logs_path;
fs::path mods_path;
fs::path steam_default_path;

fs::path UMFmodsFolder_path;
fs::path SMTFolder_path;
fs::path SMLFolder_path;
fs::path SRMLmodsFolder_path;

//////////////////////////
/// Scrollable iterations

std::string instance_list_b;
std::string instance_list_l;

//////////////////////////

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

int theme_selected = ColorPalete::Bright;

int downloader_selected = 0;

std::string selected_instance;

#define Cyan "\e[1;36m"
#define Yellow "\e[1;33m"
#define Red "\e[1;31m"
#define Clear "\e[0m"