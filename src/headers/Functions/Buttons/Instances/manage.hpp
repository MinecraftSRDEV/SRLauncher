void instance_manage(std::string instance_id)
{
    if (mounted_instance == instances_list[instance_id].getID())
    {
        MessageBoxA(NULL, "Unmount this instance first!", "Error", MB_ICONERROR | MB_OK);
    }
    else
    {
        fs::path instance_directory = instances_dir / fs::path("Slime Rancher_" + instances_list[instance_id].getID());

        InstanceModAttributes attribs = instances_list[instance_id].getModAttributes();

        fs::path instance_mods_directory;

        if (versions_map[instances_list[instance_id].getVer()].mod_support == true)
        {
            if (versions_map[instances_list[instance_id].getVer()].version_type == "pre-release")
            {
                instance_mods_directory = instance_directory / "mods";

                try
                {
                    for (const auto& entry : fs::directory_iterator(instance_mods_directory))
                    {
                        if (entry.is_regular_file() and entry.path().filename().extension() == ".dll")
                        {
                            std::string output = entry.path().filename().replace_extension().string();
                            log_message(output, LOG_TYPES::LOG_INFO);
                        }
                    }    
                }
                catch (fs::filesystem_error e)
                {

                }
            }    
        }
    }
}