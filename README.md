# :warning: Warning :warning:
This is a very early release! You are using on your own risk!

# Requirements
- [Visual C++ Redist](https://learn.microsoft.com/en-en/cpp/windows/latest-supported-vc-redist?view=msvc-170)
- [SteamCMD](https://developer.valvesoftware.com/wiki/SteamCMD)
- Steam account with purchased Slime Rancher

# Requirements to compile the code
- [SFML 2.6.1](https://www.sfml-dev.org/download/sfml/2.6.1)
- [MinGW 13.1.0](https://www.mingw-w64.org/downloads)
- SFML-GUI Lib (Not yet available)

# About
An open-source launcher designed to make it easier for users to manage various instances of the game Slime Rancher. It allows for the creation of individual game instances so you can separate the VANILLA game from modified versions and play any version of the game without the need to manually swap entire folders.

Need an older version of Slime Rancher to reminisce about the old times, see how the game looked before its release, or play with old mods like BetterBuild, but don’t know where to get it? If so, you’ve come to the right place because this program enables you to do it in a very simple way.

There is one condition:
You must own the game purchased on Steam.
If you don’t have it, use the launcher at YOUR OWN RISK! THIS PROJECT IS NOT INTENDED TO PROMOTE PIRACY!

THE PROGRAM DOES NOT SUPPORT OTHER PLATFORMS SUCH AS:

- Epic Games
- GOG
- Microsoft Store

# :question: How It Works :question:

The program uses an instance mounting system to bypass the restriction of running the game only from the main Steam installation folder. Created instances are stored by default in "Roaming/SRLauncher/instances".

For a folder to be recognized as an instance, it must contain an "info.json" file with information about the version and name. The main game folder named "Slime Rancher" is automatically treated as a mounted instance. If it does not contain an "info.json" file, it may not be recognized.

When a user selects an instance from the list, its folder is swapped with the one in the Steam game folder. YOU CANNOT HAVE MULTIPLE INSTANCES MOUNTED AT THE SAME TIME! **IF THE FOLDER IS NOT DETECTED AND ALREADY CONTAINS FILES FROM ANOTHER INSTANCE, IT MAY BE OVERWRITTEN!**

Unmounting an instance restores the instance folder to its original location. If the instance does not contain the downloaded game, a script will run to download it using SteamCMD.

You will need to log in to your Steam account with the game.

It is recommended to enter your login credentials in the profile settings. However, if you are concerned about your login details, you can enter them later directly in SteamCMD.

Notes:

- The procedure is very delicate! If something goes wrong during execution, it may result in game data, save files, or other files being corrupted!
- If you are running this launcher with a game that was already installed via Steam, it is recommended to rename the original game directory to something other than "Slime Rancher". This step is crucial to avoid potential issues with the launcher.
- If you plan to play an older version of the game, YOU MUST FIRST SWITCH Steam to OFFLINE MODE to avoid automatic updates.
- When launching an older version of the game, settings and achievements saved in the game may be lost, so it is recommended to make a backup.
- The launcher currently supports only x64 game builds.

# :hammer::wrench: Work In Progress...

At the moment, many of the launcher's features are still in development. Some are only mentioned or have the components responsible for them in place but are not yet functional. I work on the launcher in my free time and try to add new features whenever possible; however, many of them require a lot of work. If you decide to use the program at this stage, you are essentially a tester and need to be aware that you are using it at your own risk, as the mounting features are very delicate and could potentially damage game files or save data.
<hr>
©MinecraftSRDEV
