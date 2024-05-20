#include "IFVerticalScroll.h"

void CIFVerticalScroll::sub_65A390(RECT a2) {
    reinterpret_cast<void(__thiscall *)(CIFVerticalScroll *, RECT)>(0x65A390)(this, a2);
}

void CIFVerticalScroll::sub_65A500(short a2) {
    m_field_0x3a8 = 0;
    FUN_006590e0(a2);
    wnd_rect rectThis = this->GetBounds();
    wnd_rect rectHandle = m_scrollButton->GetBounds();
    m_scrollButton->MoveGWnd(rectHandle.pos.x, rectThis.pos.y);

    m_field_0x37c = rectThis.pos.y;
    m_arrowDownButton->MoveGWnd(rectThis.pos.x, a2 + 16 + rectThis.pos.y);
    OnCIFReady();
}

void CIFVerticalScroll::sub_65A5A0(int a2) {
    if (a2 == 0) {
        a2 = m_field_0x3a0;
    }
    FUN_00659150(m_field_0x3a4 - a2);
}

void CIFVerticalScroll::sub_65A5C0(int a2) {
    if (a2 == 0) {
        a2 = m_field_0x3a0;
    }
    FUN_00659150(m_field_0x3a4 + a2);
}
