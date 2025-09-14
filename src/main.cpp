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
#include <cmath>
#include <windows.h>
#include <shlobj.h>
#include <iomanip>
#include <memory.h>
#include <csignal>
#include <commdlg.h>
#include <atomic>
#include <mutex>

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

    loadingAnimation::setupLoadingAnimation(sf::Vector2f(0, 0), "pink");

    ConsoleElements::console.unlockQueue();
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

            mouseContains();

            updateButtonsBlockingState();

            postStartTasks();   

            loadingAnimation::loadingAnimation();

            miniInstanceList::ifProcessFinished();
        }
        window_draw();
        display_window();
    }
    close_launcher();
}