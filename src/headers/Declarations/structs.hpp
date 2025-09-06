struct SRGamesaveInfo {
    bool readable_version;
    int format;
    bool single_file;
};

struct SRVersion {
    std::string version_name;
    std::string release_date;
    std::string manifest;
    std::string version_type;
    int itr;
    std::string executable_hash;
    std::string assembly_hash;
    SRGamesaveInfo savegame_info;
    std::string debugCompatybile;
};

struct InstanceModAttributes {
    bool isModded;

    bool StaysModtool_installed;
    bool SatysModLoader_installed;
    bool isBetterBuild04x_installed;
    bool SRML_installed;
    bool UMF_installed;

    std::vector <fs::directory_iterator> StaysModtool_mods_list;
    std::vector <fs::directory_iterator> SatysModLoader_mods_list;
    std::vector <fs::directory_iterator> UMF_mods_list;
    std::vector <fs::directory_iterator> SRML_mods_list;
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
    std::string name;
    std::string displayedText;
    std::string version;
    std::string last_played;
    int currency;
    int day;
    int slimepedia;

    int skip;
};

struct BackupData {
    std::string name;
    std::string date;
    std::string source;
    std::string filename;
    int type;
};

struct ModAttribs {
    std::string SRmodVersion;
    std::string modName;
    bool compatybile;
    std::string modType;
};

struct UserData {
    std::string uid;
    std::string accountName;
    std::string personalName;
    bool offlinemode;
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