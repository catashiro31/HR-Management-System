#include "../include/NVTheoGio.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip>

NVTheoGio::NVTheoGio(std::string ma, std::string ten, std::string cccd,
                     std::string dc, std::string sdt, std::string mail,
                     Date ns, Date nvl, TrangThaiLamViec tt,
                     std::string pb, std::string cd, 
                     double luongGio, double soGio)
    : NhanVien(ma, ten, cccd, dc, sdt, mail, ns, nvl, tt, pb, cd), 
      mucLuongGio(luongGio), soGioLamTrongThang(soGio) {}

NVTheoGio::~NVTheoGio() {}

double NVTheoGio::tinhLuong() const {
    // Giả định soGioLamTrongThang đã được cập nhật
    double luong = mucLuongGio * soGioLamTrongThang;
    // Có thể thêm logic tính OT (làm thêm giờ)
    return luong;
}

void NVTheoGio::hienThiThongTin() const {
    std::cout << std::left << std::setw(15) << "Mã Nhân Viên:" << maNV << "\n"
              << std::setw(15) << "Họ Tên:" << hoTen << "\n"
              << std::setw(15) << "Ngày Sinh:" << ngaySinh << "\n"
              << std::setw(15) << "Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << std::setw(15) << "Mã Phòng Ban:" << maPhongBan << "\n"
              << std::setw(15) << "Loại NV:" << "Theo Giờ" << "\n"
              << std::setw(15) << "Mức Lương/Giờ:" << std::fixed << std::setprecision(0) << mucLuongGio << " VND\n"
              << std::setw(15) << "Số Giờ Làm:" << std::fixed << std::setprecision(1) << soGioLamTrongThang << "\n";
    std::cout << "------------------------------------------\n";
}

LoaiNhanVien NVTheoGio::getLoaiNV() const {
    return LoaiNhanVien::THEO_GIO;
}

void NVTheoGio::luuVaoFile(std::ostream& os) const {
    os << static_cast<int>(getLoaiNV()) << ",";
    NhanVien::luuVaoFile(os);
    os << mucLuongGio << ","
       << soGioLamTrongThang << "\n";
}

void NVTheoGio::docTuFile(std::istream& is) {
    NhanVien::docTuFile(is);
    std::string mucLuongStr, soGioStr;
    
    std::getline(is, mucLuongStr, ',');
    std::getline(is, soGioStr); // Đọc đến hết dòng

    mucLuongGio = mucLuongStr.empty() ? 0.0 : std::stod(mucLuongStr);
    soGioLamTrongThang = soGioStr.empty() ? 0.0 : std::stod(soGioStr);
}

void NVTheoGio::nhapThongTinRieng() {
    std::cout << "--- Nhập Thông Tin Lương Theo Giờ ---\n";
    mucLuongGio = Helper::nhapSoThuc(" - Nhập mức lương theo giờ (VND): ", 0);
    soGioLamTrongThang = 0; // Ban đầu chưa có
}

void NVTheoGio::setMucLuongGio(double luong) { mucLuongGio = luong; }
void NVTheoGio::setSoGioLam(double gio) { soGioLamTrongThang = gio; }
