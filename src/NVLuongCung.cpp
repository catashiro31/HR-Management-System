#include "../include/NVLuongCung.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip>

NVLuongCung::NVLuongCung(std::string ma, std::string ten, std::string cccd,
                         std::string dc, std::string sdt, std::string mail,
                         Date ns, Date nvl, TrangThaiLamViec tt,
                         std::string pb, std::string cd, double luong)
    : NhanVien(ma, ten, cccd, dc, sdt, mail, ns, nvl, tt, pb, cd), luongCoBan(luong) {}

NVLuongCung::~NVLuongCung() {}

// Định nghĩa hàm tính lương
double NVLuongCung::tinhLuong() const {
    // Logic tính lương cứng (có thể phức tạp hơn)
    // Ví dụ: Lương = luongCoBan - BHXH - Thue TNCN...
    // Tạm thời trả về lương cơ bản
    return luongCoBan;
}

// Định nghĩa hàm hiển thị
void NVLuongCung::hienThiThongTin() const {
    std::cout << std::left << std::setw(15) << "Mã Nhân Viên:" << maNV << "\n"
              << std::setw(15) << "Họ Tên:" << hoTen << "\n"
              << std::setw(15) << "Ngày Sinh:" << ngaySinh << "\n"
              << std::setw(15) << "Địa Chỉ:" << diaChi << "\n"
              << std::setw(15) << "Email:" << email << "\n"
              << std::setw(15) << "Ngày Vào Làm:" << ngayVaoLam << "\n"
              << std::setw(15) << "Trạng Thái:" << Helper::trangThaiToString(trangThai) << "\n"
              << std::setw(15) << "Mã Phòng Ban:" << maPhongBan << "\n"
              << std::setw(15) << "Mã Chức Danh:" << maChucDanh << "\n"
              << std::setw(15) << "Loại NV:" << "Lương Cứng" << "\n"
              << std::setw(15) << "Lương Cơ Bản:" << std::fixed << std::setprecision(0) << luongCoBan << " VND\n";
    std::cout << "------------------------------------------\n";
}

LoaiNhanVien NVLuongCung::getLoaiNV() const {
    return LoaiNhanVien::LUONG_CUNG;
}

void NVLuongCung::luuVaoFile(std::ostream& os) const {
    // 1. Lưu loại nhân viên (QUAN TRỌNG)
    os << static_cast<int>(getLoaiNV()) << ",";
    
    // 2. Gọi hàm của lớp cha (NhanVien)
    NhanVien::luuVaoFile(os);
    
    // 3. Lưu trường riêng của lớp này
    os << luongCoBan << "\n"; // Kết thúc bằng newline
}

void NVLuongCung::docTuFile(std::istream& is) {
    // Loại nhân viên đã được đọc ở lớp Database
    
    // 1. Gọi hàm của lớp cha (NhanVien)
    NhanVien::docTuFile(is);

    // 2. Đọc trường riêng
    std::string luongStr;
    std::getline(is, luongStr); // Đọc đến hết dòng
    try {
        if (!luongStr.empty()) {
            // Lệnh stod co a gay loi neu luongStr khong phai la so
            luongCoBan = std::stod(luongStr); 
        } else {
            luongCoBan = 0; // Neu chuoi rong
        }
    } catch (const std::exception& e) {
        // Neu loi (vi du: chuoi la "abc"), dat mac dinh la 0
        luongCoBan = 0;
        // std::cerr << "(!) Loi doc file: Luong co ban khong hop le cho NV " << getMaNV() << ". Dat mac dinh 0.\n";
    }
}

void NVLuongCung::nhapThongTinRieng() {
    std::cout << "--- Nhập Thông Tin Lương Cứng ---\n";
    luongCoBan = Helper::nhapSoThuc(" - Nhập lương cơ bản (VND): ", 0);
}

void NVLuongCung::setLuongCoBan(double luong) {
    luongCoBan = luong;
}

double NVLuongCung::getLuongCoBan() const {
    return luongCoBan;
}
