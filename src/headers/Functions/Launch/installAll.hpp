void install_all_instances()
{
    
}

std::map <int, std::string> scan_all_instances()    
{
    std::map <int, std::string> queue;
    int itr = 1;

    for (const auto& pair : instances_list)
    {
        if (instances_list[pair.first].getInstalledStatus() == false)
        {
            queue[itr] = instances_list[pair.first].getID(); 
            itr++;
        }
    }
    return queue;
}