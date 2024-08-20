struct SRVersion {
    std::string version_name;
    bool mod_support;
    std::string release_date;
    std::string manifest;
    std::string version_type;
};

struct InstanceModAttributes {
    bool StaysModtool_installed;
    bool SatysModLoader_installed;
    bool UMF_installed;

    std::vector <fs::directory_iterator> StaysModtool_mods_list;
    std::vector <fs::directory_iterator> SatysModLoader_mods_list;
    std::vector <fs::directory_iterator> UMF_mods_list;
};