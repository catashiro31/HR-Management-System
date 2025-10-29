#include "../include/PhucLoi.h"
#include "../include/Helper.h" // Sẽ dùng cho formatCurrency
#include <iostream>
#include <iomanip>

PhucLoi::PhucLoi(const std::string& ma, const std::string& ten, double chiPhi)
    : maPhucLoi(ma), tenPhucLoi(ten), chiPhiHangThang(chiPhi) {}

std::string PhucLoi::getMaPhucLoi() const { return maPhucLoi; }
std::string PhucLoi::getTenPhucLoi() const { return tenPhucLoi; }
double PhucLoi::getChiPhiHangThang() const { return chiPhiHangThang; }

void PhucLoi::setTenPhucLoi(const std::string& ten) { tenPhucLoi = ten; }
void PhucLoi::setChiPhiHangThang(double chiPhi) { chiPhiHangThang = chiPhi; }

void PhucLoi::hienThi() const {
    std::cout << "| " << std::left << std::setw(10) << maPhucLoi
              << " | " << std::setw(30) << tenPhucLoi
              << " | " << std::right << std::setw(15) << Helper::formatCurrency(chiPhiHangThang) << " VND |\n";
}

std::string PhucLoi::toStringCSV() const {
    std::stringstream ss;
    ss << maPhucLoi << "," << tenPhucLoi << "," << chiPhiHangThang;
    return ss.str();
}