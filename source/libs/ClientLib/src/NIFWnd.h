#pragma once

#include "GFXMainFrame/GWnd.h"

class CNIFWnd : public CGWnd { // also CNIFTextBoard...
    //todo : reverse me in the future ^^?

public:
    CNIFWnd(void);

    ~CNIFWnd(void);

public:
    /* CNIFTextBoard override funcs...
    void NIFTB_Func_4() override;

    void NIFTB_Func_7() override;

    char NIFTB_Func_8() override;

    void NIFTB_Func_11() override; */

    bool OnCreate(long ln) override;

    void OnUpdate() override;

    bool OnRelease() override;

    void RenderMyself() override;

    void OnWndMessage(Event3D *a1) override;

    bool Func_18(Event3D *a1) override;

    bool On3DEvent_MAYBE(Event3D *a2) override;

    void BringToFront() override;

    void SetGWndSize(int width, int height) override;

    void Func_22(int x, int y) override;

    void ShowGWnd(bool bVisible) override;

    void Func_37() override;

    virtual void MoveGWnd(int x, int y);

    virtual void MoveGWnd2(wnd_pos pos);

    virtual void Func_40();

    virtual void OnCIFReady();

    virtual void Func_42();

    virtual void OnCloseWnd();

    virtual void Func_44();

    virtual void Func_45();

    virtual bool IsInside(int x, int y);

    virtual bool SetText(const wchar_t *src);

    virtual const wchar_t *GetText();

    virtual void Func_49();

private:
    char pad[836 - 132];

};
