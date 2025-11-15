#pragma once
#include <string>
#include "Date.h"
using namespace std;

// Struct đơn giản để lưu một bản ghi về sự thay đổi
// Đây là Memento trong Memento Design Pattern
struct LichSuThayDoi {
    Date ngayThayDoi;
    string moTa;      // Ví dụ: "Cap nhat dia chi", "Thay doi trang thai"
    string giaTriCu;
    string giaTriMoi;

    // Constructor
    LichSuThayDoi(Date ngay, string mt, string cu, string moi)
        : ngayThayDoi(ngay), moTa(mt), giaTriCu(cu), giaTriMoi(moi) {}
};
