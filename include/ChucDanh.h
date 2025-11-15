#ifndef CHUCDANH_H
#define CHUCDANH_H

#include <string>
using namespace std;

class ChucDanh {
private:
    string maChucDanh;
    string tenChucDanh;
    double luongCoBan; // Bậc lương cơ bản cho chức danh này

public:
    ChucDanh(const string& ma, const string& ten, double luong);

    // Getters
    string getMaChucDanh() const;
    string getTenChucDanh() const;
    double getLuongCoBan() const;

    // Setters
    void setTenChucDanh(const string& ten);
    void setLuongCoBan(double luong);

    void hienThi() const;

    // Dùng cho lưu file CSV
    string toStringCSV() const;
};

#endif // CHUCDANH_H