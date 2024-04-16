#pragma once

#include "IFWnd.h"

class CIFConsole : public CIFWnd
{
private:
	enum eVisibleMode : DWORD {
		VISIBLE_MODE_INVISIBLE,

		VISIBLE_MODE_OPENING, 
		VISIBLE_MODE_CLOSING,

		VISIBLE_MODE_VISIBLE
	};

private:
	char pad_036C[0x3b8 - 0x036c]; //0x036C
	eVisibleMode m_CurVisibleMode; //0x03B8
	char pad_03BC[0x05A4 - 0x03B8];
public:
	BOOL IsConsolePermissioned();

	void SetVisibleMode(DWORD dwMode);

};
