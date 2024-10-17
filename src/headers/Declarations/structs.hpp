struct SRVersionChangelog {
    std::string deskription;
    std::string changes;
    std::string fixes;
    std::string image_link;
};

struct SRVersion {
    std::string version_name;
    bool mod_support;
    std::string release_date;
    std::string manifest;
    std::string version_type;
    int itr;
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