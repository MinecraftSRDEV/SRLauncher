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
        manage_ui = ManageCategories::BETTERBUILD_WORLDS;
    }

    void vanilla()
    {
        manage_ui = ManageCategories::VANILLA_SAVES;
    }

    void bbsaves()
    {
        manage_ui = ManageCategories::BETTERBUILD_SAVES;
    }

    void mods()
    {
        manage_ui = ManageCategories::MODS_PAGE;
    }

    void backups()
    {
        manage_ui = ManageCategories::BACKUPS;
    }

    void debug()
    {
        manage_ui = ManageCategories::DEBUG_PAGE;
    }

    void details()
    {
        manage_ui = ManageCategories::MNG_MAIN_PAGE;
    }
}

