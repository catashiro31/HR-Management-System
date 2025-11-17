#include "../include/NVTheoGio.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip>
using namespace std;

NVTheoGio::NVTheoGio(string ma, string ten, string cccd,
                     string dc, string sdt, string mail,
                     Date ns, Date nvl, TrangThaiLamViec tt,
                     string pb, string cd, 
                     double luongGio, double soGio)
    : NhanVien(ma, ten, cccd, dc, sdt, mail, ns, nvl, tt, pb, cd), 
      mucLuongGio(luongGio), soGioLamTrongThang(soGio) {}

NVTheoGio::~NVTheoGio() {}

double NVTheoGio::tinhLuong() const {
    return mucLuongGio * soGioLamTrongThang;
}

void NVTheoGio::hienThiThongTin(Role vaiTro) const {
    Helper helper; // <-- Phải tạo đối tượng

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
        cout << left << setw(18) << helper.removeVietnameseAccent("  Mức Lương/Giờ:") << helper.formatCurrency(mucLuongGio, true) << "\n"
             << left << setw(18) << helper.removeVietnameseAccent("  Số Giờ Làm:") << soGioLamTrongThang << "\n";
    } else {
        cout << left << setw(18) << helper.removeVietnameseAccent("  Mức Lương/Giờ:") << helper.removeVietnameseAccent("[Bảo mật]") << "\n"
             << left << setw(18) << helper.removeVietnameseAccent("  Số Giờ Làm:") << helper.removeVietnameseAccent("[Bảo mật]") << "\n";
    }
}

LoaiNhanVien NVTheoGio::getLoaiNV() const {
    return LoaiNhanVien::THEO_GIO;
}

void NVTheoGio::luuVaoFile(ostream& os) const {
    os << static_cast<int>(getLoaiNV()) << ",";
    NhanVien::luuVaoFile(os);
    os << mucLuongGio << ","
       << soGioLamTrongThang << "\n";
}
void NVTheoGio::docTuFile(istream& is) {
    NhanVien::docTuFile(is);
    string mucLuongStr, soGioStr;
    getline(is, mucLuongStr, ',');
    getline(is, soGioStr);
    try { mucLuongGio = mucLuongStr.empty() ? 0.0 : stod(mucLuongStr); } 
    catch (...) { mucLuongGio = 0.0; }
    try { soGioLamTrongThang = soGioStr.empty() ? 0.0 : stod(soGioStr); } 
    catch (...) { soGioLamTrongThang = 0.0; }
}
void NVTheoGio::nhapThongTinRieng() {
    Helper helper; // <-- Phải tạo đối tượng
    cout << "--- Nhập Thông Tin Lương Theo Giờ ---\n";
    mucLuongGio = helper.nhapSoThuc(" - Nhập mức lương theo giờ (VND): ", 0);
    soGioLamTrongThang = 0;
}
void NVTheoGio::setMucLuongGio(double luong) { mucLuongGio = luong; }
void NVTheoGio::setSoGioLam(double gio) { soGioLamTrongThang = gio; }
void NVTheoGio::hienThiThongTinBang(Role vaiTro) const {
    Helper helper;
    cout << "| " << left << setw(10) << helper.removeVietnameseAccent(maNV)
         << " | " << setw(30) << helper.removeVietnameseAccent(hoTen)
         << " | " << setw(15) << helper.removeVietnameseAccent("Theo Giờ")
         << " | " << setw(40) << helper.removeVietnameseAccent(email)
         << " | " << setw(15) << helper.removeVietnameseAccent(helper.trangThaiToString(trangThai))
         << " | " << setw(10) << helper.removeVietnameseAccent(maPhongBan)
         << " | " << setw(10) << helper.removeVietnameseAccent(maChucDanh) << " |" << "\n";
}