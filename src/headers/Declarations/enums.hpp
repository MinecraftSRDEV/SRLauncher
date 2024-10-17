enum UI_PAGES {
    MainMenu,
    InstancesMenu,
    NewInstanceMenu,
    SettingsMenu,
    VersionsList,
    ImportInstanceMenu,
    ManageMenu,
    VersionDescriptionMenu
};

enum SETTIGNS_CATEGORIES {
    MAIN_PAGE,
    PROFILE_PAGE,
    CREDITS_PAGE,
    UPDATES_PAGE
};

enum MANAGE_CATEGORIES {
    MNG_MAIN_PAGE,
    VANILLA_SAVES,
    BETTERBUILD_SAVES,
    BETTERBUILD_WORLDS,
    BACKUPS,
    MODS_PAGE
};

enum LOG_TYPES {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

enum DOWNLOADERS {
    depotdownloader,
    steamcmd
};

enum OfflineModeCheckState {
    result_online,
    result_offline,
    result_fail
};