#pragma once
#include "IFMainFrame.h"
#include "IFEdit.h"
#include "IFCheckBox.h"
class CIFStatReset : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFStatReset)
GFX_DECLARE_MESSAGE_MAP(CIFStatReset)
private:
    CIFStatReset(void);
    ~CIFStatReset(void);
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void On_BtnClick();
public:
    void UpdateMenuSize();
    void Clear();

    CIFCheckBox* m_GoldCB;
    CIFCheckBox* m_SilkCB;

};
