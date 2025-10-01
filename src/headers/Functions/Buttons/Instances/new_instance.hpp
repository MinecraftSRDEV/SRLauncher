void iconsBarScrollLeft();

void new_instance_change()
{
    UI_current = UiPages::NewInstanceMenu;
    versions_list_ddl.setFromResult("none");
    CreateInstanceUI::graphics_preset_ddl.setFromResult("none");
    CreateInstanceUI::new_instance_name_textbox.setText("");
    CreateInstanceUI::isntance_will_be_created_in_text.setString(tr("IDS_TEXT_NEWINST_WILLBECREATEDIN") + instances_dir);

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
        (tr("IDS_TEXT_NEWINST_INSTNACEINFO") + tr("IDS_TEXT_NEWINST_VERSION") + data.version_name + tr("IDS_TEXT_NEWINST_TYPE") + data.version_type + tr("IDS_TEXT_NEWINST_MANIFEST") + data.manifest + tr("IDS_TEXT_NEWINST_HASH") + data.assembly_hash + tr("IDS_TEXT_NEWINST_RELEASEDATE") + data.release_date);    
    }
    else
    {
        CreateInstanceUI::instance_ver_info_text.setString(tr("IDS_TEXT_NEWINST_INFONODATA"));
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