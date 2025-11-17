#include "../include/PhongBan.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip>
using namespace std;

PhongBan::PhongBan(string ma, string ten, string maTP)
    : maPB(ma), tenPB(ten), maTruongPhong(maTP) {}

PhongBan::~PhongBan() {}

void PhongBan::hienThi() const {
    Helper helper;
    cout << "| " << left << setw(8) << helper.removeVietnameseAccent(maPB)
              << " | " << setw(27) << helper.removeVietnameseAccent(tenPB)
              << " | " << setw(15) << helper.removeVietnameseAccent(maTruongPhong) << " |\n";
}

// Getters/Setters
string PhongBan::getMaPB() const { return maPB; }
string PhongBan::getTenPB() const { return tenPB; }
void PhongBan::setTenPB(const string& ten) { tenPB = ten; }
string PhongBan::getMaTruongPhong() const { return maTruongPhong; }
void PhongBan::setMaTruongPhong(const string& maNV) { maTruongPhong = maNV; }
