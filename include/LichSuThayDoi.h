#pragma once
#include <string>
#include "Date.h"
using namespace std;

struct LichSuThayDoi {
    Date ngayThayDoi;
    string moTa;  
    string giaTriCu;
    string giaTriMoi;


    LichSuThayDoi(Date ngay, string mt, string cu, string moi)
        : ngayThayDoi(ngay), moTa(mt), giaTriCu(cu), giaTriMoi(moi) {}
};
