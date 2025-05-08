void setTheme()
{
    UIElements.setElementsTheme();

    GuardBox.setTheme(theme_selected);

    downloadingProgress.setTheme(theme_selected);

    for (const auto& pair : InstanceIconBar::IconBarMap)
    {
        InstanceIconBar::IconBarMap[pair.first].setTheme(theme_selected);
    }
}