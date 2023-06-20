
#include "IFExtQuickSlot.h"
#include "GInterface.h"
#include "Game.h"
#include "IFExtQuickSlotSlot.h"

#include "BSLib/Debug.h"
#include <remodel/MemberFunctionHook.h>

#define SR_EXT_OPTION_DATA_COUNT 6
#define SR_EXT_OPTION_SLOT_VISIBLE_OFFSET 0
#define SR_EXT_OPTION_VERTICAL_OFFSET 1
#define SR_EXT_OPTION_2LINES_OFFSET 2
#define SR_EXT_OPTION_TRANSPARENT_OFFSET 3
#define SR_EXT_OPTION_LOCKED_OFFSET 4
#define SR_EXT_OPTION_BAR_LOCKED_OFFSET 5

GFX_BEGIN_MESSAGE_MAP(CIFExtQuickSlot, CIFWnd)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_OPT_BTN, &CIFExtQuickSlot::OnToggleSlotsOption)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_ONOFF_BTN, &CIFExtQuickSlot::OnDropDownButton)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_HORI_BTN, &CIFExtQuickSlot::OnClickSlotsHorizontal)
                    ONG_COMMAND(GDR_EXT_QUICKSLOT_VERT_BTN, &CIFExtQuickSlot::OnClickSlotsVertical)
GFX_END_MESSAGE_MAP()

CIFExtQuickSlot::CIFExtQuickSlot() :
        m_bVertical(false),
        m_bTwoLines(false),
        m_bTransparent(false),
        m_bSlotsLocked(false),
        m_bToolBarLocked(false),
        m_pMyUnderMenuBar(NULL) {
    m_bSlotsVisible = true;
    m_btSectionTypeID = 255;
}

GFX_IMPLEMENT_DYNCREATE_FN(CIFExtQuickSlot, CIFWnd)

void CIFExtQuickSlot::SetBarVerticalState(bool bState) {
    m_bVertical = bState;
}

void CIFExtQuickSlot::SetBarTransparentState(bool bState) {
    m_bTransparent = bState;
}

void CIFExtQuickSlot::SetSlotLockState(bool bState) {
    m_bSlotsLocked = bState;
}

void CIFExtQuickSlot::SetBarLockState(bool bState) {
    m_bToolBarLocked = bState;
}

void CIFExtQuickSlot::SetBarTwoLinesState(bool bState) {
    m_bTwoLines = bState;
}

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFExtQuickSlot, 0x00ee9a28)

void CIFExtQuickSlot::SaveExtSlotSetting() {
    char buffer[0x200];

    sprintf_s(buffer, "%s\\Setting\\SRExtQSOption.dat", theApp.GetWorkingDir());

    FILE* file = fopen(buffer, "wb+");

    int local_208 = 1; // hmm setting is saved? // or Config type?
    if (file != NULL) {
        bool bData[SR_EXT_OPTION_DATA_COUNT];
        fwrite(&local_208, 4, 1, file);
        bData[SR_EXT_OPTION_SLOT_VISIBLE_OFFSET] = m_bSlotsVisible;
        bData[SR_EXT_OPTION_VERTICAL_OFFSET] = m_bVertical;
        bData[SR_EXT_OPTION_2LINES_OFFSET] = m_bTwoLines;
        bData[SR_EXT_OPTION_TRANSPARENT_OFFSET] = m_bTransparent;
        bData[SR_EXT_OPTION_LOCKED_OFFSET] = m_bSlotsLocked;
        bData[SR_EXT_OPTION_BAR_LOCKED_OFFSET] = m_bToolBarLocked;
        fwrite(&bData, sizeof(bool), SR_EXT_OPTION_DATA_COUNT, file);
        fclose(file);
    }
}

CIFExtQuickSlot::~CIFExtQuickSlot() {
    SaveExtSlotSetting();
}

undefined1 CIFExtQuickSlot::ToggleExtQuickSlotOption(bool bVisible) {
    return reinterpret_cast<undefined1 (__thiscall *)(CIFExtQuickSlot *, bool)>(0x0065eb10)(this, bVisible);
}

void CIFExtQuickSlot::SetSlotsVisible(bool bVisible) {
    m_bSlotsVisible = bVisible;

    if (m_btSectionTypeID == 0 || m_btSectionTypeID == SECTION_TYPE_1) {
        if (!bVisible)
            m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                    "interface\\quick_slot\\qsl_hopen_button.ddj", NULL, NULL);
        else
            m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                    "interface\\quick_slot\\qsl_hclose_button.ddj", NULL, NULL);
    } else {
        if (!bVisible)
            m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                    "interface\\quick_slot\\qsl_vopen_button.ddj", NULL, NULL);
        else
            m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_13(
                    "interface\\quick_slot\\qsl_vclose_button.ddj", NULL, NULL);
    }

    if (m_btSectionTypeID == 0 || m_btSectionTypeID == SECTION_TYPE_2) {
        for (int iVar4 = 30, iVar2 = 10; iVar2 != 0; iVar4++, iVar2--) {
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(70 + iVar4, 1)->ShowGWnd(m_bSlotsVisible);
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(iVar4, 1)->ShowGWnd(m_bSlotsVisible);
        }
    } else if (m_btSectionTypeID == SECTION_TYPE_1 || m_btSectionTypeID == SECTION_TYPE_3) {
        for (int iVar4 = 0; iVar4 < 10; iVar4++) {
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar4, 1)->ShowGWnd(m_bSlotsVisible);
            if (iVar4 < 5)
                m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_BOARD_1 + iVar4, 1)->ShowGWnd(
                        m_bSlotsVisible);
        }
    }

    m_IRM.GetResObj<CIFStatic>(GDR_EXT_QUICKSLOT_SLOT_END, 1)->ShowGWnd(m_bSlotsVisible);
}

void CIFExtQuickSlot::OnToggleSlotsOption() {
    ToggleExtQuickSlotOption(!m_IRM.GetResObj<CIFExtQuickSlotOption>(GDR_EXT_QUICKSLOT_OPTION, 1));
}

void CIFExtQuickSlot::OnDropDownButton() {
    SetSlotsVisible(!m_bSlotsVisible);
}

void CIFExtQuickSlot::ClearChildofSlot() {
    reinterpret_cast<void(__thiscall*)(CIFExtQuickSlot*)>(0x0065eef0)(this);
#if 0
    for (int iVar2 = 0; iVar2 < 10; iVar2++) {
        m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar2,
            1)->GetSlotUnderBarBySlothgWnd()->FUN_006871d0(NULL);
        m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar2,
            1)->GetSlotUnderBarBySlothgWnd()->TB_Func_13("", 0, 0);
    }
#endif
}

void CIFExtQuickSlot::UpdateBarSlotsStyle() {
    short Sections = 0;

    if (!m_bVertical && m_bTwoLines)
        Sections = SECTION_TYPE_1;
    else if (m_bVertical && !m_bTwoLines)
        Sections = SECTION_TYPE_2;
    else if (m_bTwoLines)
        Sections = SECTION_TYPE_3;

    if (Sections == m_btSectionTypeID) {
        for (int iVar5 = 0; iVar5 < 10; iVar5++)
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5, 1)->UpdatehgWndSlot(
                    m_pMyUnderMenuBar->m_slots[40 + iVar5]->m_main_slot);
    }

    if (m_btSectionTypeID == 0)
        m_IRM.DeleteCreatedSection("Type1");
    else if (m_btSectionTypeID != SECTION_TYPE_4)
        m_IRM.DeleteCreatedSection("Type4");

    if (Sections == 0)
        m_IRM.CreateInterfaceSection("Type1", this);
    else if (Sections == SECTION_TYPE_1)
        m_IRM.CreateInterfaceSection("Type2", this);
    else if (Sections == SECTION_TYPE_2)
        m_IRM.CreateInterfaceSection("Type3", this);
    else
        m_IRM.CreateInterfaceSection("Type4", this);

    wnd_size dragsz = m_IRM.GetResObj(GDR_EXT_QUICKSLOT_WND, 1)->GetSize();
    this->SetGWndSize(dragsz.width, dragsz.height);
    wnd_pos barps = this->GetPos();

    m_btSectionTypeID = Sections;
    switch (m_btSectionTypeID) {
        case SECTION_TYPE_1: {
            int v32 = 0;
            for (int iVar5 = 0; iVar5 < 10; iVar5++) {
                CIFExtQuickSlotSlot* extslot = m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5,
                                                                                    1);
                extslot->UpdatehgWndSlot(
                        m_pMyUnderMenuBar->m_slots[40 + iVar5]->m_main_slot);
                if (iVar5 >= 5)
                    extslot->MoveGWnd(v32 + (barps.x - 149), barps.y + 40);
                else
                    extslot->MoveGWnd(v32 + (barps.x + 31), barps.y + 4);
                v32 += 36;
            }
            break;
        } case SECTION_TYPE_2: {
            int v32 = 0;
            for (int iVar5 = 0; iVar5 < 10; iVar5++) {
                CIFExtQuickSlotSlot* extslot = m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5,
                                                                                    1);
                extslot->UpdatehgWndSlot(
                        m_pMyUnderMenuBar->m_slots[40 + iVar5]->m_main_slot);
                extslot->MoveGWnd(barps.x + 5, v32 + (barps.y + 43));
                v32 += 36;
            }
            break;
        } case SECTION_TYPE_3: {
            int v32 = 0;
            for (int iVar5 = 0; iVar5 < 10; iVar5++) {
                CIFExtQuickSlotSlot* extslot = m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5,
                                                                                    1);
                extslot->UpdatehgWndSlot(
                        m_pMyUnderMenuBar->m_slots[40 + iVar5]->m_main_slot);
                if (iVar5 >= 5)
                    extslot->MoveGWnd(barps.x + 41, v32 + (barps.y - 149));
                else
                    extslot->MoveGWnd(barps.x + 5, v32 + (barps.y + 31));
                v32 += 36;
            }
            break;
        } default: {
            for (int iVar5 = 0; iVar5 < 10; iVar5++) {
                int v32 = 0;
                CIFExtQuickSlotSlot* extslot = m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + iVar5,
                                                                                    1);
                extslot->UpdatehgWndSlot(
                        m_pMyUnderMenuBar->m_slots[40 + iVar5]->m_main_slot);
                extslot->MoveGWnd(v32 + (barps.x + 43), barps.y + 4);
                v32 += 36;
            }
            break;
        }
    }

    SetSlotsVisible(m_bSlotsVisible);
}

void CIFExtQuickSlot::UpdateSlotsBarDirection() {
    UpdateBarSlotsStyle();

    char N00009BB9 = -1;

    if (m_bTransparent)
        N00009BB9 = 110;

    m_IRM.GetResObj<CIFDragableArea>(GDR_EXT_QUICKSLOT_WND, 1)->TB_Func_9(N00009BB9);
    m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_OPT_BTN, 1)->TB_Func_9(N00009BB9);
    m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_HORI_BTN, 1)->TB_Func_9(N00009BB9);
    m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_VERT_BTN, 1)->TB_Func_9(N00009BB9);
    m_IRM.GetResObj<CIFButton>(GDR_EXT_QUICKSLOT_ONOFF_BTN, 1)->TB_Func_9(N00009BB9);

    if (!m_bSlotsVisible)
        return;

    m_IRM.GetResObj(GDR_EXT_QUICKSLOT_SLOT_END, 1)->TB_Func_9(N00009BB9);

    if (m_btSectionTypeID == 0 || m_btSectionTypeID == SECTION_TYPE_2) {
        for (int v22 = 10, v14 = 30; v22 != 0; v14++, v22--) {
            m_IRM.GetResObj(v14 + 70, 1)->TB_Func_9(N00009BB9);
            m_IRM.GetResObj(v14, 1)->TB_Func_9(N00009BB9);
        }
    } else if (m_btSectionTypeID == SECTION_TYPE_1 || m_btSectionTypeID == SECTION_TYPE_3) {
        for (int v11 = 0; v11 < 10; v11++) {
            m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + v11, 1)->TB_Func_9(N00009BB9);
            if (v11 < 5)
                m_IRM.GetResObj<CIFStatic>(GDR_EXT_QUICKSLOT_SLOT_BOARD_1 + v11, 1)->TB_Func_9(N00009BB9);
        }
    }

    for (int v17 = 0; v17 < 10; v17++) {
        m_IRM.GetResObj<CIFExtQuickSlotSlot>(GDR_EXT_QUICKSLOT_SLOT_1 + v17, 1)->SetDragable(!m_bSlotsLocked);
    }

    m_IRM.GetResObj<CIFDragableArea>(GDR_EXT_QUICKSLOT_WND, 1)->SetClickable(!m_bToolBarLocked);
}

void CIFExtQuickSlot::LoadExtSlotSetting() {
    char buffer[0x200];

    sprintf_s(buffer, "%s\\Setting\\SRExtQSOption.dat", theApp.GetWorkingDir());

    FILE *pFileOpt = fopen(buffer, "rb");

    int local_210; // Config type?
    if (pFileOpt == NULL) {
        SetBarVerticalState(true);
        SetBarTransparentState(true);
        SetSlotLockState(false);
        SetBarLockState(false);
        SetBarTwoLinesState(true);
    } else {
        fread_s(&local_210, -1, sizeof(local_210), 1, pFileOpt);
        if (local_210 == 1) {
            bool bConfig[SR_EXT_OPTION_DATA_COUNT];

            fread_s(&bConfig, sizeof(bConfig), sizeof(bConfig), SR_EXT_OPTION_DATA_COUNT, pFileOpt);
            m_bSlotsVisible = bConfig[SR_EXT_OPTION_SLOT_VISIBLE_OFFSET];
            SetBarVerticalState(bConfig[SR_EXT_OPTION_VERTICAL_OFFSET]);
            SetBarTwoLinesState(bConfig[SR_EXT_OPTION_2LINES_OFFSET]);
            SetBarTransparentState(bConfig[SR_EXT_OPTION_TRANSPARENT_OFFSET]);
            SetSlotLockState(bConfig[SR_EXT_OPTION_LOCKED_OFFSET]);
            SetBarLockState(bConfig[SR_EXT_OPTION_BAR_LOCKED_OFFSET]);
        }
        fclose(pFileOpt);
    }
    UpdateSlotsBarDirection();
}

void CIFExtQuickSlot::OnClickSlotsHorizontal() {
    SetBarVerticalState(false);
    UpdateSlotsBarDirection();
}

void CIFExtQuickSlot::OnClickSlotsVertical() {
    SetBarVerticalState(true);
    UpdateSlotsBarDirection();
}

bool CIFExtQuickSlot::OnCreate(long ln) {
    m_IRM.LoadFromFile("resinfo\\ifextquickslot.txt");

    m_pMyUnderMenuBar = g_pCGInterface->GetUnderMenuBar();
    LoadExtSlotSetting();

    return true;
}
