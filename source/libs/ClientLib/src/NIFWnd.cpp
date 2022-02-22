
#include "NIFWnd.h"

void CNIFWnd::ShowGWnd(bool bVisible) {
    reinterpret_cast<void (__thiscall *)(CNIFWnd *, bool)>(0x0046d760)(this, bVisible);
}
