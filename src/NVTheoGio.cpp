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

// --- HÀM ĐƯỢC VIẾT LẠI HOÀN TOÀN ---
void NVTheoGio::hienThiThongTin(Role vaiTro) const {
    cout << "------------------------------------------\n";
    cout << left << setw(18) << "  Mã Nhân Viên:" << maNV << "\n"
              << setw(18) << "  Họ Tên:" << hoTen << "\n"
              << setw(18) << "  Loại NV:" << "Theo Giờ" << "\n"
              << setw(18) << "  Ngày Sinh:" << ngaySinh.toString() << "\n"
              << setw(18) << "  Email:" << email << "\n"
              << setw(18) << "  Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << setw(18) << "  Phòng Ban:" << maPhongBan << "\n"
              << setw(18) << "  Chức Danh:" << maChucDanh << "\n";

    // --- LOGIC PHÂN QUYỀN ---
    if (vaiTro == Role::CHU_TICH || vaiTro == Role::KE_TOAN) {
        cout << setw(18) << "  Mức Lương/Giờ:" << Helper::formatCurrency(mucLuongGio, true) << "\n"
             << setw(18) << "  Số Giờ Làm:" << soGioLamTrongThang << "\n";
    } else {
        cout << setw(18) << "  Mức Lương/Giờ:" << "[Bảo mật]" << "\n"
             << setw(18) << "  Số Giờ Làm:" << "[Bảo mật]" << "\n";
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
    cout << "--- Nhập Thông Tin Lương Theo Giờ ---\n";
    mucLuongGio = Helper::nhapSoThuc(" - Nhập mức lương theo giờ (VND): ", 0);
    soGioLamTrongThang = 0;
}
void NVTheoGio::setMucLuongGio(double luong) { mucLuongGio = luong; }
void NVTheoGio::setSoGioLam(double gio) { soGioLamTrongThang = gio; }