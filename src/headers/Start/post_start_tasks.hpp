void postStartTasks()
{
    if (screen_refresh_count > 2)
    {
        if (run_posttasks == true)
        {
            run_posttasks = false;

            sync_refresh_instances_list();

            miniInstanceList::prepare();
        }
    }
}