#include "../include/PhucLoi.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip>
using namespace std;

PhucLoi::PhucLoi(const string& ma, const string& ten, double chiPhi)
    : maPhucLoi(ma), tenPhucLoi(ten), chiPhiHangThang(chiPhi) {}

string PhucLoi::getMaPhucLoi() const { return maPhucLoi; }
string PhucLoi::getTenPhucLoi() const { return tenPhucLoi; }
double PhucLoi::getChiPhiHangThang() const { return chiPhiHangThang; }

void PhucLoi::setTenPhucLoi(const string& ten) { tenPhucLoi = ten; }
void PhucLoi::setChiPhiHangThang(double chiPhi) { chiPhiHangThang = chiPhi; }

void PhucLoi::hienThi() const {
    Helper helper; // <-- Phải tạo đối tượng
    cout << "| " << left << setw(10) << helper.removeVietnameseAccent(maPhucLoi)
              << " | " << setw(32) << helper.removeVietnameseAccent(tenPhucLoi)
              << " | " << right << setw(13) << helper.removeVietnameseAccent(helper.formatCurrency(chiPhiHangThang)) << " VND |\n";
}

string PhucLoi::toStringCSV() const {
    stringstream ss;
    ss << maPhucLoi << "," << tenPhucLoi << "," << chiPhiHangThang;
    return ss.str();
}