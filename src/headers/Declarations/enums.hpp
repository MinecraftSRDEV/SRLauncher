enum UiPages {
    MainMenu,
    InstancesMenu,
    NewInstanceMenu,
    SettingsMenu,
    VersionsList,
    ImportInstanceMenu,
    ManageMenu,
    VersionDescriptionMenu,
    EditInstanceMenu,
    InstanceDetailsMenu
};

enum SettingsCategories {
    MAIN_PAGE,
    PROFILE_PAGE,
    DOWNLOADING_PAGE,
    UPDATES_PAGE,
    DEBUGGING_PAGE,
    CREDITS_PAGE,
    LICENCES_PAGE
};

enum ManageCategories {
    MNG_MAIN_PAGE,
    VANILLA_SAVES,
    BETTERBUILD_SAVES,
    BETTERBUILD_WORLDS,
    BACKUPS,
    MODS_PAGE,
    DEBUG_PAGE,
    BETTERBUILDWORLDS_SAVESLOTS,
};

enum LogTypes {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_EXCEPTION,
};

enum Downloaders {
    depotdownloader,
    steamcmd
};

enum SaveTypes {
    vanilla_save_backup,
    betterbuild_save_backup
};

enum OfflineModeCheckState {
    result_online,
    result_offline,
    result_fail
};

enum ModLoaders {
    SMT_ld,
    SML_ld,
    SRML_ld,
    UMF_ld,
    UNKNOWN_ld
};

enum BbReaderMode {
    old_loader,
    new_loader,
    vanilla_loader
};

enum BackupTypes {
    BBworld_backup,
    Vanillaworld_backup,
    BBsave_backup,
    fullgame_backup
};