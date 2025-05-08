struct SRVersion {
    std::string version_name;
    bool mod_support;
    std::string release_date;
    std::string manifest;
    std::string version_type;
    int itr;
    std::string executable_hash;
    std::string assembly_hash;
};

struct InstanceModAttributes {
    bool StaysModtool_installed;
    bool SatysModLoader_installed;
    bool UMF_installed;

    std::vector <fs::directory_iterator> StaysModtool_mods_list;
    std::vector <fs::directory_iterator> SatysModLoader_mods_list;
    std::vector <fs::directory_iterator> UMF_mods_list;
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
    std::string version;
    std::string last_played;
    int currency;
    int day;
    int slimepedia;
};

struct BackupData {
    std::string name;
    std::string date;
    std::string source;
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