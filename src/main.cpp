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
// Features planned in 0.13                                             //
//                                                                      //
// - add support to BetterBuildMod for 0.4.x                 Finished   //
// - improve support for SRML                                Finished   //
// - Debug options buttons functions                         Finished   //
// - add function to BBW gamesaves slots                     InProgress //
// - add function to backups manager buttons                 InProgress //
// - add function to mods explorer                           InProgress //
// - mounting process mapping                                InProgress //
// - add game patcher in C# to load debug bridge to any ver  Finished   //
// - add buttons hilight when category is selected           Finished   //
//                                                                      //
// - fix mods explorer                                       BUG        //
// - fix SIGSVG 22 ERROR                                     Resolved   //
// - fix Error after mount edited instance                   BUG        //
// - fix default debug enabled as default                    Resolved   //
//                                                                      //
// Features maybe added                                                 //
// - More languages                                                     //
// - HEX saves viewer                                                   //
// - Mounting instances without mounting game                           //
// - Instance auto installer                                            //
// - support for plugin loader Slime Rancher 0.3.x                      //
// - Customizable main page (console disable)                           //
//                                                                      //
//  Job started 31.08.25                                                //
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

            updateButtonsBlockingState();

            postStartTasks();   
        }
        window_draw();
        display_window();
    }
    close_launcher();
}