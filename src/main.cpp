///////////////////////////////////////////////////////////
// Open-source launcher for Slime Rancher                //
//                                                       //
// Copyright 2025 MinecraftSRDEV                         //
//                                                       //
// This software is released under GPL 3.0 license on    //
// https://github.com/MinecraftSRDEV/SRLauncher          //
// You can use it for free without any limitations       //
//                                                       //
// Software in development You using it on your own risk!//
///////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Features planned in 0.12                                             //
// - Mounting instances without mounting game                InProgress //
// - Old BetterBuild world resigner                          Finished   //
// - Instance auto installer                                 InProgress //
// - Debug options buttons functions                         InProgress //
// - Launcher background customization                       Finished   //
// - "informations" page in instance manage (BB lock)        Finished   //
// - add function to remove BBW gamesave                     Finished   //
// - add function to BBW gamesaves slots                     InProgress //
// - add function to backups manager buttons                 InProgress //
// - add function to mods explorer                           InProgress //
// - add edit function by creating specyfic folder           InProgress //
// - add BetterBuild UID reader                              Finished   //
// - improved manage main page                               Finished   //
// - fix mods explorer                                       InProgress //
// - fix Vgamesaves listing                                  Resolved   //
// - fix SIGSVG 22 ERROR                                     InProgress //
// - fix default debug enabled as default                    Untested   //
// - fix buttons blocking                                    Resolved   //
// - fix backups list refresh                                Resolved   //
// - fix backups instance path                               Resolved   //
// - fix vanilla saves recognizer                            Resolved   //
// - fix BetterBuild saves list clearing                     Resolved   // 
// - fix BetterBuild worlds loader for stable game versions  Resolved   //
//                                                                      //
// Features maybe added                                                 //
// - More languages                                                     //
// - HEX saves viewer                                                   //
//                                                                      //
//  Job started 12.05.25                                                //
//////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <regex>
#include <thread>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <cstdint>
#include <windows.h>
#include <shlobj.h>
#include <iomanip>
#include <memory.h>
#include <csignal>
#include <commdlg.h>

#include <curl/curl.h>

namespace fs = std::filesystem;

#include <SFMLGUI/Gui.hpp>

#include "includes.hpp"

/* Main load sequence function. Contains a list of functions responsible for loading the launcher */
void load_sequence() 
{
    ///// Get run time date and s6ave to local varriabless /////
    rundate_get();

    ///// Construct all "Launcher" paths /////
    construct_paths();

    ///// Load required resources /////
    loadElements();

    window.setMouseCursor(waitCursor);

    ///// Set SFML text attributes onetime /////
    setRuntimeTexts();

    ///// Set SFML Rectangle shapes attributes onetime /////
    setShapesAttributes();

    ///// Set loaded resources to SFML elements /////
    setTextures();

    ///// Set SFML-GUI Buttons attributes onetime /////
    setButtons();

    console.unlockQueue();
    log_message("Console ready", LogTypes::LOG_INFO);

    ///// Set functions to buttons from SFML-GUI onetime /////
    setFunctions();

    ///// Check run functions /////
    runtime_check();

    ///// set theme to objects /////
    setTheme();
    
    ///// Create DropDownList from all "versionsData_map" contents /////
    createDDListFromVersionsMap();

    window.setMouseCursor(arrowCursor);
}

int main()
{
    addErrorHandlers();
    
    create_window(1280, 800);

    load_sequence();

    devUiView.disable();
    // devUiView.enable();

    while(window.isOpen())
    {
        events_loop();
        if (window.hasFocus())
        {	
            mouse_left();

            postStartTasks();   
        }
        window_draw();
        display_window();
    }
    close_launcher();
}