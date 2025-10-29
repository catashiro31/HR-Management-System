#include "../include/NVHoaHong.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip>

NVHoaHong::NVHoaHong(std::string ma, std::string ten, std::string cccd,
                     std::string dc, std::string sdt, std::string mail,
                     Date ns, Date nvl, TrangThaiLamViec tt,
                     std::string pb, std::string cd, 
                     double luongCB, double doanhSo, double tyLe)
    : NhanVien(ma, ten, cccd, dc, sdt, mail, ns, nvl, tt, pb, cd), 
      luongCoBan(luongCB), doanhSoBanHang(doanhSo), tyLeHoaHong(tyLe) {}

NVHoaHong::~NVHoaHong() {}

double NVHoaHong::tinhLuong() const {
    return luongCoBan + (doanhSoBanHang * tyLeHoaHong);
}

void NVHoaHong::hienThiThongTin() const {
    std::cout << std::left << std::setw(15) << "Mã Nhân Viên:" << maNV << "\n"
              << std::setw(15) << "Họ Tên:" << hoTen << "\n"
              << std::setw(15) << "Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << std::setw(15) << "Mã Phòng Ban:" << maPhongBan << "\n"
              << std::setw(15) << "Loại NV:" << "Hoa Hồng" << "\n"
              << std::setw(15) << "Lương Cơ Bản:" << std::fixed << std::setprecision(0) << luongCoBan << " VND\n"
              << std::setw(15) << "Tỷ Lệ HH:" << std::fixed << std::setprecision(2) << (tyLeHoaHong * 100) << "%\n"
              << std::setw(15) << "Doanh Số:" << std::fixed << std::setprecision(0) << doanhSoBanHang << " VND\n";
    std::cout << "------------------------------------------\n";
}

LoaiNhanVien NVHoaHong::getLoaiNV() const {
    return LoaiNhanVien::HOA_HONG;
}

void NVHoaHong::luuVaoFile(std::ostream& os) const {
    os << static_cast<int>(getLoaiNV()) << ",";
    NhanVien::luuVaoFile(os);
    os << luongCoBan << ","
       << doanhSoBanHang << ","
       << tyLeHoaHong << "\n";
}

void NVHoaHong::docTuFile(std::istream& is) {
    NhanVien::docTuFile(is);
    std::string luongCBStr, doanhSoStr, tyLeStr;
    
    std::getline(is, luongCBStr, ',');
    std::getline(is, doanhSoStr, ',');
    std::getline(is, tyLeStr); // Đọc đến hết dòng

    luongCoBan = luongCBStr.empty() ? 0.0 : std::stod(luongCBStr);
    doanhSoBanHang = doanhSoStr.empty() ? 0.0 : std::stod(doanhSoStr);
    tyLeHoaHong = tyLeStr.empty() ? 0.0 : std::stod(tyLeStr);
}

void NVHoaHong::nhapThongTinRieng() {
    std::cout << "--- Nhập Thông Tin Lương Hoa Hồng ---\n";
    luongCoBan = Helper::nhapSoThuc(" - Nhập lương cơ bản (VND): ", 0);
    tyLeHoaHong = Helper::nhapSoThuc(" - Nhập tỷ lệ hoa hồng (ví dụ: 0.05 cho 5%): ", 0.0);
    doanhSoBanHang = 0; // Ban đầu chưa có
}

void NVHoaHong::setDoanhSo(double doanhSo) { doanhSoBanHang = doanhSo; }
