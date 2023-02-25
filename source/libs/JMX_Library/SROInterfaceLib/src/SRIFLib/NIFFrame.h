//
// Created by Kurama on 2/25/2023.
//
#pragma once

#include "NIFTileWnd.h"

class CNIFFrame : public CNIFTileWnd {
public:
    /// \address 00473670
    bool OnCreate(long ln) override;

    /// \address 004736a0
    void RenderMyself() override;

private:
    /// \address 004745a0
    void SetFrameTexture(const std::n_string &strTexture) override;

private:
private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x078c)
    END_FIXTURE()

    RUN_FIXTURE(CNIFFrame)
};