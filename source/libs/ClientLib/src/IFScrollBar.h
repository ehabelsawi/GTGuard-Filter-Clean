#pragma once

#include "IFWnd.h"

class CIFScrollBar : public CIFWnd {



private:
    char pad[0x40];

    BEGIN_FIXTURE()
        ENSURE_SIZE(0x3ac)
    END_FIXTURE()

    RUN_FIXTURE(CIFScrollBar)
};
