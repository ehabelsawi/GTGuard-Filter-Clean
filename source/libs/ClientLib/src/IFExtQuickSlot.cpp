#include "IFExtQuickSlot.h"
#include "GInterface.h"
#include "Game.h"
#include "IFExtQuickSlotSlot.h"
#include <remodel/MemberFunctionHook.h>

CIFExtQuickSlot::CIFExtQuickSlot() :
        m_bVertical(false),
        m_bTwoLines(false),
        m_bTransparent(false),
        m_bSlotsLocked(false),
        m_bToolBarLocked(false),
        m_pMyUnerMenuBar(NULL) {
    m_bSlotsVisible = true;
    m_SectionTypeID = 255;
}

HOOK_ORIGINAL_MEMBER(0x0065e8d0, &CIFExtQuickSlot::SetBarVerticalState)

void CIFExtQuickSlot::SetBarVerticalState(bool bState) {
    m_bVertical = bState;
}

HOOK_ORIGINAL_MEMBER(0x0065e8e0, &CIFExtQuickSlot::SetBarTransparentState)

void CIFExtQuickSlot::SetBarTransparentState(bool bState) {
    m_bTransparent = bState;
}

HOOK_ORIGINAL_MEMBER(0x0065e8f0, &CIFExtQuickSlot::SetSlotLockState)

void CIFExtQuickSlot::SetSlotLockState(bool bState) {
    m_bSlotsLocked = bState;
}

HOOK_ORIGINAL_MEMBER(0x0065e900, &CIFExtQuickSlot::SetBarLockState)

void CIFExtQuickSlot::SetBarLockState(bool bState) {
    m_bToolBarLocked = bState;
}

HOOK_ORIGINAL_MEMBER(0x0065e910, &CIFExtQuickSlot::SetBarTwoLinesState)

void CIFExtQuickSlot::SetBarTwoLinesState(bool bState) {
    m_bTwoLines = bState;
}

void CIFExtQuickSlot::SaveExtSlotSetting() {
    char buffer[0x200];
    sprintf_s(buffer, "%s\\Setting\\SRExtQSOption.dat", theApp.GetWorkingDir());

    FILE *file = fopen(buffer, "wb+");
    if (file != NULL) {
        bool data[6];
        // maybe thats easy?
        data[0] = m_bSlotsVisible;
        data[1] = m_bVertical;
        data[2] = m_bTwoLines;
        data[3] = m_bTransparent;
        data[4] = m_bSlotsLocked;
        data[5] = m_bToolBarLocked;
        fwrite(&data[0], 1, 6, file);
        fclose(file);
    }
}

CIFExtQuickSlot::~CIFExtQuickSlot() {
    SaveExtSlotSetting();
}

void CIFExtQuickSlot::ToggleExtQuickSlotOption(bool bVisible) {
    reinterpret_cast<void (__thiscall *)(CIFExtQuickSlot *, bool)>(0x0065eb10)(this, bVisible);
}

void CIFExtQuickSlot::SetSlotsVisible(bool bVisible) {
    m_bSlotsVisible = bVisible;

    if (!bVisible)
        m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                "interface\\quick_slot\\qsl_hopen_button.ddj", NULL, NULL);
    else
        m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                "interface\\quick_slot\\qsl_hclose_button.ddj", NULL, NULL);

    if (m_SectionTypeID == NULL || m_SectionTypeID == SECTION_TYPE_2)
        for (int iVar4 = -9; iVar4 != 1; iVar4++) {
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_10 + iVar4, 1)->ShowGWnd(m_bSlotsVisible);
            if (iVar4 <= -5)
                m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_BOARD_5 + (iVar4 + 5), 1)->ShowGWnd(
                        m_bSlotsVisible);
        }
    else if (m_SectionTypeID == SECTION_TYPE_1 || m_SectionTypeID == SECTION_TYPE_3)
        for (int iVar2 = 0; iVar2 < 10; iVar2++) {
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar2, 1)->ShowGWnd(m_bSlotsVisible);
            if (iVar2 < 5)
                m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_BOARD_1 + iVar2, 1)->ShowGWnd(
                        m_bSlotsVisible);
        }

    m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_END, 1)->ShowGWnd(m_bSlotsVisible);
}

void CIFExtQuickSlot::OnToggleSlotsOption() {
    ToggleExtQuickSlotOption(!m_IRM.GetResObj(5, 1));
}

void CIFExtQuickSlot::OnDropDownButton() {
    SetSlotsVisible(!m_bSlotsVisible); //wait... what???
}

void CIFExtQuickSlot::ClearSlotsTexture() {
    reinterpret_cast<void (__thiscall *)(CIFExtQuickSlot *)>(0x0065eef0)(this);
#if 0
    for (int iVar2 = 0; iVar2 < 10; iVar2++) {
        m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar2,
                                             1)->GetSlotUnderBarBySlothgWnd()->FUN_006871d0();
        m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar2,
                                             1)->GetSlotUnderBarBySlothgWnd()->TB_Func_13("", NULL, NULL);
    }
#endif
}

bool CIFExtQuickSlot::OnCreate(long ln) {
    m_IRM.LoadFromFile("resinfo\\ifextquickslot.txt");

    m_pMyUnerMenuBar = g_pCGInterface->GetUnderMenuBar();


    return true;
}