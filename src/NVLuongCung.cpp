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
    Helper helper; // <-- Phải tạo đối tượng

    cout << "------------------------------------------\n";
    cout << left << setw(18) << "  Mã Nhân Viên:" << maNV << "\n"
              << setw(18) << "  Họ Tên:" << hoTen << "\n"
              << setw(18) << "  Loại NV:" << "Lương Cứng" << "\n"
              << setw(18) << "  Ngày Sinh:" << ngaySinh.toString() << "\n"
              << setw(18) << "  Email:" << email << "\n"
              << setw(18) << "  Trạng Thái:" << helper.trangThaiToString(trangThai) << "\n"
              << setw(18) << "  Phòng Ban:" << maPhongBan << "\n"
              << setw(18) << "  Chức Danh:" << maChucDanh << "\n";

    if (vaiTro == Role::CHU_TICH || vaiTro == Role::KE_TOAN) {
        cout << setw(18) << "  Lương Cơ Bản:" << helper.formatCurrency(luongCoBan, true) << "\n";
    } else {
        cout << setw(18) << "  Lương Cơ Bản:" << "[Bảo mật]" << "\n";
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
    Helper helper; // <-- Phải tạo đối tượng
    cout << "--- Nhập Thông Tin Lương Cứng ---\n";
    luongCoBan = helper.nhapSoThuc(" - Nhập lương cơ bản (VND): ", 0);
}

void NVLuongCung::setLuongCoBan(double luong) { luongCoBan = luong; }
double NVLuongCung::getLuongCoBan() const { return luongCoBan; }
void NVLuongCung::hienThiThongTinBang(Role vaiTro) const {
    Helper helper;
    cout << "| " << left << setw(10) << maNV
         << " | "<< left  << setw(25) << hoTen
         << " | "<< left<< setw(20) << "Lương Cứng"
         << " | "<< left<< setw(40) << email
         << " | "<< left<< setw(20) << helper.trangThaiToString(trangThai)
         << " | "<< left<< setw(10) << maPhongBan
         << " | "<< left << setw(10) << maChucDanh << " |" << "\n";
} 