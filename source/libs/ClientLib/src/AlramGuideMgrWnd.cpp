#include "AlramGuideMgrWnd.h"

#include "IFConfirmReputationGuide.h"
#include "IFEventGuide.h"
#include "IFQuestInfoGuide.h"
#include "IFLetterAlarmGuide.h"
#include "IFServerEventGuide.h"
#include "IFOpenMarketAlramGuide.h"
#include "IFEventGuideSecond.h"
#include "IFflorian0Guide.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CAlramGuideMgrWnd, 0x00ee99a8)

#define GUIDE_CONFIRMREPUTATION 165
#define GUIDE_EVENT 41
#define GUIDE_QUESTINFO 46
#define GUIDE_LETTERALARM 55
#define GUIDE_SERVEREVENT  179
#define GUIDE_OPENMARKETALRAM  198
#define GUIDE_EVENTSECOND  30006

#define ALRAM_GUIDE_ICON_SIZE 42

CAlramGuideMgrWnd::CAlramGuideMgrWnd() {
    m_btGuidesCount = 0;
}

void CAlramGuideMgrWnd::PrepareGuides() {
    reinterpret_cast<void(__thiscall*)(CAlramGuideMgrWnd*)>(0x0065c430)(this);
}

CIFWnd *CAlramGuideMgrWnd::CreateGuideIcon(int nWndID) {
    // Try to find the element in the list
    listGUIDES::iterator it = m_listGuides.begin();
    for (; it != m_listGuides.end(); ++it) {
        if ((*it)->UniqueID() == nWndID) {
            return *it;
        }
    }

    // List did not contain the element, try to create it
    RECT rect = {0,
                 0,
                 ALRAM_GUIDE_ICON_SIZE, 
                 ALRAM_GUIDE_ICON_SIZE};

    CIFWnd* pObj = 0;

    switch(nWndID) {
        case GUIDE_CONFIRMREPUTATION:
            pObj = (CIFWnd *) CreateInstance(this, GFX_RUNTIME_CLASS(CIFConfirmReputationGuide), rect, GUIDE_CONFIRMREPUTATION, 0);
            break;

        case GUIDE_EVENT:
            pObj = (CIFWnd *) CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventGuide), rect, GUIDE_EVENT, 0);
            break;

        case GUIDE_QUESTINFO:
            pObj = (CIFWnd *) CreateInstance(this, GFX_RUNTIME_CLASS(CIFQuestInfoGuide), rect, GUIDE_QUESTINFO, 0);
            break;

        case GUIDE_LETTERALARM:
            pObj = (CIFWnd *) CreateInstance(this, GFX_RUNTIME_CLASS(CIFLetterAlarmGuide), rect, GUIDE_LETTERALARM, 0);
            break;

        case GUIDE_SERVEREVENT:
            pObj = (CIFWnd *) CreateInstance(this, GFX_RUNTIME_CLASS(CIFServerEventGuide), rect, GUIDE_SERVEREVENT, 0);
            break;

        case GUIDE_OPENMARKETALRAM:
            pObj = (CIFWnd *) CreateInstance(this, GFX_RUNTIME_CLASS(CIFOpenMarketAlramGuide), rect, GUIDE_OPENMARKETALRAM, 0);
            break;

        case GUIDE_EVENTSECOND:
            pObj = (CIFWnd *) CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventGuideSecond), rect, GUIDE_EVENTSECOND, 0);
            break;

        case GUIDE_FLORIAN0:
            pObj = (CIFWnd *) CreateInstance(this, GFX_RUNTIME_CLASS(CIFflorian0Guide), rect, GUIDE_FLORIAN0, 0);
            break;

        default:
            assert(false);
    }

    m_listGuides.push_back(pObj);
    m_btGuidesCount++;

    PrepareGuides();

    return pObj;
}

