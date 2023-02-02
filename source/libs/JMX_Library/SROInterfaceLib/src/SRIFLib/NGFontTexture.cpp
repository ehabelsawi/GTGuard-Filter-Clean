//
// Created by Kurama on 2/1/2023.
//

#include "NGFontTexture.h"

void CNGFontTexture::SortTextLetters(const wchar_t *pText) {
    reinterpret_cast<void (__thiscall *)(CNGFontTexture *, const wchar_t *)>(0x00476350)(this, pText);
}

void CNGFontTexture::EraseTextLetters() {
    m_BGroundDimensions.width = 0;
    m_BGroundDimensions.height = 0;

    // Clear all
    m_listTextChar.erase(m_listTextChar.begin(), m_listTextChar.end());
}