#pragma once

#include <d3d9.h>

class CIFSystemMessage {
public:
    /// \address 007B89E0
    void WriteMessage(int a1, D3DCOLOR color, const wchar_t *msg, int a2, int a3);
};
