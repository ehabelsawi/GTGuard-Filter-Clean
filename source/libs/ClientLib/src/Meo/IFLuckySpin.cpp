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
#include "IFLuckySpin.h"



#define GDR_GRANTNAME_BTN_APPLY 9



GFX_IMPLEMENT_DYNCREATE(CIFLuckySpin, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFLuckySpin, CIFMainFrame)
                    ONG_COMMAND(GDR_GRANTNAME_BTN_APPLY, &On_BtnClick)
                    ONG_COMMAND(1000, &On_BtnClick)

GFX_END_MESSAGE_MAP()

CIFLuckySpin::CIFLuckySpin(void){
}
CIFLuckySpin::~CIFLuckySpin(void){

}

bool CIFLuckySpin::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    m_IRM.LoadFromFile("clientlibrary\\resinfo\\ifluckyspin.txt");
    m_IRM.CreateInterfaceSection("Create", this);

    m_pCloseBtn->ShowGWnd(true);
    m_pCloseBtn->BringToFront();

    m_pHandleBar->ShowGWnd(false);
    m_pCloseBtn->TB_Func_13("clientlibrary\\mall\\mall_web_close_button.ddj", 1, 0);
    m_pCloseBtn->SetGWndSize(28,32);
    m_pCloseBtn->MoveGWnd(364, 2);
    m_IRM.GetResObj(4, 1)->SetText(L"Silk Charge");

    m_IRM.GetResObj(9, 1)->SetText(L"Play");

    wnd_rect sz;



    sz.pos.x = 180;
    sz.pos.y = 220;
    sz.size.width = 20;
    sz.size.height = 20;
    CIFStatic* GoldLabel = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 9111, 0);
    if(m_Settings->EnableLuckySpinSilk)
    {
        wchar_t Buffers[250];
        swprintf(Buffers, sizeof(Buffers), L"Play price = %d Silk", m_Settings->LuckySpinPrice);
        GoldLabel->SetText(Buffers);

    }
    else
    {
        wchar_t Buffers[250];
        swprintf(Buffers, sizeof(Buffers), L"%d Gold", m_Settings->LuckySpinPrice);
        GoldLabel->SetText(Buffers);
    }


    sz.size.width = 36;
    sz.size.height = 36;

    int center_x = 200;  // Merkez X
    int center_y = 220;  // Merkez Y
    int radius = 120;    // Slotların daire üzerindeki mesafesi
    int slot_count = 16; // Toplam slot sayısı

    for (int i = 0; i < slot_count; i++) {
        float angle = 2 * 3.14159f * i / slot_count; // Açıyı dereceye değil radyana çevirdik
        sz.pos.x = center_x + static_cast<int>(radius * cos(angle)) - sz.size.width / 2;
        sz.pos.y = center_y + static_cast<int>(radius * sin(angle)) - sz.size.height / 2;

        CIFStatic* bg = (CIFStatic*)CGWnd::CreateInstance(
                this, GFX_RUNTIME_CLASS(CIFStatic), sz,7601 + i, 0);
        bg->ShowGWnd(true);
        bg->TB_Func_13("clientlibrary\\mall\\itembg.ddj", 1, 1);
    }

    center_x = 200;  // Merkez X
    center_y = 220;  // Merkez Y

    sz.size.width = 32;
    sz.size.height = 32;

    for (int i = 0; i < slot_count; i++) {
        float angle = 2 * 3.14159f * i / slot_count; // Açıyı dereceye değil radyana çevirdik
        sz.pos.x = center_x + static_cast<int>(radius * cos(angle)) - sz.size.width / 2;
        sz.pos.y = center_y + static_cast<int>(radius * sin(angle)) - sz.size.height / 2;

        itemslots[i] = (CIFSlotWithHelp*)CGWnd::CreateInstance(
                this, GFX_RUNTIME_CLASS(CIFSlotWithHelp), sz, 601 + i, 0);
        itemslots[i]->ShowGWnd(true);
        itemslots[i]->SetClickable(false);

    }


    this->ShowGWnd(false);
    return true;
}

void CIFLuckySpin::UpdateMenuSize()
{

    int PosX = 0, PosY = 0;
    PosY = (g_CGame->GetRes().res->height/2) - (this->GetSize().height/2);
    PosX = (g_CGame->GetRes().res->width/2) - (this->GetSize().width/2);
    this->MoveGWnd(PosX, PosY);
    BringToFront();
}
void CIFLuckySpin::FillTheSlot(int itemID, int Count, int Slot) {
    if(Slot < 16)
    {
        printf("%d \n", Slot);
        const SItemData* data = &g_CGlobalDataManager->GetItemData(itemID);
        itemslots[Slot]->ShowGWnd(true);
        if (data != NULL) {
            itemslots[Slot]->TB_Func_13(data->AssocFileIcon.c_str(), 0, 0);

            CMsgStreamBuffer buf(0xB034);
            buf << INT32(0) << INT32(itemID);
            u_short typeID2 = data->m_typeId.getTypeID2();
            u_short typeID3 = data->m_typeId.getTypeID3();
            u_short typeID4 = data->m_typeId.getTypeID4();
            switch (typeID2) {
                case 1:
                    buf << UINT8(0) << UINT64(0) << UINT32(1) << UINT8(0) << UINT8(1) << UINT8(0) << UINT8(2) << UINT8(0);
                    break;
                case 2:
                    switch (typeID3) {
                        case 1:
                            buf << UINT8(0x01);
                            break;
                        case 2:
                            buf << UINT32(0x00);
                            break;
                        default:
                            if (typeID4 == 3)//Magic cube
                                buf << UINT32(0x01);
                            break;
                    }
                    break;
                case 3:
                    buf << UINT16(0x01);
                    if (typeID3 == 11)
                        if (typeID4 == 1 || typeID4 == 2)
                            buf << UINT8(0x00);
                        else if (typeID3 == 14 && typeID4 == 2)
                            buf << UINT8(0x00);
                    break;
            }

            CSOItem* tempItemInfo = new CSOItem();
            tempItemInfo->ReadFromPacket(&buf, 1);
            tempItemInfo->SetEnabled(true);
            if (tempItemInfo) {

                itemslots[Slot]->ItemInfo = tempItemInfo;
                /* if(tempItemInfo->GetItemData()->IsNasrun())
                 {
                     m_itemInfo->ItemInfo = tempItemInfo;
                 }
                 else
                 {
                     m_itemInfo->SetSlotData(tempItemInfo);
                 }*/
                itemslots[Slot]->ItemInfo->m_quantity = Count;
                itemslots[Slot]->ItemInfo->m_OptLevel = 0;
                itemslots[Slot]->SetType(19);
                itemslots[Slot]->ShowGWnd(true);
            }
        }
    }

}

void CIFLuckySpin::OnUpdate()
{

}
void CIFLuckySpin::Clear()
{

}


void CIFLuckySpin::On_BtnClick() {

CMsgStreamBuffer buf(0x169A);
buf << byte(27);
SendMsg(buf);
}
