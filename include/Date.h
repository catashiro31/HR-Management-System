#pragma once
#include <string>
#include <iostream>

using namespace std;

class Date {
private:
    int ngay;
    int thang;
    int nam;

public:
    // Constructor
    Date(int d = 1, int m = 1, int y = 2000);

    // Setters
    void setDate(int d, int m, int y);

    // Getters
    string toString() const; // Chuyển thành chuỗi "dd/mm/yyyy"
    int getNgay() const; // <-- HÀM MỚI
    int getThang() const; // <-- HÀM MỚI
    int getNam() const; // <-- HÀM MỚI

    // Các toán tử nạp chồng (overloading)
    friend ostream& operator<<(ostream& os, const Date& dt);
    friend istream& operator>>(istream& is, Date& dt);

    // Hàm static để lấy ngày hiện tại (đơn giản hóa)
    static Date layNgayHienTai();
    static Date fromString(const string& str);
};