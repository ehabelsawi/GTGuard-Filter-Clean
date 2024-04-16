#include "IFConsole.h"

#include "ICPlayer.h"

#include "Game.h"

BOOL CIFConsole::IsConsolePermissioned() {
    if (g_pMyPlayerObj != NULL && g_pMyPlayerObj->IsGameMaster())
        return TRUE;

    return (Fun_GetCfgGame()->m_bDebugMode);
}

