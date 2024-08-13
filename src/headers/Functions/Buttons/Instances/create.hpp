void create_instance()
{
    std::string instance_name = new_instance_name_textbox.getText();
    std::string version_selected = versions_list.getResult();
    if (!instance_name.empty())
    {
        // fs::path new_instance_path = defaultDir / "instances" / instance_name;
        std::string instances_dir = SlimeRancher_instances_path_textbox.getText();
        // fs::path steam_dir = steam_game_dir;
        fs::path steam_dir = instances_dir;
        fs::path new_instance_path = steam_dir / ("Slime Rancher_" + instance_name);
        if (fs::exists(new_instance_path) && fs::is_directory(new_instance_path))
        {
            //popup error here
        }
        else
        {
            if (version_selected != "none")
            {
                fs::create_directory(new_instance_path);

                JSONEncoder::JSONObject obj;

                obj.add("name", new JSONEncoder::JSONString(instance_name));
                obj.add("version", new JSONEncoder::JSONString(version_selected));

                std::string jsonConfig =  obj.stringify();
                std::ofstream configfile;
                configfile.open(new_instance_path / "info.json");
                configfile << jsonConfig;
                configfile.close();

                UI_current = UI_PAGES::InstancesMenu;
                refresh_instances_list();
            }
            else
            {
                //popup error here
            }
        }  
    }
    else
    {
        //popup error here
    }   
}