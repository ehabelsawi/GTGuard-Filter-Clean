#include <IFChatViewer.h>
#include <IFMainPopup.h>
#include <IFChatOptionBoard.h>
#include <IFWholeChat.h>
#include "IFExtQuickSlot.h"
#include "SRIFLib/NIFUnderMenuBar.h"

#include "hooks/Hooks.h"
#include "Util.h"
#include "imgui_windows/ImGui_Windows.h"

#include "IFflorian0Guide.h"
#include "examples/IFflorian0.h"
#include "examples/NIFKyuubi09.h"

#include "support/hook.h"

extern "C" _declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {

        // Setup all the required hooks
        Setup();

        // Inject all the new objects
        RegisterObject(&GFX_RUNTIME_CLASS(CIFflorian0));
        RegisterObject(&GFX_RUNTIME_CLASS(CIFflorian0Guide));
        RegisterObject(&GFX_RUNTIME_CLASS(CNIFKyuubi09));

        // Override existing objects

#ifdef CONFIG_EXT_QUICK_SLOT
        OverrideObject<CIFExtQuickSlot, 0x00ee9a28>();
        OverrideObject<CIFExtQuickSlotOption, 0x00ee9a48>();
#endif // CONFIG_EXT_QUICK_SLOT

        OverrideObject<CIFChatOptionBoard, 0x00eec128>();

#ifdef CONFIG_OLD_MAINPOPUP
        OverrideObject<CIFMainPopup, 0x00eea6dc>();
#endif // CONFIG_OLD_MAINPOPUP

#ifdef CONFIG_CHATVIEWER
        OverrideObject<CIFChatViewer, 0x00EEC168>();
#endif // CONFIG_CHATVIEWER

#ifdef CONFIG_WHOLE_CHAT
        OverrideObject<CIFWholeChat, 0x00eec7a8>();
#endif // CONFIG_WHOLE_CHAT

#ifdef CONFIG_MAINPOP_PLAYERINFO
        OverrideObject<CIFPlayerInfo, 0x00eea7e8>();
#endif // CONFIG_MAINPOP_PLAYERINFO

#ifdef CONFIG_IMGUI
        OnCreate(ImGui_OnCreate);
        OnEndScene(ImGui_OnEndScene);
        OnWndProc(ImGui_WndProc);

        OnPreSetSize(ImGui_OnPreSetSize);
        OnPostSetSize(ImGui_OnPostSetSize);
#endif // CONFIG_IMGUI

#ifdef CONFIG_OLD_UNDERBAR
        // https://www.elitepvpers.com/forum/sro-pserver-guides-releases/4256375-source-fix-old-exp-bar-writing-code.html
        replaceAddr(0x00D9841C, addr_from_this(&CNIFUnderMenuBar::Update));
#endif // CONFIG_OLD_UNDERBAR

        OnPreInitGameAssets(InstallRuntimeClasses);
    }

    return TRUE;
}
