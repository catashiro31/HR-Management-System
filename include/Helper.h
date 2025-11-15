#ifndef HELPER_H
#define HELPER_H

#include "GlobalConfig.h" 
#include "Date.h" // <-- THÊM VÀO
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

    // Hàm nhập liệu
    static int nhapSoNguyen(const string& prompt, int min, int max);
    static double nhapSoThuc(const string& prompt, double min);
    static string nhapChuoi(const string& prompt, bool choPhepRong = false);
    
    // Chuyển đổi
    static string trangThaiToString(TrangThaiLamViec trangThai);
    static TrangThaiLamViec stringToTrangThai(const string& str);
    static string toLower(const string& str);

    // --- HÀM CŨ ---
    static string formatCurrency(double value, bool showVND = false);
    static string taoMaTuDong(const string& tienTo, int soThuTu);
    
    // --- HÀM MỚI (Cho Bước 2) ---
    static string chuanHoaTen(const string& hoTen);
    static string taoEmail(const string& tenChuanHoa, const Date& ngaySinh);
    static string taoPassword(const Date& ngaySinh);
    static string roleToString(Role role);

    static string boDauTiengViet(const string& str);
};

#endif // HELPER_H