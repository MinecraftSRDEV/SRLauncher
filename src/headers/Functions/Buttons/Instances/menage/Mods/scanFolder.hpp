/**
 * Scanning specyfic folder for mods and adds to list
 * 
 * @param folder_path selected folder path
 * @param mod_file_ex mod file extension like: .dll
 * @param mod_list_itr Y position on mods list
 * @param selected_instance_id pointer to instance
 * @param mod_loader mod loader id 0 = SMT, 1 = SML, 2 = SRML, 3 = UMF
 * @param mods_list pointer to all mods list
 * @param attribs pointer to mods counter
 */
void scanModsFolder(const fs::path& folder_path, const std::string& mod_file_ex, int& mod_list_itr, const std::string& selected_instance_id, int mod_loader, std::map <std::string, ModClass>& mods_list, std::vector <ModAttribs>& attribs, int Xposition)
{
    for (const auto& entry : fs::directory_iterator(folder_path))
    {
        fs::path folderPath = folder_path / entry.path();
        if (fs::is_directory(folderPath))
        {
            for (const auto& modEntry : fs::directory_iterator(folderPath))
            {
                if (modEntry.is_regular_file() and modEntry.path().filename().extension() == mod_file_ex)
                {
                    mod_list_itr += add_mod_to_list(mod_list_itr, modEntry, folderPath, mod_loader, selected_instance_id, mods_list, attribs, Xposition);
                }
            }
        }
        else if (entry.is_regular_file() and entry.path().filename().extension() == mod_file_ex)
        {
            mod_list_itr += add_mod_to_list(mod_list_itr, entry, folderPath, mod_loader, selected_instance_id, mods_list, attribs, Xposition);
        }
    }
}