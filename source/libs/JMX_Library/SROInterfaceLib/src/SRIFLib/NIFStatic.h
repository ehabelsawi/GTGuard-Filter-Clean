#pragma once

#include "NIFWnd.h"

// Author : Kyuubi09
// TODO : we need to reverse it, if u feel free, do it plis
class CNIFStatic : public CNIFWnd { // 872 bytes
GFX_DECLARE_DYNAMIC_EXISTING(CNIFStatic, 0x0115e090)

public:
	virtual void SetText(wchar_t* format, ...);
	char pad[32];
	
};
