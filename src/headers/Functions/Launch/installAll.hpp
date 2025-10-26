void download_game(std::string gamerun_path);

void runQueueDownloading()
{
    if (downloader_selected == steamcmd)
    {
        autoDownloadLoopProcessing = false;
    }
    else
    {
        std::vector <std::string> queue;

        queue.clear();

        for (const auto& pair : selectionListMap)
        {
            if (selectionListMap[pair.first].selectChkbox.getState())
            {
                queue.emplace_back(selectionListMap[pair.first].attributes.name);
            }
        }

        for (const auto& itr : queue)
        {
            mount_function(itr);

            gameDownloadFinished = false;
            isAutoDownloadnig = true;

            fs::path steam_dir = steam_game_dir;
            fs::path game_dir = steam_dir / "Slime Rancher";
            std::string gamepath = game_dir.string();
            std::string gamerun_path = gamepath + "/SlimeRancher.exe";

            std::thread downloadThread(download_game, gamerun_path);
            downloadThread.detach();
            while(true)
            {
                if (gameDownloadFinished)
                {
                    break;
                }
                sf::sleep(sf::seconds(0.5));
            }
        }
        autoDownloadLoopProcessing = false;
    }
}