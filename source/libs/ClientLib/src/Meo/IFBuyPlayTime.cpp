#include <Game.h>
#include <ICPlayer.h>
#include <GInterface.h>
#include <TextStringManager.h>
#include <BSLib/multibyte.h>
#include <GlobalDataManager.h>
#include <Macro/IFMacroMenuAutoHunt.h>
#include <EntityManagerClient.h>
#include <ICMonster.h>
#include <NavMesh/LocationInfo.h>
#include <NavMesh/IRegionManager.h>
#include <Macro/IFMacroMenu.h>
#include <sstream>
#include <ExtraUI/IFCounterWnd.h>
#include <CustomData/CustomDataManager.h>
#include <CustomData/CustomSettingManager.h>
#include "IFBuyPlayTime.h"



#define GDR_GRANTNAME_BTN_APPLY 9



GFX_IMPLEMENT_DYNCREATE(CIFBuyPlayTime, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFBuyPlayTime, CIFMainFrame)
                    ONG_COMMAND(GDR_GRANTNAME_BTN_APPLY, &On_BtnClick)
                    ONG_COMMAND(1000, &On_BtnClick)

GFX_END_MESSAGE_MAP()

CIFBuyPlayTime::CIFBuyPlayTime(void){
}
CIFBuyPlayTime::~CIFBuyPlayTime(void){

}

bool CIFBuyPlayTime::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    m_IRM.LoadFromFile("clientlibrary\\resinfo\\ifbuyplaytime.txt");
    m_IRM.CreateInterfaceSection("Create", this);
    this->m_pTitleText->SetText(L"Reset the Play Time");
    /* this->m_pHandleBar->TB_Func_13("clientlibrary\\mall\\mall_web_top_image.ddj", 1, 1);
     this->m_pTitleText->SetText(L"          Reset the Stat Points");
     wnd_pos xo = this->m_pHandleBar->GetPos();

     this->m_pHandleBar->MoveGWnd(xo.x+2, xo.y + 3);

     m_pCloseBtn->TB_Func_13("clientlibrary\\mall\\mall_web_close_button.ddj", 1, 0);
     m_pCloseBtn->SetGWndSize(28,32);
     m_pCloseBtn->MoveGWnd(m_pCloseBtn->GetPos().x - 20, m_pCloseBtn->GetPos().y-2);
     //    this->SetText(L"Reset the Stat Points");

     this->m_pTitleText->BringToFront();
 */


    this->m_IRM.GetResObj(9, 1)->SetText(L"Reset");

    wnd_rect sz;



    sz.pos.x = 120;
    sz.pos.y = 46;
    sz.size.width = 16;
    sz.size.height = 16;
    CIFStatic* GoldLabel = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 9, 0);
    GoldLabel->SetText(L"Gold");
    GoldLabel->JustifyHorizontal(JUSTIFY_LEFT);
    GoldLabel->JustifyVertical(JUSTIFY_MIDDLE);

    sz.pos.x = 160;
    sz.pos.y = 46;
    sz.size.width = 16;
    sz.size.height = 16;
    m_GoldCB = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), sz, 10, 0);
    m_GoldCB->SetCheckBoxState(false);

    sz.pos.x = 200;
    sz.pos.y = 46;
    sz.size.width = 16;
    sz.size.height = 16;
    CIFStatic* GoldLabel2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 9, 0);
    wchar_t Buffers[250];
    swprintf(Buffers, sizeof(Buffers), L"%d Gold", m_Settings->PlayTimeResetGold);
    GoldLabel2->SetText(Buffers);
    GoldLabel2->JustifyHorizontal(JUSTIFY_LEFT);
    GoldLabel2->JustifyVertical(JUSTIFY_MIDDLE);



    sz.pos.x = 120;
    sz.pos.y = 76;
    sz.size.width = 16;
    sz.size.height = 16;
    CIFStatic* SilkLabel = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 99, 0);
    SilkLabel->SetText(L"Silk");
    SilkLabel->JustifyHorizontal(JUSTIFY_LEFT);
    SilkLabel->JustifyVertical(JUSTIFY_MIDDLE);

    sz.pos.x = 160;
    sz.pos.y = 76;
    sz.size.width = 16;
    sz.size.height = 16;
    m_SilkCB = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), sz, 100, 0);
    m_SilkCB->SetCheckBoxState(false);

    sz.pos.x = 200;
    sz.pos.y = 76;
    sz.size.width = 16;
    sz.size.height = 16;
    CIFStatic* GoldLabel23 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 90, 0);

    swprintf(Buffers, sizeof(Buffers), L"%d Silk", m_Settings->PlayTimeResetSilk);
    GoldLabel23->SetText(Buffers);
    GoldLabel23->JustifyHorizontal(JUSTIFY_LEFT);
    GoldLabel23->JustifyVertical(JUSTIFY_MIDDLE);


    UpdateMenuSize();
    this->ShowGWnd(false);
    return true;
}

void CIFBuyPlayTime::UpdateMenuSize()
{

    int PosX = 0, PosY = 0;
    PosY = (g_CGame->GetRes().res->height/2) - (this->GetSize().height/2);
    PosX = (g_CGame->GetRes().res->width/2) - (this->GetSize().width/2);
    this->MoveGWnd(PosX, PosY);
    BringToFront();
}


void CIFBuyPlayTime::OnUpdate()
{

}
void CIFBuyPlayTime::Clear()
{

}


void CIFBuyPlayTime::On_BtnClick() {

    if(m_SilkCB->GetCheckedState_MAYBE() && m_GoldCB->GetCheckedState_MAYBE())
    {
        g_pCGInterface->ShowMessage_Warning(L"You can only select one option");
        return;
    }
    else if(m_SilkCB->GetCheckedState_MAYBE())
    {
        CMsgStreamBuffer buf(0x169A);
        buf << byte(28);
        buf << (byte)0;
        SendMsg(buf);
    }
    else if(m_GoldCB->GetCheckedState_MAYBE())
    {
        CMsgStreamBuffer buf(0x169A);
        buf << byte(28);
        buf << (byte)1;
        SendMsg(buf);
    }
}
