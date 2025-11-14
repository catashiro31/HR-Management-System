#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include <string>
using namespace std;

// === CẤU HÌNH VAI TRÒ ===
enum class Role {
    CHU_TICH = 1,
    TRUONG_PHONG = 2,
    KE_TOAN = 3,
    NHAN_VIEN = 4,
    CHUA_PHAN_LOAI = 0
};

// === CẤU HÌNH FILE ===
const string FILE_NHANVIEN = "nhanvien.csv";
const string FILE_PHONGBAN = "phongban.csv";
const string FILE_LICHSU = "lichsu.csv";
const string FILE_CHUCDANH = "chucdanh.csv";
const string FILE_PHUCLOI = "phucloi.csv";
const string FILE_DANGKY_PHUCLOI = "nhanvien_phucloi.csv";
// --- FILE MOI ---
const string FILE_ACCOUNT = "accounts.csv";


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