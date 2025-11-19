#include "../include/ChucDanh.h"
#include "../include/Helper.h" 
#include <iostream>
#include <iomanip>
using namespace std;

ChucDanh::ChucDanh(const string& ma, const string& ten, double luong)
    : maChucDanh(ma), tenChucDanh(ten), luongCoBan(luong) {}

string ChucDanh::getMaChucDanh() const { return maChucDanh; }
string ChucDanh::getTenChucDanh() const { return tenChucDanh; }
double ChucDanh::getLuongCoBan() const { return luongCoBan; }

void ChucDanh::setTenChucDanh(const string& ten) { tenChucDanh = ten; }
void ChucDanh::setLuongCoBan(double luong) { luongCoBan = luong; }

void ChucDanh::hienThi() const {
    Helper helper; // <-- Phải tạo đối tượng
    cout << "| " << left << setw(8) << helper.removeVietnameseAccent(maChucDanh)
              << " | " << setw(27) << helper.removeVietnameseAccent(tenChucDanh)
              << " | " << right << setw(13) << helper.removeVietnameseAccent(helper.formatCurrency(luongCoBan)) << " VND |\n";
}

string ChucDanh::toStringCSV() const {
    stringstream ss;
    ss << maChucDanh << "," << tenChucDanh << "," << luongCoBan;
    return ss.str();
}