#include "../include/NVLuongCung.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip>
using namespace std;

NVLuongCung::NVLuongCung(string ma, string ten, string cccd,
                         string dc, string sdt, string mail,
                         Date ns, Date nvl, TrangThaiLamViec tt,
                         string pb, string cd, double luong)
    : NhanVien(ma, ten, cccd, dc, sdt, mail, ns, nvl, tt, pb, cd), luongCoBan(luong) {}

NVLuongCung::~NVLuongCung() {}

double NVLuongCung::tinhLuong() const {
    return luongCoBan;
}

void NVLuongCung::hienThiThongTin(Role vaiTro) const {
    Helper helper; 

    cout << "------------------------------------------\n";
    cout << left << setw(18) << helper.removeVietnameseAccent("  Mã Nhân Viên:") << helper.removeVietnameseAccent(maNV) << "\n"
         << left << setw(18) << helper.removeVietnameseAccent("  Họ Tên:") << helper.removeVietnameseAccent(hoTen) << "\n"
         << left << setw(18) << helper.removeVietnameseAccent("  Loại NV:") << helper.removeVietnameseAccent("Theo Giờ") << "\n"
         << left << setw(18) << helper.removeVietnameseAccent("  Ngày Sinh:") << helper.removeVietnameseAccent(ngaySinh.toString()) << "\n"
         << left << setw(18) << helper.removeVietnameseAccent("  Email:") << helper.removeVietnameseAccent(email) << "\n"
         << left << setw(18) << helper.removeVietnameseAccent("  Trạng Thái:") << helper.removeVietnameseAccent(helper.trangThaiToString(trangThai)) << "\n"
         << left << setw(18) << helper.removeVietnameseAccent("  Phòng Ban:") << helper.removeVietnameseAccent(maPhongBan) << "\n"
         << left << setw(18) << helper.removeVietnameseAccent("  Chức Danh:") << helper.removeVietnameseAccent(maChucDanh) << "\n";

    if (vaiTro == Role::CHU_TICH || vaiTro == Role::KE_TOAN) {
        cout << setw(18) << helper.removeVietnameseAccent("  Lương Cơ Bản: ") << helper.formatCurrency(luongCoBan, true) << "\n";
    } else {
        cout << setw(18) << helper.removeVietnameseAccent("  Lương Cơ Bản:") << helper.removeVietnameseAccent("[Bảo mật]") << "\n";
    }
}

LoaiNhanVien NVLuongCung::getLoaiNV() const {
    return LoaiNhanVien::LUONG_CUNG;
}

void NVLuongCung::luuVaoFile(ostream& os) const {
    os << static_cast<int>(getLoaiNV()) << ",";
    NhanVien::luuVaoFile(os);
    os << luongCoBan << "\n"; 
}

void NVLuongCung::docTuFile(istream& is) {
    NhanVien::docTuFile(is);
    string luongStr;
    getline(is, luongStr); 
    try {
        luongCoBan = luongStr.empty() ? 0.0 : stod(luongStr);
    } catch (...) {
        luongCoBan = 0;
    }
}

void NVLuongCung::nhapThongTinRieng() {
    Helper helper;
    cout << "--- Nhập Thông Tin Lương Cứng ---\n";
    luongCoBan = helper.nhapSoThuc(" - Nhập lương cơ bản (VND): ", 0);
}

void NVLuongCung::setLuongCoBan(double luong) { luongCoBan = luong; }
double NVLuongCung::getLuongCoBan() const { return luongCoBan; }
void NVLuongCung::hienThiThongTinBang(Role vaiTro) const {
    Helper helper;
    cout << "| " << left << setw(10) << helper.removeVietnameseAccent(maNV)
         << " | "<< left  << setw(30) << helper.removeVietnameseAccent(hoTen)
         << " | "<< left<< setw(15) << helper.removeVietnameseAccent("Lương Cứng")
         << " | "<< left<< setw(40) << helper.removeVietnameseAccent(email)
         << " | "<< left<< setw(15) << helper.removeVietnameseAccent(helper.trangThaiToString(trangThai))
         << " | "<< left<< setw(10) << helper.removeVietnameseAccent(maPhongBan)
         << " | "<< left << setw(10) << helper.removeVietnameseAccent(maChucDanh) << " |" << "\n";
} 