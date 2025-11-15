#ifndef PHUCLOI_H
#define PHUCLOI_H

#include <string>
#include <sstream>

using namespace std;


class PhucLoi {
private:
    string maPhucLoi;
    string tenPhucLoi;
    double chiPhiHangThang;

public:
    PhucLoi(const string& ma, const string& ten, double chiPhi);

    // Getters
    string getMaPhucLoi() const;
    string getTenPhucLoi() const;
    double getChiPhiHangThang() const;

    // Setters
    void setTenPhucLoi(const string& ten);
    void setChiPhiHangThang(double chiPhi);

    void hienThi() const;

    // Dùng cho lưu file CSV
    string toStringCSV() const;
};

#endif // PHUCLOI_H

