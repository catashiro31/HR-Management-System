#ifndef HELPER_H
#define HELPER_H

#include "GlobalConfig.h" 
#include "Date.h" 
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

class Helper {
public:
    // --- BỎ TOÀN BỘ STATIC ---
    void setConsoleUTF8();
    void xoaManHinh();
    void dungManHinh();

    int nhapSoNguyen(const string& prompt, int min, int max);
    double nhapSoThuc(const string& prompt, double min);
    string nhapChuoi(const string& prompt, bool choPhepRong = false);

    string trangThaiToString(TrangThaiLamViec trangThai);
    TrangThaiLamViec stringToTrangThai(const string& str);
    string toLower(const string& str);
    string roleToString(Role role);

    string formatCurrency(double value, bool showVND = false);
    string taoMaTuDong(const string& tienTo, int soThuTu);
    
    string chuanHoaTen(const string& hoTen);
    string taoEmail(const string& tenChuanHoa, const Date& ngaySinh, const string& maNV, bool dungMaNV);
    string taoPassword(const Date& ngaySinh, const string& maNV, bool dungMaNV);
};

#endif // HELPER_H