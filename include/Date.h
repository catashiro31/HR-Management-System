#pragma once
#include <string>
#include <iostream>

using namespace std;

class Date {
private:
    int ngay;
    int thang;
    int nam;

    // Hàm này chỉ dùng nội bộ, nên ở private là đúng
    bool laNamNhuan(int nam) const;

public:
    // --- HÀM NÀY PHẢI Ở PUBLIC ---
    // (Vì NhanVien.cpp cần gọi nó)
    int soNgayTrongThang(int thang, int nam) const;

    Date(int d = 1, int m = 1, int y = 2000);
    void setDate(int d, int m, int y);

    // Getters
    string toString() const;
    int getNgay() const;
    int getThang() const;
    int getNam() const;

    friend ostream& operator<<(ostream& os, const Date& dt);
    friend istream& operator>>(istream& is, Date& dt);

    // So sánh
    bool operator<=(const Date& other) const;

    // Tiện ích
    Date layNgayHienTai();
    Date fromString(const string& str);
};