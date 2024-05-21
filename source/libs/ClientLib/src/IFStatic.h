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

    void RenderMyself_IMPL() {
        CIFStatic::RenderMyself();
    }

    /// \address 0064D940
    void RenderMyself() override;

    /// \address 0064D9B0
    void Func_42() override;

    /// \address 0064D780
    virtual bool SetTextFormatted(const wchar_t *format, ...);

    /// \address 0064D6C0
    virtual bool Func_50(const wchar_t *format, ...);

    /// \address 0064D750
    virtual bool Func_51(const wchar_t *text);

private:
    int m_field_0x36c;  //0x036C
    float m_field_0x370;//0x0370
    float m_field_0x374;//0x0374
    char pad_0370[0x8]; //0x0370


    BEGIN_FIXTURE()
    ENSURE_SIZE(0x380)
    ENSURE_OFFSET(m_field_0x370, 0x0370)
    ENSURE_OFFSET(m_field_0x374, 0x0374)
    END_FIXTURE()

    RUN_FIXTURE(CIFStatic)
};
