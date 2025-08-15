#include "headers/Functions/CriticalErrorsDetection/errorDetection.hpp"

#include "headers/Declarations/varriables.hpp"
#include "headers/Declarations/dictionaries.hpp"
#include "headers/Declarations/enums.hpp"
#include "headers/Declarations/structs.hpp"

#include "headers/Classes/save_menagement/management_main_class.hpp"

#include "headers/Classes/uiElements_class.hpp"

#include "headers/Declarations/maps.hpp"

#include "headers/Classes/json_parser.hpp"
#include "headers/Classes/json_encoder.hpp"
#include "headers/Classes/md5calculator.hpp"
#include "headers/Classes/VDF_parser.hpp"
#include "headers/Classes/downloadingProgressBar.hpp"

#include "headers/Functions/crypt/md5calc.hpp"

#include "headers/Functions/Logs/log_message.hpp"

#include "headers/Functions/Buttons/Instances/playtimeCalculator.hpp"

#include "headers/Classes/dev_ui_viewer.hpp"

#include "headers/Classes/instance_list.hpp"
#include "headers/Classes/version_class.hpp"
#include "headers/Classes/instance_icon_bar_options.hpp"
#include "headers/Classes/save_menagement/betterbuild_save.hpp"
#include "headers/Classes/save_menagement/mod_class.hpp"
#include "headers/Classes/save_menagement/game_save_class.hpp"
#include "headers/Classes/save_menagement/backup_list_class.hpp"

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

#include "headers/SetObjectsParams/buttons/asyncCangeProtection.hpp"

#include "headers/Functions/Data_menagement/move_directory.hpp"
#include "headers/Functions/Data_menagement/directory_check.hpp"
#include "headers/Functions/Data_menagement/rename_slime_rancher_dir.hpp"

#include "headers/ResourceLoad/reloadBackground.hpp"

#include "headers/Functions/Data_menagement/browse_folder_dialogbox.hpp"
#include "headers/Functions/Data_menagement/get_folders.hpp"

#include "headers/Functions/window/create.hpp"

#include "headers/Functions/Animations/downloading.hpp"

#include "headers/Functions/Userdata/slash_remover.hpp"

#include "headers/Functions/Settings/defaults/default_functions.hpp"

#include "headers/ResourceLoad/loadElements.hpp"
#include "headers/ResourceLoad/loadPatchNotes.hpp"
#include "headers/ResourceLoad/loadJsons.hpp"
#include "headers/ResourceLoad/loadLicences.hpp"

#include "headers/Functions/Launch/steamworksBypass.hpp"

#include "headers/Functions/crypt/decryptor.hpp"
#include "headers/Functions/crypt/encryptor.hpp"

#include "headers/Functions/Data_menagement/file_editor.hpp"

#include "headers/Functions/Config/update_file.hpp"
#include "headers/Functions/Userdata/settingsValues.hpp"

#include "headers/SetObjectsParams/textures/setTextures.hpp"
#include "headers/SetObjectsParams/ui/setUiElements.hpp"
#include "headers/SetObjectsParams/ui/setTheme.hpp"

#include "headers/Functions/Userdata/get_userdata_path.hpp"
#include "headers/Functions/Userdata/get_steam_default_path.hpp"

#include "headers/Functions/Userdata/get_steam_profile.hpp"

#include "headers/Start/construct_paths.hpp"

#include "headers/Functions/Settings/lock/lock.hpp"
#include "headers/Functions/Settings/lock/unlock.hpp"

#include "headers/Functions/Settings/defaults/allSettings.hpp"

#include "headers/Functions/Settings/defaults/reset_function.hpp"

#include "headers/Functions/Buttons/Settings/subcats.hpp"

#include "headers/Functions/Data_menagement/SteamCMDCheck.hpp"

#include "headers/Functions/Buttons/Instances/iconbar.hpp"

#include "headers/Functions/Buttons/Launcher_pages/categories.hpp"
#include "headers/Functions/Buttons/Launcher_pages/manageCategories.hpp"
#include "headers/Functions/Buttons/Instances/import.hpp"
#include "headers/Functions/Buttons/Instances/new_instance.hpp"
#include "headers/Functions/Buttons/Instances/refresh_list.hpp"
#include "headers/Functions/Buttons/Instances/create.hpp"

#include "headers/Functions/Buttons/Instances/menage/vanillaSavesDeserializer/dateFromat.hpp"
#include "headers/Functions/Buttons/Instances/menage/backups/makeBackupAsk.hpp"
#include "headers/Functions/Buttons/Instances/menage/backups/backupRemove.hpp"
#include "headers/Functions/Buttons/Instances/menage/backups/backupRestore.hpp"
#include "headers/Functions/Buttons/Instances/menage/backups/backupReveal.hpp"
#include "headers/Functions/Buttons/Instances/menage/backups/bcScanner.hpp"
#include "headers/Functions/Buttons/Instances/menage/BetterBuildWorldReader/binaryReader.hpp"
#include "headers/Functions/Buttons/Instances/menage/BetterBuildWorldReader/unlocker.hpp"
#include "headers/Functions/Buttons/Instances/menage/BetterBuildWorldReader/BBWremover.hpp"
#include "headers/Functions/Buttons/Instances/menage/BetterBuildWorldReader/scanner.hpp"
#include "headers/Functions/Buttons/Instances/menage/mainpage/detailsText.hpp"
#include "headers/Functions/Buttons/Instances/menage/vanillaSavesDeserializer/deserializer.hpp"
#include "headers/Functions/Buttons/Instances/menage/saveScaner/vanilla.hpp"
#include "headers/Functions/Buttons/Instances/menage/saveScaner/modded.hpp"
#include "headers/Functions/Buttons/Instances/menage/saveScaner/autoSelector.hpp"
#include "headers/Functions/Buttons/Instances/menage/Mods/findSpecyficMod.hpp"
#include "headers/Functions/Buttons/Instances/menage/Mods/recognizer.hpp"
#include "headers/Functions/Buttons/Instances/menage/Mods/scanFolder.hpp"
#include "headers/Functions/Buttons/Instances/menage/Mods/loadModsFolder.hpp"
#include "headers/Functions/Buttons/Instances/menage/Mods/betterBuildChecker.hpp"
#include "headers/Functions/Buttons/Instances/menage/Mods/positionCorrection.hpp"
#include "headers/Functions/Buttons/Instances/menage/Mods/canBeInstalledChecker.hpp"
#include "headers/Functions/Buttons/Instances/menage/Mods/OldBetterBuildUIDReader.hpp"
#include "headers/Functions/Buttons/Instances/manage.hpp"

#include "headers/Functions/updates/handleHTML.hpp"

#include "headers/Events/scrolling/ScrollVersionDescription.hpp"
#include "headers/Events/scrolling/ScrollpatchNotesList.hpp"
#include "headers/Events/scrolling/ScrollInstancesList.hpp"
#include "headers/Events/scrolling/manage/bbw.hpp"
#include "headers/Events/scrolling/manage/vanillaSaves.hpp"
#include "headers/Events/scrolling/manage/modsManager.hpp"
#include "headers/Events/loop.hpp"

#include "headers/Functions/Buttons/Instances/unmount.hpp"
#include "headers/Functions/Buttons/Instances/mount.hpp"
#include "headers/Functions/Buttons/Instances/edit.hpp"
#include "headers/Functions/Buttons/Instances/open_folder.hpp"
#include "headers/Functions/Buttons/Instances/remove.hpp"

#include "headers/Start/nonEmptyDataFolderCheck.hpp"
#include "headers/Start/runtime.hpp"
#include "headers/Start/post_start_tasks.hpp"

#include "headers/Functions/mouse/left.hpp"

#include "headers/Functions/Launch/installAll.hpp"
#include "headers/Functions/Launch/debugBridge.hpp"
#include "headers/Functions/Launch/download_game.hpp"
#include "headers/Functions/Launch/run_game.hpp"

#include "headers/Functions/window/draw.hpp"
#include "headers/Functions/window/display.hpp"

#include "headers/Functions/updates/launcher_update_check.hpp"

#include "headers/SetObjectsParams/buttons/setFunctions.hpp"