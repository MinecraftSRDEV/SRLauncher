void iconsBarScrollLeft();

void new_instance_change()
{
    UI_current = UiPages::NewInstanceMenu;
    versions_list_ddl.setFromResult("none");
    CreateInstanceUI::graphics_preset_ddl.setFromResult("none");
    CreateInstanceUI::new_instance_name_textbox.setText("");
    CreateInstanceUI::isntance_will_be_created_in_text.setString("Will be created in:\n" + instances_dir);

    iconBarScrollWhile("pink");
}

void updateInstanceInfo()
{
    std::string id = versions_list_ddl.getResult();

    SRVersion data;

    data = versionsData_map[id];

    if (!id.empty())
    {
        CreateInstanceUI::instance_ver_info_text.setString
        ("Instance info\n\nVersion: " + data.version_name + "\n\nType: " + data.version_type + "\n\nManifest:\n" + data.manifest + "\n\nHash:\n" + data.assembly_hash + "\n\nMod support: " + std::to_string(data.mod_support) + "\n\nRelease date:\n" + data.release_date);    
    }
    else
    {
        CreateInstanceUI::instance_ver_info_text.setString("Instance info\n\nNo data");
    }
}

void import_instance_change()
{
    if (getfolder_import_instance() == true)
    {
        UI_current = UiPages::ImportInstanceMenu;
        versions_list_ddl.setFromResult("none");    
    }
}

void cancel_instance_creation()
{
    UI_current = UiPages::InstancesMenu;
}

void cancel_instance_import()
{
    UI_current = UiPages::InstancesMenu;
}