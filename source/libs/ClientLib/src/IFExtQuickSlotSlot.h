#pragma once

#include "IFWnd.h"

class CIFExtQuickSlotSlot : public CIFWnd {

public:
    bool OnCreate(long ln) override;

    void RenderMyself() override;

    void OnWndMessage(Event3D *a1) override;

    bool Func_25(int a1) override;

    bool Func_28(int a1, int a2, int a3) override;

    int OnMouseRightDown(int a1, int x, int y) override;

    int OnMouseRightUp(int a1, int x, int y) override;


};