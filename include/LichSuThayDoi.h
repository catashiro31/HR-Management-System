#pragma once
#include <string>
#include "Date.h"

// Struct đơn giản để lưu một bản ghi về sự thay đổi
// Đây là Memento trong Memento Design Pattern
struct LichSuThayDoi {
    Date ngayThayDoi;
    std::string moTa;      // Ví dụ: "Cap nhat dia chi", "Thay doi trang thai"
    std::string giaTriCu;
    std::string giaTriMoi;

    // Constructor
    LichSuThayDoi(Date ngay, std::string mt, std::string cu, std::string moi)
        : ngayThayDoi(ngay), moTa(mt), giaTriCu(cu), giaTriMoi(moi) {}
};
