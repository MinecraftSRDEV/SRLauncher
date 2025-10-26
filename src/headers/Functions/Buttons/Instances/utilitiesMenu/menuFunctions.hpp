void runQueueDownloading();

namespace instUtilitiesFunctions
{
    void refreshList()
    {
        instUtilitiesMenu::hideMenuInsantly();
        refresh_instances_list();
    }

    void backToInstancesList()
    {
        selectionListMap.clear();
        UI_current = UiPages::InstancesMenu;
    }

    void confirmSelectionAndInstallInstances()
    {
        int result = MessageBoxA(NULL, tr("IDS_MSG_CONFIRMINSTALLALL").c_str(), "Warning", MB_ICONWARNING | MB_YESNO);
        if (result == IDYES)
        {
            UI_current = UiPages::DownloadingQueueMenu;
            autoDownloadLoopProcessing = true;
            std::thread downloadingThread(runQueueDownloading);
            downloadingThread.detach();
        }
        else
        {
            backToInstancesList();
        }
    }
    
    int howMuchSelectedInstances()
    {
        int out = 0;
        for (const auto& pair : selectionListMap)
        {
            if (selectionListMap[pair.first].selectChkbox.getState())
            {
                out++;
            }
        }

        return out;
    }
    
    void listSelectionCheckstate()
    {
        if (howMuchSelectedInstances() == selectionListMap.size())
        {
            InstanceslistElements::selectionList::bottom::confirm.setBlockState(false);
            InstanceslistElements::selectionList::body::selectAllCheckbox.setState(true);
            return;
        }
        else if (howMuchSelectedInstances() > 0)
        {
            InstanceslistElements::selectionList::bottom::confirm.setBlockState(false);
            InstanceslistElements::selectionList::body::selectAllCheckbox.setState(false);

        }
        else if (howMuchSelectedInstances() == 0)
        {
            InstanceslistElements::selectionList::bottom::confirm.setBlockState(true);
            InstanceslistElements::selectionList::body::selectAllCheckbox.setState(false);
            return;
        }
    }

    void listSelectionAll()
    {
        for (const auto& pair : selectionListMap)
        {
            selectionListMap[pair.first].selectChkbox.setState(InstanceslistElements::selectionList::body::selectAllCheckbox.getState());
        }
        listSelectionCheckstate();
    }

    void downloadAll()
    {
        instUtilitiesMenu::hideMenuInsantly();
        UI_current = UiPages::SelectionMenu;
        // apply instances informations from map to submap, and create List with checkboxes

        selectionListMap.clear();
        int iteration = 0;
        int lastY = 115;

        InstanceslistElements::selectionList::head::headerText.setPosition(((1280 / 2) - (InstanceslistElements::selectionList::head::headerText.getLocalBounds().width / 2)), 5);
        InstanceslistElements::selectionList::bottom::confirm.setBlockState(true);

        for(const auto& pair : instances_list)
        {
            if (instances_list[pair.first].getInstalledStatus() == false)
            {
                selectionListMap[iteration].create(60, lastY, 1160, 60, iteration, instances_list[pair.first].getID(), instances_list[pair.first].getVer(), instances_list[pair.first].getIconTexture(), font);
                selectionListMap[iteration].selectChkbox.setState(true);
                selectionListMap[iteration].selectChkbox.setFunction(listSelectionCheckstate);
                iteration++;
                lastY += 62;
            }
        }

        if (selectionListMap.size() > 0)
        {
            InstanceslistElements::selectionList::body::selectAllCheckbox.setBlockState(false);
            InstanceslistElements::selectionList::body::selectAllCheckbox.setFunction(listSelectionAll);
            InstanceslistElements::selectionList::body::selectAllCheckbox.setState(true);
            InstanceslistElements::selectionList::bottom::confirm.setBlockState(false);
        }
        else
        {
            InstanceslistElements::selectionList::body::noInstancesText.setPosition(((1280 / 2) - (InstanceslistElements::selectionList::body::noInstancesText.getLocalBounds().width / 2)), 300);
            InstanceslistElements::selectionList::body::selectAllCheckbox.setState(false);
            InstanceslistElements::selectionList::body::selectAllCheckbox.setBlockState(true);
        }
    }

    void goToSettings()
    {
        instUtilitiesMenu::hideMenuInsantly();
        launcherCategories::settings();
    }
}