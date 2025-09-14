void updateDetailsTexts(std::string lastPlayed, Playtime playtime)
{
    try
    {
        lastPlayedText.setString("Last played date: " + lastPlayed);
        totalPlayTimeInstanceText.setString("Total playtime\n" + std::to_string(playtime.hours) + "H " + std::to_string(playtime.minutes) + "M " + std::to_string(playtime.seconds) + "S " + std::to_string(playtime.miliseconds) + "Ms"); 
    }
    catch(std::exception e) {}
}

void totalPlayTimeCalc()
{
    std::string newTime = "";
    sf::Int64 timeCalc = 0;
    Playtime totalTime;

    if (instances_list.size() > 0)
    {
        for (const auto& pair : instances_list)
        {
            try
            {
                sf::Int64 total = timeCalc + std::stoll(instances_list[pair.first].getPlaytime());
                timeCalc = total;
            }
            catch(const std::exception& e){}
        }    
    }

    totalTime = calcPlaytime(timeCalc);

    totalLauncherPlaytimeText.setString("Total playtime\n" + std::to_string(totalTime.hours) + "H " + std::to_string(totalTime.minutes) + "M " + std::to_string(totalTime.seconds) + "S " + std::to_string(totalTime.miliseconds) + "Ms");     
}

void mouseContains()
{
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (UI_current == UiPages::MainMenu)
    {
        if (!miniInstanceList::dataLoading)
        {
            if (miniInstancesListMap.size() > 0)
            {
                for (const auto& itr : miniInstancesListMap)
                {
                    if (miniInstancesListMap[itr.first].getHitbox().contains(mouse))
                    {
                        // miniInstancesListMap[itr.first].hilight(true);
                        updateDetailsTexts(miniInstancesListMap[itr.first].getLastPlayed(), miniInstancesListMap[itr.first].getTime());
                        miniInstanceList::instanceHilighted = true;
                        break;
                    }
                    else
                    {
                        // miniInstancesListMap[itr.first].hilight(false);
                        miniInstanceList::instanceHilighted = false;
                    }
                }
            }
        }
    }
}