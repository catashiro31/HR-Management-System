#pragma once
#include <string>
#include <iostream>

// Lớp Date đơn giản để quản lý ngày tháng
// Thể hiện tính đóng gói
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
    std::string toString() const; // Chuyển thành chuỗi "dd/mm/yyyy"

    // Các toán tử nạp chồng (overloading)
    friend std::ostream& operator<<(std::ostream& os, const Date& dt);
    friend std::istream& operator>>(std::istream& is, Date& dt);

    // Hàm static để lấy ngày hiện tại (đơn giản hóa)
    static Date layNgayHienTai();

    static Date fromString(const std::string& str);
};
