std::map <std::string, SRVersion> versionsData_map;

class instance_list_class;
class BetterBuildSave;
class VanillaSave;
class versionClass;
class ModClass;
class BackupList;
class InstanceIconBarOption;
std::map <std::string, instance_list_class> instances_list;
std::map <int, std::string> instances_list_iterations;
std::map <int, BetterBuildSave> betterbuildworlds_list;
std::map <int, VanillaSave> vanillasaves_list;
std::map <int, VanillaSave> betterbuildsaves_list;
std::map <int, versionClass> versions_pachnotes_list;
std::map <int, BackupList> Backups_list;
std::map <std::string, ModClass> LauncherMods_list;
std::map <std::string, ModClass> InstanceMods_list;

std::vector <ModAttribs> mods_folder_data_list;
std::vector <ModAttribs> instance_mods_folder_list;

uiElements UIElements;

namespace InstanceIconBar
{
    std::map <std::string, InstanceIconBarOption> IconBarMap;
}