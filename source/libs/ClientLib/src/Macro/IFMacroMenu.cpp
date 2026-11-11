#include "IFMacroMenu.h"
#include "Game.h"
#include <BSLib/Debug.h>
#include <IFSelectableArea.h>
#include <TextStringManager.h>


#define GDR_STATIC2 5
#define GDR_STATIC3 6
GFX_IMPLEMENT_DYNCREATE(CIFMacroMenu, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFMacroMenu, CIFMainFrame)
                    ONG_COMMAND(100, &CIFMacroMenu::OnUnknownStuff)

GFX_END_MESSAGE_MAP()

CIFMacroMenu::CIFMacroMenu(void) {
    //   AutoPotionSlot = 0;
    descbox = 0;
    BS_DEBUG_LOW(">" __FUNCTION__);
}
CIFMacroMenu::~CIFMacroMenu(void) {
    if (m_pTabs) {
        free(m_pTabs);
        m_pTabs = 0;
    }
    BS_DEBUG_LOW(">" __FUNCTION__);
}
int CIFMacroMenu::Func_4(int a2) {
    int v1 = 0;
    while (a2 != v1 + 100) {
        if (++v1 >= 7)
            return -1;
    }

    return 100;
}
bool CIFMacroMenu::OnCreate(long ln) {

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    m_IRM.LoadFromFile("clientlibrary\\resinfo\\ifmacromenu.txt");
    m_IRM.CreateInterfaceSection("Create", this);
    this->SetText(L"VSRO MACRO BOT");
    wnd_rect sz;

    sz.pos.x= 45;
    sz.pos.y = 42;

    m_pTabs = new CIFSelectableArea *[numberOfTabs];

    for (int i = 0; i < numberOfTabs; i++) {

        RECT selectable_area_size;
        selectable_area_size.top = 42;
        selectable_area_size.left = 32;
        // selectable_area_size.left = tabMarginLeft + tabWidth * i;
        selectable_area_size.right = tabWidth + 1;
        selectable_area_size.bottom = tabHeight;

        m_pTabs[i] = (CIFSelectableArea*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea),
                                                               selectable_area_size, tabFirstId + i, 0);

        m_pTabs[i]->SetFont(this->N00009C2F);


        m_pTabs[i]->sub_64CE30("interface\\option\\opt_long_tab_on.ddj",
                               "interface\\option\\opt_long_tab_off.ddj", "interface\\option\\opt_long_tab_off.ddj");

        switch (i) {
            case 0:
            {
                m_pTabs[0]->sub_64CC30(1);
                /*m_pTabs[0]->SetText(L"Auto h?i ph?c");*/
                m_pTabs[0]->SetText(TSM_GETTEXTPTR(L"UIIT_MACRO_VSRO_2"));
            }
                break;
            case 1:
            {
                m_pTabs[1]->MoveGWnd(m_pTabs[0]->GetPos().x + tabWidth + 10, m_pTabs[0]->GetPos().y);
                /*m_pTabs[1]->SetText(L"K? n?ng s?n");*/
                // m_pTabs[1]->SetClickable(false);
                m_pTabs[1]->SetText(TSM_GETTEXTPTR(L"UIIT_MACRO_VSRO_3"));
            }
                break;
            case 2:
            {
                m_pTabs[2]->MoveGWnd(m_pTabs[1]->GetPos().x + tabWidth + 10, m_pTabs[1]->GetPos().y);
                /*m_pTabs[2]->SetText(L"Thi?t l?p s?n");*/
                //m_pTabs[2]->SetClickable(false);
                m_pTabs[2]->SetText(TSM_GETTEXTPTR(L"UIIT_MACRO_VSRO_5"));
            }
                break;
            case 3:
            {
                m_pTabs[3]->MoveGWnd(m_pTabs[2]->GetPos().x + tabWidth + 10, m_pTabs[2]->GetPos().y);
                /*m_pTabs[3]->SetText((L"Auto nh?t ??"));*/
                m_pTabs[3]->SetText(TSM_GETTEXTPTR(L"UIIT_MACRO_VSRO_4"));
            }
                break;
            case 4:
            {
                m_pTabs[4]->MoveGWnd(m_pTabs[3]->GetPos().x + tabWidth + 10, m_pTabs[3]->GetPos().y);
                /*m_pTabs[4]->SetText(L"Auto cu?n");*/
                // m_pTabs[4]->SetClickable(false);
                m_pTabs[4]->SetText(TSM_GETTEXTPTR(L"UIIT_MACRO_VSRO_6"));
            }
                break;
        }
        m_pTabs[i]->sub_64CC30(0);

    }
    this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->m_pHandleBar->ShowGWnd(false);
    this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->m_pCloseBtn->ShowGWnd(false);
    this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->m_pTitleText->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));

    descbox = this->m_IRM.GetResObj<CIFTextBox>(4, 1);
   // descbox->JustifyHorizontal(JUSTIFY_LEFT);
    //descbox->JustifyVertical(JUSTIFY_TOP);

    this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->m_pTitleText->MoveGWnd(this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->m_pTitleText->GetPos().x, this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->m_pTitleText->GetPos().y - 8);


    sz.pos.x= 9;
    sz.pos.y = 64;
    sz.size.width = 683;
    sz.size.height = 412;

   AutoPotionSlot = m_IRM.GetResObj<CIFMacroMenuAutoPotion>(300, 1);
   AutoPotionSlot->BringToFront();



    AutoSkillSlot = m_IRM.GetResObj<CIFMacroMenuAutoSkill>(301, 1);

    AutoHuntSlot = m_IRM.GetResObj<CIFMacroMenuAutoHunt>(302, 1);

    PickupFilterSlot = m_IRM.GetResObj<CIFMacroMenuPickFilter>(303, 1);
    AutoScrollSlot = m_IRM.GetResObj<CIFMacroMenuAutoScrollSlot>(304, 1);
    for (int i = 0; i < numberOfTabs; i++) {
        if (i == 0)
            continue;

        m_pTabs[i]->sub_64CC30(0);
        m_pTabs[i]->m_FontTexture.sub_8B4750(2);
    }


    m_pTabs[0]->sub_64CC30(1);


    //AutoSkillSlot->ShowGWnd(false);
    descbox->SetText(L"§Æt c¸c vËt phÈm cÇn tù ®éng vµo c¸c « vµ kÐo thanh ngang ®Ó chän % tù ®éng håi phôc");
    this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->SetText(L"CÊu h×nh håi phôc");

    //AutoPotionSlot->ShowGWnd(true);
    //AutoHuntSlot->ShowGWnd(false);
    //PickupFilterSlot->ShowGWnd(false);
    //AutoScrollSlot->ShowGWnd(false);
    UpdateMenuSize();
    this->ShowGWnd(false);



    return true;
}

void CIFMacroMenu::OnUpdate()
{

}
void CIFMacroMenu::OnUnknownStuff() {
    int id = GetCurrentEventMsgCtrlId();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}
void CIFMacroMenu::ActivateTabPage(BYTE page) {
    for (int i = 0; i < numberOfTabs; i++) {
        if (i == page)
            continue;

        m_pTabs[i]->sub_64CC30(0);
        m_pTabs[i]->m_FontTexture.sub_8B4750(2);
    }


    m_pTabs[page]->sub_64CC30(1);
    switch (page)
    {
        case 0:
        {
            descbox->SetText(L"§Æt c¸c vËt phÈm cÇn tù ®éng vµo c¸c « vµ kÐo thanh ngang ®Ó chän % tù ®éng håi phôc.");
            this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->SetText(L"CÊu h×nh håi phôc");


            AutoHuntSlot->ShowGWnd(false);
            AutoSkillSlot->ShowGWnd(false);
            PickupFilterSlot->ShowGWnd(false);
            AutoScrollSlot->ShowGWnd(false);
            AutoPotionSlot->ShowGWnd(true);
            AutoPotionSlot->BringToFront();
        }
            break;
        case 1:
        {
            descbox->SetText(L"G¾p c¸c kü n¨ng cÇn sö dông vµo c¸c « bªn ph¶i vµ chän vò khÝ vµ khiªn tõ hßm ®å nh©n vËt vµo « ®Ó tù ®éng dïng kü n¨ng.");
            this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->SetText(L"CÊu h×nh kü n¨ng");


            AutoScrollSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(false);
            AutoPotionSlot->ShowGWnd(false);
            PickupFilterSlot->ShowGWnd(false);
            AutoSkillSlot->ShowGWnd(true);
            AutoSkillSlot->BringToFront();
        }
            break;

        case 2:
        {
            descbox->SetText(L"TÝch vµo c¸c « tïy chØnh tù ®éng s¨n.");
            this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->SetText(L"CÊu h×nh tïy chØnh");


            AutoScrollSlot->ShowGWnd(false);
            PickupFilterSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(false);
            AutoPotionSlot->ShowGWnd(false);
            AutoSkillSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(true);
            AutoHuntSlot->BringToFront();
        }
            break;
        case 3:
        {
            descbox->SetText(L"TÝch vµo c¸c môc cÇn thó nhÆt vµ gì bá thó nhÆt.");
            this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->SetText(L"CÊu h×nh nhÆt ®å");


            AutoScrollSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(false);
            AutoPotionSlot->ShowGWnd(false);
            AutoSkillSlot->ShowGWnd(false);
            PickupFilterSlot->ShowGWnd(true);
            PickupFilterSlot->BringToFront();
        }
            break;
        case 4:
        {
            descbox->SetText(L"§Æt c¸c items muèn tù ®éng söa dông vµo c¸c « vµ l­u l¹i.!");
            this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->SetText(L"CÊu h×nh tù ®éng sö dông items");


            PickupFilterSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(false);
            AutoPotionSlot->ShowGWnd(false);
            AutoSkillSlot->ShowGWnd(false);
            AutoScrollSlot->ShowGWnd(true);
            AutoScrollSlot->BringToFront();
        }
        break;

        case 5:
        {
            descbox->SetText(L"CÊu h×nh tù ®éng gi¶ kim thuËt");
            this->m_IRM.GetResObj<CIFMainFrame>(3, 1)->SetText(L"CÊu h×nh tù ®éng gi¶ kim thuËt");

            PickupFilterSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(false);
            AutoHuntSlot->ShowGWnd(false);
            AutoPotionSlot->ShowGWnd(false);
            AutoSkillSlot->ShowGWnd(false);
            AutoScrollSlot->ShowGWnd(false);

        }
            break;
    }
}

void CIFMacroMenu::UpdateMenuSize()
{
    int PosX = 0, PosY = 0;
    PosY = (g_CGame->GetRes().res->height/2 - 50) - (this->GetSize().height/2);
    PosX = (g_CGame->GetRes().res->width/2) - (this->GetSize().width/2);
    this->MoveGWnd(PosX, PosY);
    BringToFront();
}
