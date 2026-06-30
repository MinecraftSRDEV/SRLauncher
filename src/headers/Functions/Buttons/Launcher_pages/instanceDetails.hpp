std::string getVersionFromResources(std::string path);

void asyncGetVersionFromAssets(std::string source)
{
    InstanceDetailsElements::details::versionFromResources.setString(tr("IDS_TEXT_INSTDET_VERRES") + getVersionFromResources(source));
}

std::string buildModLoadersString(const InstanceModAttributes& attribs)
{
    std::map <int, std::string> loaders;
    int index = 0;

    if (attribs.StaysModtool_installed == true)
    {
        loaders[index] = "Saty's mod tool";
        index++;
    }
    if (attribs.SatysModLoader_installed == true)
    {
        loaders[index] = "Saty's mod loader";
        index++;
    }
    if (attribs.isBetterBuild04x_installed == true)
    {
        loaders[index] = "NewBetterBuildMod";
        index++;
    }
    if (attribs.UMF_installed == true)
    {
        loaders[index] = "UMF";
        index++;
    }
    if (attribs.SRML_installed == true)
    {
        loaders[index] = "SRML";
        index++;
    }

    if (loaders.empty())
    {
        loaders[index] = "Vanilla";
    }
    
    std::string output;
    size_t size = loaders.size();
    index = 0;

    while (index <= size)
    {
        try
        {
            output += loaders.at(index);
            if ((index + 1) < size)
            {
                output += " | ";
            }
            else
            {
                break;
            }
        }
        catch(std::exception e) {}
        index++;
    }

    return output;
}

namespace instanceDetailsCategory
{
    void back()
    {
        UI_current = UiPages::InstancesMenu;
    }

    void change(std::string id)
    {
        UI_current = UiPages::InstanceDetailsMenu;

        {
            using namespace InstanceDetailsElements;

            instance_list_class &target = instances_list[id];

            head::instanceIcon.setTexture(target.getIconTexture());
            head::instanceNameText.setString(target.getID());

            details::versionText.setString(tr("IDS_TEXT_INSTDET_VER") + target.getVer());

            details::versionFromResources.setString(tr("IDS_TEXT_INSTDET_VERRES") + tr("IDS_TEXT_INSTDET_LOADINGDATA"));
            
            std::thread verGetThread(asyncGetVersionFromAssets, fs::path(instances_path / fs::path("Slime Rancher_" + id)).string() + "/SlimeRancher_Data/resources.assets");
            verGetThread.detach();

            details::instanceLocationText.setString(tr("IDS_TEXT_INSTDET_INSTLOCATION") + "");

            details::modloadersText.setString(tr("IDS_TEXT_INSTDET_MODLOADERS") + buildModLoadersString(target.getModAttributes()));
            
            details::lastPlayedText.setString(tr("IDS_TEXT_INSTDET_LASTPLAYED") + "");

            details::totalPlayTimeText.setString(tr("IDS_TEXT_INSTDET_TOTALPLAYTIME") + target.getPlaytime());

            details::dataLocationText.setString(tr("IDS_TEXT_INSTDET_DATALOCATION") + target.getLocalPath());

            details::savesCountText.setString(tr("IDS_TEXT_INSTDET_SAVESCOUNT") + "");

            details::modsInstalledCountText.setString(tr("IDS_TEXT_INSTDET_INSTALLEDMODS") + "");

            details::isDebugableText.setString(tr("IDS_TEXT_INSTDET_DEBUGABLE") + "");
        }
    }
}