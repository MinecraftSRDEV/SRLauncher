/**
 * Scanning mods folder in launcher directory and building mods list.
 */
int loadLauncherMods(const std::string& selected_instance_id)
{
    LauncherMods_list.clear();
    try
    {
        int last_mod_ir_pos = 20;
        int last_mod_index = 0;

        scanModsFolder(SMTFolder_path, ".dll", last_mod_ir_pos, selected_instance_id, SMT_ld, LauncherMods_list, mods_folder_data_list, 700, LauncherModsIndexing, last_mod_index);
        scanModsFolder(SMLFolder_path, ".dll", last_mod_ir_pos, selected_instance_id, SML_ld, LauncherMods_list, mods_folder_data_list, 700, LauncherModsIndexing, last_mod_index);
        scanModsFolder(SRMLmodsFolder_path, ".dll", last_mod_ir_pos, selected_instance_id, SRML_ld, LauncherMods_list, mods_folder_data_list, 700, LauncherModsIndexing, last_mod_index);
        scanModsFolder(UMFmodsFolder_path, ".umfmod", last_mod_ir_pos, selected_instance_id, UMF_ld, LauncherMods_list, mods_folder_data_list, 700, LauncherModsIndexing, last_mod_index);
        return 1;
    }
    catch (fs::filesystem_error e){}
    return 0;
}