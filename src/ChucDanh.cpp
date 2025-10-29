#include "../include/ChucDanh.h"
#include "../include/Helper.h" // Sẽ dùng cho formatCurrency
#include <iostream>
#include <iomanip>

ChucDanh::ChucDanh(const std::string& ma, const std::string& ten, double luong)
    : maChucDanh(ma), tenChucDanh(ten), luongCoBan(luong) {}

std::string ChucDanh::getMaChucDanh() const { return maChucDanh; }
std::string ChucDanh::getTenChucDanh() const { return tenChucDanh; }
double ChucDanh::getLuongCoBan() const { return luongCoBan; }

void ChucDanh::setTenChucDanh(const std::string& ten) { tenChucDanh = ten; }
void ChucDanh::setLuongCoBan(double luong) { luongCoBan = luong; }

void ChucDanh::hienThi() const {
    std::cout << "| " << std::left << std::setw(10) << maChucDanh
              << " | " << std::setw(25) << tenChucDanh
              << " | " << std::right << std::setw(15) << Helper::formatCurrency(luongCoBan) << " VND |\n";
}

std::string ChucDanh::toStringCSV() const {
    std::stringstream ss;
    ss << maChucDanh << "," << tenChucDanh << "," << luongCoBan;
    return ss.str();
}