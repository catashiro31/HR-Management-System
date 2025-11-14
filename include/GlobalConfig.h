#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include <string>
using namespace std;

// Cấu hình file
const string FILE_NHANVIEN = "nhanvien.csv";
const string FILE_PHONGBAN = "phongban.csv";
const string FILE_LICHSU = "lichsu.csv";

// --- FILE MOI ---
const string FILE_CHUCDANH = "chucdanh.csv";
const string FILE_PHUCLOI = "phucloi.csv";
const string FILE_DANGKY_PHUCLOI = "nhanvien_phucloi.csv";

// Cấu hình hệ thống
enum class LoaiNhanVien {
    LUONG_CUNG = 1,
    THEO_GIO = 2,
    HOA_HONG = 3
};

enum class TrangThaiLamViec {
    THU_VIEC = 1,
    CHINH_THUC = 2,
    DA_NGHI = 3,
    KHONG_XAC_DINH = 0
};

#endif // GLOBALCONFIG_H