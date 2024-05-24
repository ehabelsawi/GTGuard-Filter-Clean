#include "IFSystemMessage.h"

void CIFSystemMessage::WriteMessage(int a1, D3DCOLOR color, const wchar_t *msg, int a2, int a3) {
    // Redirection to original client code
    reinterpret_cast<void (__thiscall *)(CIFSystemMessage *, int, int, const wchar_t*, int, int)>(0x007B89E0)(this, a1, color, msg, a2, a3);
}

void CIFSystemMessage::WriteErrorMessage(BYTE btType, WORD wErrorCode, DWORD dwColor, int a5, int a6) {
    // todo : implement me... im very big btw
    reinterpret_cast<void(__thiscall *)(CIFSystemMessage *, BYTE, WORD, DWORD, int, int)>(0x007b8b40)(this, btType, wErrorCode, dwColor, a5, a6);
}
