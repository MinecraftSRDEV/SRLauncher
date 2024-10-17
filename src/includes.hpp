#include "headers/Declarations/varriables.hpp"
#include "headers/Declarations/enums.hpp"
#include "headers/Declarations/structs.hpp"
#include "headers/Declarations/maps.hpp"

#include "headers/Classes/json_parser.hpp"
#include "headers/Classes/json_encoder.hpp"
#include "headers/Classes/md5calculator.hpp"
#include "headers/Classes/VDF_parser.hpp"

#include "headers/Functions/Logs/log_message.hpp"

#include "headers/Classes/popup_message_window.hpp"
#include "headers/Classes/instance_list.hpp"
#include "headers/Classes/version_class.hpp"
#include "headers/Classes/save_menagement/betterbuild_save.hpp"
#include "headers/Classes/save_menagement/mod_class.hpp"
#include "headers/Classes/save_menagement/game_save_class.hpp"

// #include "headers/Classes/formattedText.hpp"

#include "headers/Classes/steamGuardAuthClass.hpp"

#include "headers/Declarations/SFMLObjects/objects.hpp"
#include "headers/Declarations/SFMLObjects/ui/elements.hpp"

#include "headers/Declarations/namespaces.hpp"

#include "headers/Start/create_versions_list.hpp"
#include "headers/Start/objects_attributes.hpp"
#include "headers/Start/run_date.hpp"

#include "headers/Functions/Logs/save_log_file.hpp"
#include "headers/Functions/window/close.hpp"

#include "headers/Functions/Userdata/white_space_remover.hpp"

#include "headers/Functions/Data_menagement/move_directory.hpp"
#include "headers/Functions/Data_menagement/directory_check.hpp"
#include "headers/Functions/Data_menagement/rename_slime_rancher_dir.hpp"

#include "headers/Functions/Data_menagement/browse_folder_dialogbox.hpp"
#include "headers/Functions/Data_menagement/get_folders.hpp"

#include "headers/Functions/window/create.hpp"

#include "headers/Functions/Animations/downloading.hpp"

#include "headers/Functions/Userdata/slash_remover.hpp"

#include "headers/ResourceLoad/loadElements.hpp"
#include "headers/ResourceLoad/loadJsons.hpp"

#include "headers/Functions/crypt/decryptor.hpp"
#include "headers/Functions/crypt/encryptor.hpp"

#include "headers/Functions/Config/update_file.hpp"
#include "headers/Functions/Userdata/textbox_data.hpp"

#include "headers/SetObjectsParams/textures/setTextures.hpp"
#include "headers/SetObjectsParams/ui/setButtons.hpp"
#include "headers/SetObjectsParams/ui/setTheme.hpp"

#include "headers/Functions/Userdata/get_userdata_path.hpp"
#include "headers/Functions/Userdata/get_steam_default_path.hpp"

#include "headers/Functions/Userdata/get_steam_profile.hpp"

#include "headers/Start/construct_paths.hpp"

#include "headers/Functions/Settings/lock/lock.hpp"
#include "headers/Functions/Settings/lock/unlock.hpp"

#include "headers/Functions/Settings/defaults/dafault_paths.hpp"
#include "headers/Functions/Settings/defaults/default_checkboxes.hpp"

#include "headers/Functions/Settings/defaults/reset_function.hpp"

#include "headers/Functions/Buttons/Settings/subcats.hpp"

#include "headers/Functions/Data_menagement/SteamCMDCheck.hpp"

#include "headers/Functions/Buttons/Launcher_pages/categories.hpp"
#include "headers/Functions/Buttons/Instances/import.hpp"
#include "headers/Functions/Buttons/Instances/new_instance.hpp"
#include "headers/Functions/Buttons/Instances/refresh_list.hpp"
#include "headers/Functions/Buttons/Instances/create.hpp"

#include "headers/Functions/Buttons/Instances/manage.hpp"

#include "headers/Functions/Buttons/Instances/downloadCMD.hpp"

#include "headers/Events/loop.hpp"

#include "headers/Functions/Buttons/Instances/unmount.hpp"
#include "headers/Functions/Buttons/Instances/mount.hpp"
#include "headers/Functions/Buttons/Instances/edit.hpp"
#include "headers/Functions/Buttons/Instances/open_folder.hpp"
#include "headers/Functions/Buttons/Instances/remove.hpp"

#include "headers/Start/runtime.hpp"

#include "headers/Functions/mouse/left.hpp"

#include "headers/Functions/Launch/download_game.hpp"
#include "headers/Functions/Launch/run_game.hpp"

#include "headers/Functions/window/draw.hpp"
#include "headers/Functions/window/display.hpp"

#include "headers/Functions/updates/launcher_update_check.hpp"

#include "headers/SetObjectsParams/buttons/setFunctions.hpp"