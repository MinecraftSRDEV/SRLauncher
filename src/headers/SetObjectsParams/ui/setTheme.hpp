void setTheme()
{
    UIElements.setElementsTheme();

    MainpageElements::GuardBox.setTheme(theme_selected);

    MainpageElements::playbar::downloadingProgress.setTheme(theme_selected);

    MainpageElements::playbar::progress_bg.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::inactive]);
    MainpageElements::playbar::progress_moveing.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::checkbox_inactive]);

    InstanceslistElements::utilitiesMenu::body.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::outline]);
    InstanceslistElements::utilitiesMenu::body.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::semitransparrent]);

    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        InstanceIconBar::IconBarMap[pair.first].setTheme(theme_selected);
    }
}