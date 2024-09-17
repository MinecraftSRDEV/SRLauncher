void new_instance_change()
{
    UI_current = UI_PAGES::NewInstanceMenu;
    versions_list.setFromResult("none");
}

void import_instance_change()
{
    if (getfolder_import_instance() == true)
    {
        UI_current = UI_PAGES::ImportInstanceMenu;
        versions_list.setFromResult("none");    
    }
}

void cancel_instance_creation()
{
    UI_current = UI_PAGES::InstancesMenu;
}

void cancel_instance_import()
{
    UI_current = UI_PAGES::InstancesMenu;
}