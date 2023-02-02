//
// Created by Kurama on 2/1/2023.
//
#pragma once

#include "BSLib/BSLib.h"

#include "NGFontTexture.h"

#include <d3d9.h>

enum ENUM_HALIGN_TYPE : int {
    HALIGN_LEFT = 0,
    HALIGN_CENTER = 1,
    HALIGN_RIGHT = 2,
};

enum ENUM_VALIGN_TYPE : int {
    VALIGN_TOP = 0,
    VALIGN_CENTER = 1,
    VALIGN_DOWN = 2,
};

class CNIFTextBoard {
public:
    CNIFTextBoard();

public:
    virtual ~CNIFTextBoard();

    virtual void NTB_Func_1(float a2);

    virtual void OnRender();

    virtual void NTB_Func_3();

    virtual void FontTextureRender();

    virtual void SetHAlign(ENUM_HALIGN_TYPE Type);

    virtual void SetVAlign(ENUM_VALIGN_TYPE Type);

    virtual void NTB_Func_7();

    ///\Alpha Alpha, is the Transparency
    virtual BYTE GetAlpha();

    virtual void SetAlpha(BYTE btValue);

    virtual void NTB_Func_10();

    virtual void TextureRender();

    virtual void NTB_Func_12(const char *str, int a3, int a4);

    virtual void NTB_Func_13(std::n_string str, int a3, int a4);

    virtual void NTB_Func_14(std::n_string str, int a3, int a4);

    virtual void NTB_Func_15(int a2);

    virtual void NTB_Func_16();

public:
    void InstantiateFontText(const wchar_t *pText);

private:
    ENUM_HALIGN_TYPE m_nTextureHAlignType; //0x0004
    ENUM_VALIGN_TYPE m_nTextureVAlignType; //0x0008
public:
    CNGFontTexture m_NFontTexture; //0x000C
private:
    std::n_wstring m_wstrFontTexture; //0x0078
private:
    D3DCOLOR m_dwUnknwonColor; //0x0094 im sure about thats its belong to font
    D3DCOLOR m_dwBG_FontColor; //0x0098
public:
    void *m_pFontTextData; //0x009C
private:
    D3DCOLOR m_dwTextureColor; //0x00A0 // m_pMainTexture3D color image
    char pad_00a4[8]; //0x00A4
    BYTE m_cAniFadeAlphaStart; //0x00AC // Count
    BYTE m_btCurrentTextureAlpha; //0x00AD
    BYTE m_cAniFadeAlphaMax; //0x00AE // Count
    float m_fAniFadeTime; //0x00B0
    float m_fAniFadeSpeed; //0x00B4
    IDirect3DBaseTexture9 *m_pBgTexture3D; //0x00B8 // Background
    IDirect3DBaseTexture9 *m_pHoverTexture3D; //0x00BC
    std::n_string m_strFocusTexturePath; //0x00C0
    IDirect3DBaseTexture9 *m_pMainTexture3D; //0x00DC // Current
    std::n_string m_strBGroundTexturePath; //0x00E0 // Background
    DWORD m_dwDestroyBGTextureMask; //0x00FC Bit 1 mean release its from the game texture mgr
    bool m_bRenderTexture; //0x0100
private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x0104)
        ENSURE_OFFSET(m_nTextureHAlignType, 0x0004)
        ENSURE_OFFSET(m_nTextureVAlignType, 0x0008)
        ENSURE_OFFSET(m_NFontTexture, 0x000C)
        ENSURE_OFFSET(m_wstrFontTexture, 0x0078)
        ENSURE_OFFSET(m_dwUnknwonColor, 0x0094)
        ENSURE_OFFSET(m_dwBG_FontColor, 0x0098)
        ENSURE_OFFSET(m_pFontTextData, 0x009C)
        ENSURE_OFFSET(m_dwTextureColor, 0x00A0)
        ENSURE_OFFSET(m_cAniFadeAlphaStart, 0x00AC)
        ENSURE_OFFSET(m_btCurrentTextureAlpha, 0x00AD)
        ENSURE_OFFSET(m_cAniFadeAlphaMax, 0x00AE)
        ENSURE_OFFSET(m_fAniFadeTime, 0x00B0)
        ENSURE_OFFSET(m_fAniFadeSpeed, 0x00B4)
        ENSURE_OFFSET(m_pBgTexture3D, 0x00B8)
        ENSURE_OFFSET(m_pHoverTexture3D, 0x00BC)
        ENSURE_OFFSET(m_strFocusTexturePath, 0x00C0)
        ENSURE_OFFSET(m_pMainTexture3D, 0x00DC)
        ENSURE_OFFSET(m_strBGroundTexturePath, 0x00E0)
        ENSURE_OFFSET(m_dwDestroyBGTextureMask, 0x00FC)
        ENSURE_OFFSET(m_bRenderTexture, 0x0100)
    END_FIXTURE()

    RUN_FIXTURE(CNIFTextBoard)
};