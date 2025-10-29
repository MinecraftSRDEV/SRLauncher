std::string getVersionFromResources(std::string path);

void asyncGetVersionFromAssets(std::string source)
{
    InstanceDetailsElements::details::versionFromResources.setString(tr("IDS_TEXT_INSTDET_VERRES") + getVersionFromResources(source));
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
        }
    }
}