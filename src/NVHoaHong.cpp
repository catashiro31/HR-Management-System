#include "../include/NVHoaHong.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip>
using namespace std;

NVHoaHong::NVHoaHong(string ma, string ten, string cccd,
                     string dc, string sdt, string mail,
                     Date ns, Date nvl, TrangThaiLamViec tt,
                     string pb, string cd, 
                     double luongCB, double doanhSo, double tyLe)
    : NhanVien(ma, ten, cccd, dc, sdt, mail, ns, nvl, tt, pb, cd), 
      luongCoBan(luongCB), doanhSoBanHang(doanhSo), tyLeHoaHong(tyLe) {}

NVHoaHong::~NVHoaHong() {}

double NVHoaHong::tinhLuong() const {
    return luongCoBan + (doanhSoBanHang * tyLeHoaHong);
}

// --- HÀM ĐƯỢC VIẾT LẠI HOÀN TOÀN ---
void NVHoaHong::hienThiThongTin(Role vaiTro) const {
    cout << "------------------------------------------\n";
    cout << left << setw(18) << "  Mã Nhân Viên:" << maNV << "\n"
              << setw(18) << "  Họ Tên:" << hoTen << "\n"
              << setw(18) << "  Loại NV:" << "Hoa Hồng" << "\n"
              << setw(18) << "  Ngày Sinh:" << ngaySinh.toString() << "\n"
              << setw(18) << "  Email:" << email << "\n"
              << setw(18) << "  Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << setw(18) << "  Phòng Ban:" << maPhongBan << "\n"
              << setw(18) << "  Chức Danh:" << maChucDanh << "\n";

    // --- LOGIC PHÂN QUYỀN ---
    if (vaiTro == Role::CHU_TICH || vaiTro == Role::KE_TOAN) {
        cout << setw(18) << "  Lương Cơ Bản:" << Helper::formatCurrency(luongCoBan, true) << "\n"
             << setw(18) << "  Tỷ Lệ HH:" << fixed << setprecision(2) << (tyLeHoaHong * 100) << "%\n"
             << setw(18) << "  Doanh Số:" << Helper::formatCurrency(doanhSoBanHang, true) << "\n";
    } else {
        cout << setw(18) << "  Lương Cơ Bản:" << "[Bảo mật]" << "\n"
             << setw(18) << "  Tỷ Lệ HH:" << "[Bảo mật]" << "\n"
             << setw(18) << "  Doanh Số:" << "[Bảo mật]" << "\n";
    }
}

LoaiNhanVien NVHoaHong::getLoaiNV() const {
    return LoaiNhanVien::HOA_HONG;
}

void NVHoaHong::luuVaoFile(ostream& os) const {
    os << static_cast<int>(getLoaiNV()) << ",";
    NhanVien::luuVaoFile(os);
    os << luongCoBan << ","
       << doanhSoBanHang << ","
       << tyLeHoaHong << "\n";
}
void NVHoaHong::docTuFile(istream& is) {
    NhanVien::docTuFile(is);
    string luongCBStr, doanhSoStr, tyLeStr;
    getline(is, luongCBStr, ',');
    getline(is, doanhSoStr, ',');
    getline(is, tyLeStr); 
    try { luongCoBan = luongCBStr.empty() ? 0.0 : stod(luongCBStr); } 
    catch (...) { luongCoBan = 0.0; }
    try { doanhSoBanHang = doanhSoStr.empty() ? 0.0 : stod(doanhSoStr); } 
    catch (...) { doanhSoBanHang = 0.0; }
    try { tyLeHoaHong = tyLeStr.empty() ? 0.0 : stod(tyLeStr); } 
    catch (...) { tyLeHoaHong = 0.0; }
}
void NVHoaHong::nhapThongTinRieng() {
    cout << "--- Nhập Thông Tin Lương Hoa Hồng ---\n";
    luongCoBan = Helper::nhapSoThuc(" - Nhập lương cơ bản (VND): ", 0);
    tyLeHoaHong = Helper::nhapSoThuc(" - Nhập tỷ lệ hoa hồng (ví dụ: 0.05 cho 5%): ", 0.0);
    doanhSoBanHang = 0;
}
void NVHoaHong::setDoanhSo(double doanhSo) { doanhSoBanHang = doanhSo; }