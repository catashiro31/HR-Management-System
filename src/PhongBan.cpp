#include "../include/PhongBan.h"
#include <iostream>
#include <iomanip>

PhongBan::PhongBan(std::string ma, std::string ten, std::string maTP)
    : maPB(ma), tenPB(ten), maTruongPhong(maTP) {}

PhongBan::~PhongBan() {}

void PhongBan::hienThi() const {
    std::cout << "| " << std::left << std::setw(10) << maPB
              << "| " << std::setw(25) << tenPB
              << "| " << std::setw(15) << maTruongPhong << "|\n";
}

// Getters/Setters
std::string PhongBan::getMaPB() const { return maPB; }
std::string PhongBan::getTenPB() const { return tenPB; }
void PhongBan::setTenPB(const std::string& ten) { tenPB = ten; }
std::string PhongBan::getMaTruongPhong() const { return maTruongPhong; }
void PhongBan::setMaTruongPhong(const std::string& maNV) { maTruongPhong = maNV; }
 