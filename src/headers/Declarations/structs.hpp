struct WindowsInfo
{
    DWORD MajorVersion;
    DWORD MinorVersion;
    DWORD BuildNumber;
    std::string sysLang = "en";
    bool sysTheme = true;
};

struct SRGamesaveInfo {
    bool readable_version = false;
    int format = 0;
    bool single_file = false;
};

struct SRVersion {
    std::string version_name = "";
    std::string release_date = "";
    std::string manifest = "";
    std::string version_type = "";
    int itr = 0;
    std::string executable_hash = "";
    std::string assembly_hash = "";
    SRGamesaveInfo savegame_info;
    std::string debugCompatybile = "";
};

struct InstanceModAttributes {
    bool isModded = false;

    bool StaysModtool_installed = false;
    bool SatysModLoader_installed = false;
    bool isBetterBuild04x_installed = false;
    bool SRML_installed = false;
    bool UMF_installed = false;

    std::vector <fs::directory_iterator> StaysModtool_mods_list;
    std::vector <fs::directory_iterator> SatysModLoader_mods_list;
    std::vector <fs::directory_iterator> UMF_mods_list;
    std::vector <fs::directory_iterator> SRML_mods_list;
};

namespace miniInstanceList
{
    struct attributes{
        sf::Texture& icon_texture;
        sf::Texture& clock_texture;

        sf::Font& font;
        sf::RenderWindow& window;

        int x;
        int y;
        int size_x;
        int size_y;
        int it_number;

        std::string lastPlayed;
        std::string name;
        std::string version;
        InstanceModAttributes modsAtrb;
        std::string playtime_count;
    };
};

struct WorldData {
    int16_t version;
    bool levelLocked;
    std::string levelPassword;
    int objectCount;
    int spawnerCount;
    std::string levelname;
};

struct SavegameData {
    std::string name = "";
    std::string displayedText = "";
    std::string version = "";
    std::string last_played = "";
    int currency = 0;
    int day = 0;
    int slimepedia = 0;

    int skip = 0;
};

struct BackupData {
    std::string name = "";
    std::string date = "";
    std::string source = "";
    std::string filename = "";
    int type = 0;
};

struct ModAttribs {
    std::string SRmodVersion = "";
    std::string modName = "";
    std::string spoofedName = "";
    bool compatybile = false;
    std::string modType = "";
    int modListType = 0;
};

struct UserData {
    std::string uid = "";
    std::string accountName = "";
    std::string personalName = "";
    bool offlinemode = false;
};

struct SessionData {
    std::string usedLauncherVer = "";
    bool steamRenamed = false;
    std::string gameVersion = "";
    std::string instanceName = "";
    bool debuggingEnabled = false;

    bool loaded = false;
};

struct ManageResult {
    std::string name;
    sf::Texture& iconTx;
    std::string installedModsCount;
    std::string vSavesCount;
    std::string modSavesCount;
    std::string launcherModsCount;
    bool bb_status;
    std::string bb_uid;
};

struct SaveSlotsData {
    std::string nameA;
    std::string nameB;
    std::string nameC;
};

struct modMeta {
    bool hasOnLoad;
    bool hasOnUnload;
    bool conSRML;
};