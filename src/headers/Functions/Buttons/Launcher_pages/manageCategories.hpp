void exit_manage_function()
{
    UI_current = UiPages::InstancesMenu;
    selected_instance.erase();
    refresh_instances_list();
}

void changeCategory_mng_bbworls()
{
    manage_ui = BETTERBUILD_WORLDS;
}

void changeCategory_mng_vanilla()
{
    manage_ui = VANILLA_SAVES;
}

void changeCategory_mng_bbsaves()
{
    manage_ui = BETTERBUILD_SAVES;
}

void changeCategory_mng_mods()
{
    manage_ui = MODS_PAGE;
}

void changeCategory_mng_backups()
{
    manage_ui = BACKUPS;
}