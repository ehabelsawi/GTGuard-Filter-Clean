#include "IFStatic.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFStatic, 0x00EE9720)

CIFStatic::CIFStatic() {
    N00000609 = 0;
    N000096E4 = 0;

    m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
    m_FontTexture.sub_8B2BA0(3, D3DCOLOR_RGBA(0xB4, 0xB4, 0xB4, 255));
}

CIFStatic::~CIFStatic() {
    // empty
}

bool CIFStatic::OnCreate(long ln) {
    return true;
}

bool CIFStatic::SetText(const wchar_t *src) {
    if (src) {
        CIFWnd::SetText(src);
        Func_42();
        return true;
    }

    return false;
}

void CIFStatic::OnGfxMessage(Event3D *pEvent) {
    reinterpret_cast<void(__thiscall *)(CIFStatic *, Event3D *)>(0x0064D850)(this, pEvent);
}

void CIFStatic::RenderMyself() {
    reinterpret_cast<void(__thiscall *)(CIFStatic *)>(0x0064D940)(this);
}

void CIFStatic::Func_42() {
    reinterpret_cast<void(__thiscall *)(CIFStatic *)>(0x0064D9B0)(this);
}

bool CIFStatic::SetTextFormatted(const wchar_t *format, ...) {
    if (format == NULL) {
        return false;
    }

    wchar_t buffer[0x1000];

    va_list args;
    va_start(args, format);
    vswprintf(buffer, 0x1000, format, args);
    va_end(args);

    // Note: SetText also returns a boolean telling if setting the text was successful. However
    //       the original code does ignore that value here.
    SetText(buffer);

    Func_42();

    return true;
}

bool CIFStatic::Func_50(const wchar_t *format, ...) {
    if (format == NULL) {
        return false;
    }

    wchar_t buffer[0x1000];

    va_list args;
    va_start(args, format);
    vswprintf(buffer, 0x1000, format, args);
    va_end(args);

    // Note: SetText also returns a boolean telling if setting the text was successful. However
    //       the original code does ignore that value here.
    SetText(buffer);

    Func_42();

    return true;
}

bool CIFStatic::Func_51(const wchar_t *src) {
    assert(FALSE);
    return false;
}
