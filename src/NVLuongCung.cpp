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

// --- HÀM ĐƯỢC VIẾT LẠI HOÀN TOÀN ---
void NVLuongCung::hienThiThongTin(Role vaiTro) const {
    cout << "------------------------------------------\n";
    cout << left << setw(18) << "  Mã Nhân Viên:" << maNV << "\n"
              << setw(18) << "  Họ Tên:" << hoTen << "\n"
              << setw(18) << "  Loại NV:" << "Lương Cứng" << "\n"
              << setw(18) << "  Ngày Sinh:" << ngaySinh.toString() << "\n"
              << setw(18) << "  Email:" << email << "\n"
              << setw(18) << "  Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << setw(18) << "  Phòng Ban:" << maPhongBan << "\n"
              << setw(18) << "  Chức Danh:" << maChucDanh << "\n";

    // --- LOGIC PHÂN QUYỀN ---
    // Chỉ Chủ Tịch và Kế Toán mới thấy lương
    if (vaiTro == Role::CHU_TICH || vaiTro == Role::KE_TOAN) {
        cout << setw(18) << "  Lương Cơ Bản:" << Helper::formatCurrency(luongCoBan, true) << "\n";
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
    cout << "--- Nhập Thông Tin Lương Cứng ---\n";
    luongCoBan = Helper::nhapSoThuc(" - Nhập lương cơ bản (VND): ", 0);
}

void NVLuongCung::setLuongCoBan(double luong) { luongCoBan = luong; }
double NVLuongCung::getLuongCoBan() const { return luongCoBan; }