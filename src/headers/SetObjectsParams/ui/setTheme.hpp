void setTheme()
{
    UIElements.setElementsTheme();

    MainpageElements::GuardBox.setTheme(theme_selected);

    MainpageElements::playbar::downloadingProgress.setTheme(theme_selected);

    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        InstanceIconBar::IconBarMap[pair.first].setTheme(theme_selected);
    }
}