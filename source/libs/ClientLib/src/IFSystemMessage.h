#pragma once

#include "IFWnd.h"

class CIFSystemMessage : public CIFWnd {
public:
    /// \address 007B89E0
    void WriteMessage(int a1, D3DCOLOR color, const wchar_t *msg, int a2, int a3);

private:
    char pad_036c[32]; //0x036C
private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x038C)
    END_FIXTURE()
    
    RUN_FIXTURE(CIFSystemMessage)
};
