int reloadLauncherBackground()
{
    if (!srlBackgroundPath.empty())
    {
        sf::Image testBgImg;

        if (testBgImg.loadFromFile(srlBackgroundPath))
        {
            bg_texture.loadFromImage(testBgImg);
            background.setTexture(bg_texture);
            return 3;
        }
        else
        {
            log_message(reloadbgdi::ERROR_TEXT + "could not load file", LogTypes::LOG_ERROR);
            return 2;
        }
    }
    else if (srlBackgroundPath == SRL_BG_DEF_PATH)
    {
        SRL_background_img_path_textbox.setText(SRL_BG_DEF_PATH);
        return 4;
    }
    else
    {
        log_message(reloadbgdi::ERROR_TEXT + "invalid file path or path missing", LogTypes::LOG_ERROR);
        return 1;
    }

    SRL_background_img_path_textbox.setText(SRL_BG_DEF_PATH);
    log_message(reloadbgdi::ERROR_TEXT + "ended", LogTypes::LOG_ERROR);
    return 0;
}