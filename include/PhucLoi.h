#ifndef PHUCLOI_H
#define PHUCLOI_H

#include <string>
#include <sstream>

class PhucLoi {
private:
    std::string maPhucLoi;
    std::string tenPhucLoi;
    double chiPhiHangThang;

public:
    PhucLoi(const std::string& ma, const std::string& ten, double chiPhi);

    // Getters
    std::string getMaPhucLoi() const;
    std::string getTenPhucLoi() const;
    double getChiPhiHangThang() const;

    // Setters
    void setTenPhucLoi(const std::string& ten);
    void setChiPhiHangThang(double chiPhi);

    void hienThi() const;

    // Dùng cho lưu file CSV
    std::string toStringCSV() const;
};

#endif // PHUCLOI_H

