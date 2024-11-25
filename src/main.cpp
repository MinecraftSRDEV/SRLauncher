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

#include <curl/curl.h>

namespace fs = std::filesystem;

#include <SFMLGUI/Gui.hpp>

#include "includes.hpp"

void install_all_instances()
{
    
}

std::map <int, std::string> scan_all_instances()    
{
    std::map <int, std::string> queue;
    int itr = 1;

    for (const auto& pair : instances_list)
    {
        if (instances_list[pair.first].getInstalledStatus() == false)
        {
            queue[itr] = instances_list[pair.first].getID(); 
            itr++;
        }
    }
    return queue;
}

/* Main load sequence function. Contains a list of functions responsible for loading the launcher */
void load_sequence() 
{
    ///// Get run time date and s6ave to local varriabless /////
    rundate_get();

    ///// Construct all "Launcher" paths /////
    construct_paths();

    ///// Load required resources /////
    loadElements();

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
}

int main()
{
    create_window(1280, 800);

    load_sequence();

    devUiView.disable();

    while(window.isOpen())
    {
        if (window.hasFocus())
        {	
            events_loop();

            mouse_left();

            postStartTasks();

            
        }
        window_draw();
        display_window();
    }
    close_launcher();
}