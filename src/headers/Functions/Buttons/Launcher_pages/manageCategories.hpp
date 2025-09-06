namespace manageCategories
{
    void exit_function()
    {
        UI_current = UiPages::InstancesMenu;
        selected_instance.erase();
        refresh_instances_list();
    }

    void bbworls()
    {
        manage_ui = BETTERBUILD_WORLDS;
    }

    void vanilla()
    {
        manage_ui = VANILLA_SAVES;
    }

    void bbsaves()
    {
        manage_ui = BETTERBUILD_SAVES;
    }

    void mods()
    {
        manage_ui = MODS_PAGE;
    }

    void backups()
    {
        manage_ui = BACKUPS;
    }
}

