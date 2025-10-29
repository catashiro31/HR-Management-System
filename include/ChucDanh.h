#ifndef CHUCDANH_H
#define CHUCDANH_H

#include <string>

class ChucDanh {
private:
    std::string maChucDanh;
    std::string tenChucDanh;
    double luongCoBan; // Bậc lương cơ bản cho chức danh này

public:
    ChucDanh(const std::string& ma, const std::string& ten, double luong);

    // Getters
    std::string getMaChucDanh() const;
    std::string getTenChucDanh() const;
    double getLuongCoBan() const;

    // Setters
    void setTenChucDanh(const std::string& ten);
    void setLuongCoBan(double luong);

    void hienThi() const;

    // Dùng cho lưu file CSV
    std::string toStringCSV() const;
};

#endif // CHUCDANH_H