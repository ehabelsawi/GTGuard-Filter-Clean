#pragma once
#include "IFMainFrame.h"
#include "IFEdit.h"
#include "IFCheckBox.h"
class CIFBuyPlayTime : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFBuyPlayTime)
GFX_DECLARE_MESSAGE_MAP(CIFBuyPlayTime)
private:
    CIFBuyPlayTime(void);
    ~CIFBuyPlayTime(void);
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void On_BtnClick();
public:
    void UpdateMenuSize();
    void Clear();

    CIFCheckBox* m_GoldCB;
    CIFCheckBox* m_SilkCB;

};
