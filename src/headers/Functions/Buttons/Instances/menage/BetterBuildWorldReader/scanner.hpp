void noFunction()
{
    MessageBoxA(NULL, "Function not implemated yet", "info", MB_ICONINFORMATION | MB_OK);
}

/**
 * Universal BetterBuild words scanner function.
 * This function automatically create list of custom worlds.
 * 
 * @param bbw_dir BetterBuild worlds directory path.
 * @param reader_mode selected reader 0 = old, 1 = new. 
 */
void scanBetterBuildWorlds(const fs::path& bbw_dir, int reader_mode)
{
    int last_bbsave_entry_y = 5;
    int iteration = 0;
    betterbuildworlds_list.clear();

    for (const auto& entry : fs::directory_iterator(bbw_dir))
    {
        if (entry.is_regular_file() and entry.path().filename().extension() == ".world")
        {
            std::string output = entry.path().string();

            WorldData worldData = LoadWorld(output);

            worldData.levelname = entry.path().filename().replace_extension().string();

            betterbuildworlds_list[iteration].create(130, last_bbsave_entry_y, worldData, font);
            betterbuildworlds_list[iteration].transportFunction(noFunction, backupWorldAsk);
            last_bbsave_entry_y += 120;
            iteration++;
        }
    }
}