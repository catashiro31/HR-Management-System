#ifndef HELPER_H
#define HELPER_H

#include "GlobalConfig.h" // Cần cho TrangThaiLamViec
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <sstream>

class Helper {
public:
    static void setConsoleUTF8();
    static void xoaManHinh();
    static void dungManHinh();

    // Sửa lại hàm nhapSoNguyen và nhapSoThuc để khớp với file của bạn
    static int nhapSoNguyen(const std::string& prompt, int min, int max);
    static double nhapSoThuc(const std::string& prompt, double min);

    // Hàm nhập liệu gốc
    static std::string nhapChuoi(const std::string& prompt, bool choPhepRong = false);

    // Chuyển đổi
    static std::string trangThaiToString(TrangThaiLamViec trangThai);
    static TrangThaiLamViec stringToTrangThai(const std::string& str);

    // --- HAM MOI CAN THEM ---
    static std::string formatCurrency(double value, bool showVND = false); 
    static std::string taoMaTuDong(const std::string& tienTo, int soThuTu);
};

#endif // HELPER_H

