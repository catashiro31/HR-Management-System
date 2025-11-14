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
void NVLuongCung::hienThiThongTin() const {
    cout << left << setw(15) << "Mã Nhân Viên:" << maNV << "\n"
              << setw(15) << "Họ Tên:" << hoTen << "\n"
              << setw(15) << "Ngày Sinh:" << ngaySinh << "\n"
              << setw(15) << "Địa Chỉ:" << diaChi << "\n"
              << setw(15) << "Email:" << email << "\n"
              << setw(15) << "Ngày Vào Làm:" << ngayVaoLam << "\n"
              << setw(15) << "Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << setw(15) << "Mã Phòng Ban:" << maPhongBan << "\n"
              << setw(15) << "Mã Chức Danh:" << maChucDanh << "\n"
              << setw(15) << "Loại NV:" << "Lương Cứng" << "\n"
              << setw(15) << "Lương Cơ Bản:" << fixed << setprecision(0) << luongCoBan << " VND\n";
    cout << "------------------------------------------\n";
}

LoaiNhanVien NVLuongCung::getLoaiNV() const {
    return LoaiNhanVien::LUONG_CUNG;
}

void NVLuongCung::luuVaoFile(ostream& os) const {
    // 1. Lưu loại nhân viên (QUAN TRỌNG)
    os << static_cast<int>(getLoaiNV()) << ",";
    
    // 2. Gọi hàm của lớp cha (NhanVien)
    NhanVien::luuVaoFile(os);
    
    // 3. Lưu trường riêng của lớp này
    os << luongCoBan << "\n"; // Kết thúc bằng newline
}

void NVLuongCung::docTuFile(istream& is) {
    NhanVien::docTuFile(is);
    string luongStr;
    getline(is, luongStr); 
    try {
        if (!luongStr.empty()) {
            // Lệnh stod co a gay loi neu luongStr khong phai la so
            luongCoBan = stod(luongStr); 
        } else {
            luongCoBan = 0; // Neu chuoi rong
        }
    } catch (const exception& e) {
        // Neu loi (vi du: chuoi la "abc"), dat mac dinh la 0
        luongCoBan = 0;
        // cerr << "(!) Loi doc file: Luong co ban khong hop le cho NV " << getMaNV() << ". Dat mac dinh 0.\n";
    }
}

void NVLuongCung::nhapThongTinRieng() {
    cout << "--- Nhập Thông Tin Lương Cứng ---\n";
    luongCoBan = Helper::nhapSoThuc(" - Nhập lương cơ bản (VND): ", 0);
}

void NVLuongCung::setLuongCoBan(double luong) {
    luongCoBan = luong;
}

double NVLuongCung::getLuongCoBan() const {
    return luongCoBan;
}
