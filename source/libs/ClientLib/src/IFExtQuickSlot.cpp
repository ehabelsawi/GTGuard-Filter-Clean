#include "IFExtQuickSlot.h"
#include "GInterface.h"


CIFExtQuickSlot::~CIFExtQuickSlot() {
    SaveToolBarSetting();
}

bool CIFExtQuickSlot::OnCreate(long ln) {
    m_IRM.LoadFromFile("resinfo\\ifextquickslot.txt");

    m_pMyUnerMenuBar = g_pCGInterface->GetUnderMenuBar();


    return true;
}