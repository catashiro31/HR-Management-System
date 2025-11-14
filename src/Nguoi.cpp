#include "../include/Nguoi.h"
#include <iostream>
#include <string>
#include <sstream>

Nguoi::Nguoi(std::string ten, std::string cccd, std::string dc,
             std::string sdt, std::string mail, Date ns)
    : hoTen(ten), cmnd_cccd(cccd), diaChi(dc), soDienThoai(sdt), email(mail), ngaySinh(ns) {}

// Destructor ảo không cần làm gì cụ thể ở lớp base này
Nguoi::~Nguoi() {}

// Định nghĩa các hàm ảo luuVaoFile và docTuFile
// Sử dụng ký tự ',' làm phân cách (CSV-like)
void Nguoi::luuVaoFile(std::ostream& os) const {
    // Thay thế các dấu cách trong chuỗi bằng '_' để tránh lỗi khi đọc file
    // (Một kỹ thuật đơn giản, dùng CSV chuẩn sẽ tốt hơn) 
    // Tạm thời giả định chuỗi không chứa ký tự ','
    os << hoTen << ","
       << cmnd_cccd << ","
       << diaChi << ","
       << soDienThoai << ","
       << email << ","
       << ngaySinh.toString() << ",";
}

void Nguoi::docTuFile(std::istream& is) {
    std::string line;
    std::getline(is, hoTen, ',');
    std::getline(is, cmnd_cccd, ',');
    std::getline(is, diaChi, ',');
    std::getline(is, soDienThoai, ',');
    std::getline(is, email, ',');

    std::string ngaySinhStr;
    std::getline(is, ngaySinhStr, ',');
    // Chuyển đổi chuỗi "dd/mm/yyyy" sang đối tượng Date
    // === BỌC BẢO VỆ (0): XỬ LÝ ĐỌC NGÀY AN TOÀN ===
    try {
        // Chuyển đổi chuỗi "dd/mm/yyyy" sang đối tượng Date
        int d, m, y;
        char slash1, slash2; // SUA LOI LOGIC: Can 2 bien
        std::stringstream ss(ngaySinhStr);
        ss >> d >> slash1 >> m >> slash2 >> y;

        // Kiem tra neu doc loi (chuoi rong/hong) hoac sai dinh dang
        if (ss.fail() || slash1 != '/' || slash2 != '/') {
            ngaySinh.setDate(1, 1, 1990); // Dat ngay mac dinh
        } else {
            ngaySinh.setDate(d, m, y);
        }
    } catch (const std::exception& e) {
        // Bat moi loi khac co the xay ra
        ngaySinh.setDate(1, 1, 1990); // Dat ngay mac dinh
    }
}

// Implement getters/setters
void Nguoi::setHoTen(const std::string& ten) {
    hoTen = ten;
}

std::string Nguoi::getHoTen() const {
    return hoTen;
}

void Nguoi::setDiaChi(const std::string& dc) {
    diaChi = dc;
}

std::string Nguoi::getDiaChi() const {
    return diaChi;
}
