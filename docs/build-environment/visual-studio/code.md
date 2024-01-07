# Setup VSCode

## Setup

1. Follow [this guide](2005.md) to install Visual Studio 2005
2. Follow [this guide](../ninja.md) to install Ninja build
3. Install VSCode

## Open Project

1. Open the project
2. Install recommended plugins (CMake & C++), VSCode should notify you if you don't have them.  
   ![Recommended Plugins Dialog](vscode-recommended-dialog.png)

3. Press Ctrl+Shift+P to open the command window
4. Type `select configure preset`, select it and press enter
   ![select configure preset](vscode-select-configure-preset.png)

5. Select RelWithDebInfo-cfg
   ![vscode select relwithdebinfo](vscode-select-relwithdebinfo.png)

6. Wait until configuration is done (should only take a few seconds)

7. Open command window again

8. Type `build target`, select this entry, press enter
   ![select build target](vscode-select-build-target.png)

9. Select `DevKit_DLL`
   ![select devkit dll](vscode-select-devkit-dll.png)

## Run and Debug

!!! important
    You must have a working game client in `BinOut/RelWithDebInfo/`. The client executable must load `DevKit_DLL.dll` as an imported dll or with LoadLibrary as the entry point. Just copy your whole game client to this folder.

1. Press Ctrl+Shift+P to open the command window
2. Type `debug` and select `Debug: Start Debugging`
   ![start debug command](vscode-start-debug.png)
3. In case you get another selection menu, select `Run client`
