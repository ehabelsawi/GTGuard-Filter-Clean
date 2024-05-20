#include "IFTileWnd.h"
#include <BSLib/Debug.h>

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFTileWnd, 0x00EECBD4)

CIFTileWnd::CIFTileWnd() {
    BS_DEBUG_LOW(">" __FUNCTION__);
    set_N00009B9D(0);
}

CIFTileWnd::~CIFTileWnd() {
    ReleaseTextures();
}

void CIFTileWnd::TB_Func_13(std::n_string str, int a3, int a4) {
    BS_DEBUG_LOW(__FUNCTION__ " (\"%s\", %d, %d)", str.c_str(), a3, a4);
    Func_49(str);
}

bool CIFTileWnd::OnCreate(long ln) {
    FUN_0081ace0();
    return true;
}

void CIFTileWnd::RenderMyself() {
    CIFWnd::RenderMyself();
}

void CIFTileWnd::SetGWndSize(int width, int height) {
    CIFWnd::SetGWndSize(width, height);
}

void CIFTileWnd::Func_40() {
    OnCIFReady();
}

void CIFTileWnd::OnCIFReady() {
    /// \todo Implement this function
    reinterpret_cast<void(__thiscall *)(CIFTileWnd *)>(0x0081A740)(this);
}

void CIFTileWnd::Func_49(std::n_string str) {
    assert(FALSE);
}

void CIFTileWnd::set_N00009B9D(bool a2) {
    N00009B9D = a2;
}

void CIFTileWnd::ReleaseTextures() {
    /// \todo Implement this function
    reinterpret_cast<void(__thiscall *)(CIFTileWnd *)>(0x0081AE00)(this);
}

void CIFTileWnd::FUN_0081ace0() {
    /// \todo Implement this function
    reinterpret_cast<void(__thiscall *)(CIFTileWnd *)>(0x0081ace0)(this);
}
