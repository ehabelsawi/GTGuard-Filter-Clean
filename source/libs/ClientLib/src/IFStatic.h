#pragma once

#include "IFWnd.h"

class CIFStatic : public CIFWnd {
    GFX_DECLARE_DYNAMIC_EXISTING(CIFStatic, 0x00EE9720)

public:
    /// \address 0064D5F0
    CIFStatic();

    /// \address 0064D690
    ~CIFStatic();

public:
    /// \address 0064D6B0
    bool OnCreate(long ln) override;

    /// \address 0064D810
    bool SetText(const wchar_t *src) override;

    /// \address 0064D850
    void OnGfxMessage(Event3D *pEvent) override;

    /// \address 0064D940
    void RenderMyself() override;

    /// \address 0064D9B0
    void Func_42() override;

    virtual bool SetTextFormatted(const wchar_t *format, ...);

    /// \address 0064D6C0
    virtual bool Func_50(const wchar_t *format, ...);

    /// \address 0064D750
    virtual bool Func_51(const wchar_t *src);

private:
    int N000096E4;    //0x036C
    char pad_0370[16];//0x0370
};
