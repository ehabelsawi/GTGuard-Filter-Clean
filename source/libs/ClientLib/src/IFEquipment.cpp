#include <CustomData/CustomSettingManager.h>
#include <ctime>
#include "IFEquipment.h"
#include "Game.h"
#include "GInterface.h"
#include "TextStringManager.h"
#define WeaponSlot 106
#define ShieldSlot 107
#define HeadSlot 100
#define ChestSlot 101
#define LegSlot 104
#define ShoulderSlot 102
#define HandSlot 103
#define FootSlot 105
#define EarringSlot 106
#define NecklaceSlot 107
#define JobSlot 108
#define LeftRingSlot 111
#define RightRingSlot 112

GFX_MSGMAP* CIFEquipment::MessageMap(){
    static const GFX_MSGMAP_ENTRY skillBoardMessageEntries[] =
            {
                    {GFX_WM_COMMAND, 0, 300, 300, BSSig_u12, 0,
                            (GFX_PMSG)(static_cast< void (GFX_MSG_CALL CGWndBase::*)() >(&CIFEquipment::AutoSort))},
                    // Diğer özel mesaj girişleri buraya eklenebilir
            };

    static GFX_MSGMAP newmap =
            {
                    reinterpret_cast<const GFX_MSGMAP *>(0x00da6e88), skillBoardMessageEntries,
            };
    return &newmap;
}
time_t lastUpdate;
template <typename T>
T my_min(const T& a, const T& b) {
    return (a < b) ? a : b;
}
#define STOP_AUTOSORT() \
    m_Settings->AutoSortRunning = false; \
    m_Settings->StartAutoSort = false;
void CIFEquipment::OnUpdateIMPL()
{

    if (m_Settings->StartAutoSort && float(clock() - lastUpdate) / CLOCKS_PER_SEC > 0.2)
    {
        bool finished = false;
        bool isPacketSent = false;

        D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 0);
        CIFSystemMessage* systemmessage = g_pCGInterface->GetSystemMessageView();

        if (!m_Settings->AutoSortRunning) {
            m_Settings->AutoSortRunning = true;
            systemmessage->WriteMessage(255, color, L"Auto sorting started...", 7, 7);
        }

        CIFInventory* Inventory = g_pCGInterface->GetMainPopup()->GetInventory();
        if (!Inventory)
        {
            STOP_AUTOSORT();
            return;
        }


        std::n_vector<CIFSlotWithHelp*>& slots = Inventory->pSlots;

        for (std::n_vector<CIFSlotWithHelp*>::iterator it = slots.begin(); it != slots.end(); ++it) {
            CIFSlotWithHelp* pSlot = *it;
            if (!pSlot || !pSlot->ItemInfo || !pSlot->ItemInfo->GetItemData()) continue;

            int itemId = pSlot->ItemInfo->GetItemData()->RefObjectId;
            int itemCount = pSlot->ItemInfo->GetQuantity();
            int maxCount = pSlot->ItemInfo->GetItemData()->m_maxStack;

            if (itemCount < maxCount) {
                for (std::n_vector<CIFSlotWithHelp*>::iterator jt = it + 1; jt != slots.end(); ++jt) {
                    CIFSlotWithHelp* pSlotj = *jt;
                    if (!pSlotj || !pSlotj->ItemInfo || !pSlotj->ItemInfo->GetItemData()) continue;

                    int itemIdj = pSlotj->ItemInfo->GetItemData()->RefObjectId;
                    int itemCountj = pSlotj->ItemInfo->GetQuantity();

                    if (itemIdj == itemId && itemCountj < maxCount) {
                        int countToMove = (itemCount < (maxCount - itemCountj)) ? itemCount : (maxCount - itemCountj);

                        CMsgStreamBuffer buf(0x7034);
                        buf << BYTE(0x0)
                            << BYTE(pSlotj->GetSlot() + 13)
                            << BYTE(pSlot->GetSlot() + 13)
                            << UINT16(countToMove);
                        SendMsg(buf);
                        isPacketSent = true;
                        break;
                    }
                }
            }

            if (isPacketSent)
                break;
        }

        if (!isPacketSent) {
            finished = true;
            STOP_AUTOSORT();
            color = D3DCOLOR_ARGB(255, 0, 255, 0);
            systemmessage->WriteMessage(255, color, L"Auto sorting finished...", 7, 7);

        }

        lastUpdate = clock();
    }
    if (g_pCGInterface)
      {
          int ItemsPoint = 0;
          for (size_t i = 0; i < 13; i++)
          {
              CSOItem* pItem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(i);

              if (pItem != 0x0)
              {
                  ObjectData* pData = pItem->GetObjectData();
                  if (pData)
                      ItemsPoint += (pItem->m_OptLevel + pData->ReqLevel1 + (pData->Rarity * 3));
              }
          }
          wchar_t Priceb[255];
          swprintf_s(Priceb, L"%d", ItemsPoint);
          m_IRM.GetResObj(99999, 1)->SetText(Priceb);


          if(m_Settings->AutoRepairHammerUsing)
          {
              bool itemfound = false;
              for(int i = 0; i < 7; i++)
              {

                  CSOItem * p = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(i);
                  if(p)
                  {
                      if(p->GetItemData() != NULL)
                      {
                          if(p->m_CurrDurability < 5)
                          {
                              itemfound = true;
                              break;
                          }
                      }
                  }
              }
              CSOItem * p = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7);
              if(p != NULL)
              {
                  if(p->GetItemData() != NULL)
                  {
                      if(p->GetItemData()->m_typeId.getTypeID1() == 3 && p->GetItemData()->m_typeId.getTypeID2() == 1 && p->GetItemData()->m_typeId.getTypeID3() == 4)
                      {
                          if(p->m_CurrDurability < 5)
                          {
                              itemfound = true;
                          }
                      }
                  }
              }
              if(itemfound)
              {
                  CIFInventory *Inventory = g_pCGInterface->GetMainPopup()->GetInventory();
                  int slotcnt = Inventory->InventorySlotCount();
                  for(int i = 0; i <= slotcnt; i++)
                  {
                      if(Inventory->pSlots[i]->ItemInfo != NULL)
                      {
                          if(Inventory->pSlots[i]->ItemInfo->GetItemData() != NULL)
                          {
                              if(Inventory->pSlots[i]->ItemInfo->GetItemData()->IsRepairHammer())
                              {
                                  CMsgStreamBuffer buf(0x704C);
                                  UINT16 type = Inventory->pSlots[i]->ItemInfo->GetItemData()->m_typeId.m_type_id_value;
                                  byte slot = i + 13;
                                  buf << slot;
                                  buf << type;
                                  //printf("%d \n", type);
                                  SendMsg(buf);
                                  break;
                              }
                          }
                      }
                  }

              }
          }

        }
    reinterpret_cast<void(__thiscall*)(CIFEquipment*)>(0x006ab6b0)(this);
}
bool CIFEquipment::OnCreateIMPL(long ln) {

    bool a = reinterpret_cast<bool(__thiscall*)(CIFEquipment*, long)>(0x006ac1c0)(this, ln);
     m_IRM.GetResObj(99999, 1)->m_FontTexture.sub_8B4750(7);
     m_IRM.GetResObj(9999, 1)->m_FontTexture.sub_8B4750(7);
    m_IRM.GetResObj(9999, 1)->SetText(L"Item Points");
    if(m_Settings->AutoSortButton)
    {
        m_IRM.GetResObj(300, 1)->ShowGWnd(true);
        m_IRM.GetResObj(300, 1)->SetText(L"Auto Sort");
    }
    return a;
}
void CIFEquipment::AutoSort()
{
    m_Settings->StartAutoSort = true;
}
void CIFEquipment::SetSlotLock(byte slot)
{
    if(slot == 0)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1)->ItemInfo->ItemLocked = 1;
            }

        }
    }
    if(slot == 1)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 2)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 3)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 4)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 5)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 6)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 7)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1)->ItemInfo != NULL)
            {
               this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 8)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1)->ItemInfo != NULL)
            {
                   this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 9)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 10)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 11)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
    if(slot == 12)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1)->ItemInfo->ItemLocked = 1;
            }
        }
    }
}
void CIFEquipment::SetSlotUnLock(byte slot)
{
    if(slot == 0)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1)->ItemInfo->ItemLocked = 0;
            }

        }
    }
    if(slot == 1)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 2)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 3)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 4)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 5)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 6)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 7)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 8)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1)->ItemInfo != NULL)
            {
                  this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 9)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1)->ItemInfo != NULL)
            {
                  this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 10)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1)->ItemInfo != NULL)
            {
                  this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 11)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
    if(slot == 12)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1)->ItemInfo->ItemLocked = 0;
            }
        }
    }
}
void CIFEquipment::SetItemTime(byte slot, long min)
{
    if(slot == 0)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1)->ItemInfo != NULL)
            {
                  this->m_IRM.GetResObj<CIFSlotWithHelp>(HeadSlot, 1)->ItemInfo->itemtimes = min;
            }

        }
    }
    if(slot == 1)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(ChestSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 2)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(ShoulderSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 3)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(HandSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 4)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(LegSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 5)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(FootSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 6)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(WeaponSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 7)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(ShieldSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 8)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(JobSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 9)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(EarringSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 10)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(NecklaceSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 11)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1)->ItemInfo != NULL)
            {
                 this->m_IRM.GetResObj<CIFSlotWithHelp>(LeftRingSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 12)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1)->ItemInfo != NULL)
            {
                  this->m_IRM.GetResObj<CIFSlotWithHelp>(RightRingSlot, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
    if(slot == 20)
    {
        if(this->m_IRM.GetResObj<CIFSlotWithHelp>(117, 1) != NULL)
        {
            if(this->m_IRM.GetResObj<CIFSlotWithHelp>(117, 1)->ItemInfo != NULL)
            {
                this->m_IRM.GetResObj<CIFSlotWithHelp>(117, 1)->ItemInfo->itemtimes = min;
            }
        }
    }
}
CSOItem* CIFEquipment::GetEquipmentObjectBySlot(BYTE SlotIndex)
{
    return reinterpret_cast<CSOItem*(__thiscall*)(CIFEquipment*, BYTE)>(0x006AB6E0)(this, SlotIndex);
}


CSOItem* CIFEquipment::Test4(BYTE param_1)
{
    return reinterpret_cast<CSOItem*(__thiscall*)(CIFEquipment*, BYTE)>(0x006ab800)(this, param_1);
}

void CIFEquipment::TakeItem(int param_1)
{
    reinterpret_cast<void*(__thiscall*)(CIFEquipment*, int)>(0x0068cb90)(this, param_1);
}
