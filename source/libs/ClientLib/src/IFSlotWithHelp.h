#pragma once

#include "IFWnd.h"

class CIFSlotWithHelp : public CIFWnd {
public:
private:
    char pad_036C[0x35C]; //0x036C
private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x06C8)
    END_FIXTURE()

    RUN_FIXTURE(CIFSlotWithHelp)
};