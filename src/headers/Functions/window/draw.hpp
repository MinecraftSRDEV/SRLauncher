void renderCategories()
{
    categories_bg.render(window);
    MainCategory_button.render(window);
    InstancesCategory_button.render(window);
    SettingsCategory_button.render(window);
    SavesToolCategory_button.render(window);
}

void window_draw()
{
    window.draw(background);
    
    if (UI_current == UI_PAGES::MainMenu)
    {
        renderCategories();

        last_played_bg.render(window);
        launch_last_instance_button.render(window);

        if (game_downloading == true)
        {
            window.draw(progress_bg);
            window.draw(progress_moveing);
        }

        window.draw(Mounted_instance_info_text);
        window.draw(Launcher_version_text);
    }

    if (UI_current == UI_PAGES::InstancesMenu)
    {
        renderCategories();

        instances_bg.render(window);
        new_instance_button.render(window);

        for (const auto& pair : instances_list)
        {
            instances_list[pair.first].render(window);
        }
    }

    if (UI_current == UI_PAGES::NewInstanceMenu)
    {
        new_instance_name_textbox.render(window);
        versions_list.render(window); 
        create_button.render(window); 
        instance_creation_cancel.render(window); 
    }

    if (UI_current == UI_PAGES::SettingsMenu)
    {
        renderCategories();
        
        settings_bg.render(window);
        Subcat_settings_main_button.render(window);
        Subcat_settings_progile_button.render(window);

        if (options_ui == SETTIGNS_CATEGORIES::MAIN_PAGE)
        {
            SlimeRancher_steam_path_textbox.render(window);
            SlimeRancher_instances_path_textbox.render(window);

            SaveConfig_button.render(window);
        }
        if (options_ui == SETTIGNS_CATEGORIES::PROFILE_PAGE)
        {
            SteamProfile_name_textbox.render(window);
            SteamProfile_password_textbox.render(window);
            save_profile_button.render(window);
            login_manualy_checkbox.render(window);
        }
    }

    if (UI_current == UI_PAGES::DataToolsMenu)
    {
        renderCategories();

        datatools_bg.render(window);
    }
}