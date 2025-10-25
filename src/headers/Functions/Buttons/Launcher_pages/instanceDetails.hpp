namespace instanceDetailsCategory
{
    void back()
    {
        UI_current = UiPages::InstancesMenu;
    }

    void change(std::string id)
    {
        UI_current = UiPages::InstanceDetailsMenu;
    }
}