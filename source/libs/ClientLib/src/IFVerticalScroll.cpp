#include "IFVerticalScroll.h"

void CIFVerticalScroll::sub_65A390(RECT a2) {
    reinterpret_cast<void(__thiscall *)(CIFVerticalScroll *, RECT)>(0x65A390)(this, a2);
}

void CIFVerticalScroll::sub_65A500(short a2) {
    reinterpret_cast<void(__thiscall *)(CIFVerticalScroll *, short)>(0x0065A500)(this, a2);
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
