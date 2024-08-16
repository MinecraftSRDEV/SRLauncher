void instances_stat_refresh()
{
    for(const auto& pair : instances_list)
    {
        if (mounted_instance == pair.first)
        {
            instances_list[pair.first].updateStatus(instance_list_class::status::Mounted);
        }
        else
        {
            instances_list[pair.first].updateStatus(instance_list_class::status::Unmounted);
        }
    }
}

void refresh_instances_list()
{
    instances_list.clear();
    int last_entry_y = 85;

    fs::path instances_path = instances_dir;

    std::ifstream getdata;
    fs::path path = fs::path(steam_game_dir) / "Slime Rancher";
    std::string path_str = path.string();
    getdata.open(path_str + "/info.json");
    if (getdata)
    {
        JSON json = JSON::parseFromFile(path_str + "/info.json");

        std::string name = json.getObject().at("name").getString();
        std::string version = json.getObject().at("version").getString();

        instances_list[name].create(10, last_entry_y, 1260, 80, name, version, font);
        last_entry_y += 85;
    }
    else
    {
        //popup warning here
    }
    getdata.close();

    for (const auto& entry : fs::directory_iterator(instances_path))
    {
        std::ifstream getdata;
        fs::path path = instances_path / entry.path();
        std::string path_str = path.string();
        getdata.open(path_str + "/info.json");
        if (getdata)
        {
            JSON json = JSON::parseFromFile(path_str + "/info.json");

            std::string name = json.getObject().at("name").getString();
            std::string version = json.getObject().at("version").getString();

            instances_list[name].create(10, last_entry_y, 1260, 80, name, version, font);
            last_entry_y += 85;
        }
        getdata.close();
    }


    instances_stat_refresh();
}