#pragma once
#include "IFMainFrame.h"
#include "IFEdit.h"
#include "IFCheckBox.h"
class CIFLuckySpin : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFLuckySpin)
GFX_DECLARE_MESSAGE_MAP(CIFLuckySpin)
private:
    CIFLuckySpin(void);
    ~CIFLuckySpin(void);
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void On_BtnClick();
public:
    void UpdateMenuSize();
    void Clear();

    CIFCheckBox* m_GoldCB;
    CIFCheckBox* m_SilkCB;
    CIFSlotWithHelp * itemslots[30];
    void FillTheSlot(int ItemID, int Count, int Slot);
};
