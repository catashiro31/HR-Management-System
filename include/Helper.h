#ifndef HELPER_H
#define HELPER_H

#include "GlobalConfig.h" // Cần cho TrangThaiLamViec
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

class Helper {
public:
    static void setConsoleUTF8();
    static void xoaManHinh();
    static void dungManHinh();

    // Sửa lại hàm nhapSoNguyen và nhapSoThuc để khớp với file của bạn
    static int nhapSoNguyen(const string& prompt, int min, int max);
    static double nhapSoThuc(const string& prompt, double min);

    // Hàm nhập liệu gốc
    static int nhapSoNguyen(); // Giữ lại hàm cũ của tôi nếu bạn chưa có
    static string nhapChuoi(const string& prompt, bool choPhepRong = false);

    // Chuyển đổi
    static string trangThaiToString(TrangThaiLamViec trangThai);
    static TrangThaiLamViec stringToTrangThai(const string& str);
    static string toLower(const string& str);

    // --- HAM MOI CAN THEM ---
    static string formatCurrency(double value, bool showVND = false);
    static string taoMaTuDong(const string& tienTo, int soThuTu);
};

#endif // HELPER_H

