#pragma once

#include "IFWnd.h"

#define GDR_ALRAM_GUIDE_MGR_WND 158

typedef std::n_list<CIFWnd *> listGUIDES;

class CAlramGuideMgrWnd : public CIFWnd {

GFX_DECLARE_DYNAMIC_EXISTING(CAlramGuideMgrWnd, 0x00ee99a8)

public:
    CAlramGuideMgrWnd();

    CIFWnd *CreateGuideIcon(int nWndID);

    void UpdatePositions();

private:
    BYTE m_btGuidesCount; //0x036C
    listGUIDES m_listGuides; //0x0370
private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x037C)
        ENSURE_OFFSET(m_btGuidesCount, 0x036c)
        ENSURE_OFFSET(m_listGuides, 0x0370)
    END_FIXTURE()

    RUN_FIXTURE(CAlramGuideMgrWnd)
};
