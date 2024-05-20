#pragma once

#include "IFWnd.h"

class CIFScrollBar : public CIFWnd {

protected:
    /// \address 00659150
    void FUN_00659150(int a2);

private:
    char pad[0x34];

protected:
    int m_field_0x3a0;// 0x03a0
    int m_field_0x3a4;// 0x03a4

private:
    char pad2[4];


    BEGIN_FIXTURE()
        ENSURE_SIZE(0x3ac)
        ENSURE_OFFSET(m_field_0x3a0, 0x03a0)
        ENSURE_OFFSET(m_field_0x3a4, 0x03a4)
    END_FIXTURE()

    RUN_FIXTURE(CIFScrollBar)
};
