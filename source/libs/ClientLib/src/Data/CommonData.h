#pragma once

/**
 * Common data from CharacteData and ItemData
 * @note Field names match column names of file
 */
struct SCommonData {
    undefined2 N00001350; //0x0000
    // undefined pad_0002[2]; //0x0002
    int refObjectId; //0x0004
    std::n_wstring CodeName; //0x0008
    std::n_wstring ObjName; //0x0024
    std::n_wstring OrgObjCodeName; //0x0040
    undefined pad_005C[4]; //0x005C
    std::n_wstring NameStrID; //0x0060
    std::n_wstring DescStrID; //0x007C
    int DecayTime; //0x0098
    int Country; //0x009C
    undefined pad_00A0[104]; //0x00A0
    int Speed1; //0x0108
    int Speed2; //0x010C
    int Scale; //0x0110
    int BCHeight; //0x0114
    int BCRadius; //0x0118
    undefined pad_011C[8]; //0x011C
    std::n_string AssocFileObj; //0x0124
    std::n_string AssocFileDrop; //0x0140
    std::n_string AssocFileIcon; //0x015C
    std::n_string AssocFile1; //0x0178
    std::n_string AssocFile2; //0x0194
    undefined pad_01B0[16]; //0x01B0

private:
    BEGIN_FIXTURE()
        ENSURE_OFFSET(CodeName, 0x0008)
        ENSURE_OFFSET(ObjName, 0x0024)
        ENSURE_OFFSET(OrgObjCodeName, 0x0040)
        ENSURE_OFFSET(NameStrID, 0x0060)
        ENSURE_OFFSET(DescStrID, 0x007c)
        ENSURE_OFFSET(DecayTime, 0x0098)
        ENSURE_OFFSET(Country, 0x009C)

        ENSURE_OFFSET(Speed1, 0x0108)
        ENSURE_OFFSET(Speed2, 0x010c)
        ENSURE_OFFSET(Scale, 0x0110)
        ENSURE_OFFSET(BCHeight, 0x0114)
        ENSURE_OFFSET(BCRadius, 0x0118)

        ENSURE_OFFSET(AssocFileObj, 0x0124)
        ENSURE_OFFSET(AssocFileDrop, 0x0140)
        ENSURE_OFFSET(AssocFileIcon, 0x015c)
        ENSURE_OFFSET(AssocFile1, 0x0178)
        ENSURE_OFFSET(AssocFile2, 0x0194)

    END_FIXTURE()

    RUN_FIXTURE(SCommonData)
};
