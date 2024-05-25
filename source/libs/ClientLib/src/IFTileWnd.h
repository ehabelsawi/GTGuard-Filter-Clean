#pragma once

#include "IFWnd.h"

#define CORNER_LEFT_UP 0
#define CORNER_RIGHT_UP 1
#define CORNER_RIGHT_DOWN 2
#define CORNER_LEFT_DOWN 3

#define EDGE_LEFT_SIDE 0
#define EDGE_MID_UP 1
#define EDGE_RIGHT_SIDE 2
#define EDGE_MID_DOWN 3

class CIFTileWnd : public CIFWnd {
    GFX_DECLARE_DYNAMIC_EXISTING(CIFTileWnd, 0x00EECBD4)

public:
    /// \address 0081AB10
    CIFTileWnd();

    /// \address 0081B490
    ~CIFTileWnd();

    /// \address 0081AC50
    void TB_Func_13(std::n_string str, int a3, int a4) override;

    /// \address 0081B530
    bool OnCreate(long ln) override;

    /// \address 0081A730
    void RenderMyself() override;

    /// \address 0081A920
    void SetGWndSize(int width, int height) override;

    /// \address 0081A720
    void Func_40() override;

    /// \address 0081A740
    void OnCIFReady() override;

    /// \address 0081B540
    virtual void SetFrameTexture(std::n_string strTexture);

protected:
    /// \addresss 0081A910
    void Set_field_036C(bool a2);

    /// \address 0081AE00
    void ReleaseTextures();

private:
    /// \address 0081ace0
    void InitializeFrameTextures();

protected:
    /// \address 0081a930
    void OptimizeEdgesVerticesPos();

    /// \address 0081aa20
    void OptimizeCornersVerticesPos();

    /// \address 0081ae80
    void SetCornersTexture(std::n_string strCorners[4]);

    /// \address 0081b1b0
    void SetEdgesTexture(std::n_string strEdges[4]);

private:
    bool field_036C;                            //0x036C
    IDirect3DBaseTexture9 *m_pCornersTexture[4];//0x0370
    IDirect3DBaseTexture9 *m_pEdgesTexture[4];  //0x0380
    std::n_string m_strCornersTexture[4];       //0x0390
    std::n_string m_strEdgesTexture[4];         //0x0400
    D3DVECTOR m_vecCornersRenderBuff[4][8];     //0x0470
    D3DVECTOR m_vecEdgesRenderBuff[4][8];       //0x05F0
    wnd_size m_sCornersSize[4];                 //0x0770
    wnd_size m_sEdgesSize[4];                   //0x0790
private:
    BEGIN_FIXTURE()
        ENSURE_SIZE(0x7b0)
        ENSURE_OFFSET(m_vecCornersRenderBuff, 0x0470)
        ENSURE_OFFSET(m_vecEdgesRenderBuff, 0x05f0)
    END_FIXTURE()

    RUN_FIXTURE(CIFTileWnd)
};
