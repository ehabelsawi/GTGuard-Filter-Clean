#pragma once
#include "ifwnd.h"
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
	virtual void Func_49(std::n_string str);

protected:
    /// \addresss 0081A910
	void set_N00009B9D(bool a2);

    /// \address 0081AE00
	void ReleaseTextures();

private:
    /// \address 0081ace0
    void FUN_0081ace0();

private:
	bool N00009B9D; //0x036C
	char pad_036D[35]; //0x036D
	std::n_string N00009BAF[4]; //0x0390
	std::n_string N00009BB0[4]; //0x0400
	char pad_0470[832]; //0x0470

    BEGIN_FIXTURE()
        ENSURE_SIZE(0x7b0)
        ENSURE_OFFSET(N00009B9D, 0x36c)
    END_FIXTURE()

    RUN_FIXTURE(CIFTileWnd)
};

