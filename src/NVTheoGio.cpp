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
    // Giả định soGioLamTrongThang đã được cập nhật
    double luong = mucLuongGio * soGioLamTrongThang;
    // Có thể thêm logic tính OT (làm thêm giờ)
    return luong;
}

void NVTheoGio::hienThiThongTin() const {
    cout << left << setw(15) << "Mã Nhân Viên:" << maNV << "\n"
              << setw(15) << "Họ Tên:" << hoTen << "\n"
              << setw(15) << "Ngày Sinh:" << ngaySinh << "\n"
              << setw(15) << "Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << setw(15) << "Mã Phòng Ban:" << maPhongBan << "\n"
              << setw(15) << "Loại NV:" << "Theo Giờ" << "\n"
              << setw(15) << "Mức Lương/Giờ:" << fixed << setprecision(0) << mucLuongGio << " VND\n"
              << setw(15) << "Số Giờ Làm:" << fixed << setprecision(1) << soGioLamTrongThang << "\n";
    cout << "------------------------------------------\n";
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
    getline(is, soGioStr); // Đọc đến hết dòng

    // === BỌC BẢO VỆ (7): MỨC LƯƠNG GIỜ ===
    try {
        mucLuongGio = mucLuongStr.empty() ? 0.0 : stod(mucLuongStr);
    } catch (const exception& e) {
        mucLuongGio = 0.0; // Dat mac dinh neu loi
    }

    // === BỌC BẢO VỆ (8): SỐ GIỜ LÀM ===
    try {
        soGioLamTrongThang = soGioStr.empty() ? 0.0 : stod(soGioStr);
    } catch (const exception& e) {
        soGioLamTrongThang = 0.0; // Dat mac dinh neu loi
    }
}

void NVTheoGio::nhapThongTinRieng() {
    cout << "--- Nhập Thông Tin Lương Theo Giờ ---\n";
    mucLuongGio = Helper::nhapSoThuc(" - Nhập mức lương theo giờ (VND): ", 0);
    soGioLamTrongThang = 0; // Ban đầu chưa có
}

void NVTheoGio::setMucLuongGio(double luong) { mucLuongGio = luong; }
void NVTheoGio::setSoGioLam(double gio) { soGioLamTrongThang = gio; }
