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

void NVHoaHong::hienThiThongTin() const {
    cout << left << setw(15) << "Mã Nhân Viên:" << maNV << "\n"
              << setw(15) << "Họ Tên:" << hoTen << "\n"
              << setw(15) << "Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << setw(15) << "Mã Phòng Ban:" << maPhongBan << "\n"
              << setw(15) << "Loại NV:" << "Hoa Hồng" << "\n"
              << setw(15) << "Lương Cơ Bản:" << fixed << setprecision(0) << luongCoBan << " VND\n"
              << setw(15) << "Tỷ Lệ HH:" << fixed << setprecision(2) << (tyLeHoaHong * 100) << "%\n"
              << setw(15) << "Doanh Số:" << fixed << setprecision(0) << doanhSoBanHang << " VND\n";
    cout << "------------------------------------------\n";
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
    getline(is, tyLeStr); // Đọc đến hết dòng

    // === BỌC BẢO VỆ (4): LƯƠNG CƠ BẢN ===
    try {
        luongCoBan = luongCBStr.empty() ? 0.0 : stod(luongCBStr);
    } catch (const exception& e) {
        luongCoBan = 0.0; // Dat mac dinh neu loi
    }

    // === BỌC BẢO VỆ (5): DOANH SỐ ===
    try {
        doanhSoBanHang = doanhSoStr.empty() ? 0.0 : stod(doanhSoStr);
    } catch (const exception& e) {
        doanhSoBanHang = 0.0; // Dat mac dinh neu loi
    }

    // === BỌC BẢO VỆ (6): TỶ LỆ ===
    try {
        tyLeHoaHong = tyLeStr.empty() ? 0.0 : stod(tyLeStr);
    } catch (const exception& e) {
        tyLeHoaHong = 0.0; // Dat mac dinh neu loi
    }
}

void NVHoaHong::nhapThongTinRieng() {
    cout << "--- Nhập Thông Tin Lương Hoa Hồng ---\n";
    luongCoBan = Helper::nhapSoThuc(" - Nhập lương cơ bản (VND): ", 0);
    tyLeHoaHong = Helper::nhapSoThuc(" - Nhập tỷ lệ hoa hồng (ví dụ: 0.05 cho 5%): ", 0.0);
    doanhSoBanHang = 0; // Ban đầu chưa có
}

void NVHoaHong::setDoanhSo(double doanhSo) { doanhSoBanHang = doanhSo; }
