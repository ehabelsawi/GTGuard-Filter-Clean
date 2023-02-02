//
// Created by Kurama on 2/1/2023.
//

#include "NIFTextBoard.h"
#include "GNFontChar.h"

CNIFTextBoard::CNIFTextBoard() : m_NFontTexture() {
    m_fAniFadeSpeed = 0.0f;
    m_btCurrentTextureAlpha = 255; // D3DCOLOR_RGBA(0, 0, 0, 255)
    m_fAniFadeTime = 0.0f;

    m_dwTextureColor = D3DCOLOR_RGBA(0, 0, 0, 0);

    void *pFontData = g_sNFontDataVec->at(0);
    m_pFontTextData = pFontData;
    m_NFontTexture.m_pFontData = pFontData;
    m_dwUnknwonColor = D3DCOLOR_RGBA(255, 255, 255, 255);
    m_dwBG_FontColor = D3DCOLOR_RGBA(0, 0, 0, 0);
    InstantiateFontText(L"");

    m_nTextureHAlignType = HALIGN_CENTER;
    NTB_Func_3();
    m_nTextureVAlignType = VALIGN_CENTER;
    NTB_Func_3();

    m_pMainTexture3D = NULL;
    m_dwDestroyBGTextureMask = FALSE;
    m_pHoverTexture3D = NULL;
    m_pBgTexture3D = NULL;
    m_bRenderTexture = false;
}

void CNIFTextBoard::InstantiateFontText(const wchar_t *pText) {
    if(pText != NULL) {
        m_wstrFontTexture = pText;
        m_NFontTexture.SortTextLetters(m_wstrFontTexture.c_str());

        return;
    }

    m_wstrFontTexture.clear();
    m_NFontTexture.EraseTextLetters();
}