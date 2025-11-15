#include "../include/NhanVien.h"
#include "../include/Helper.h"
#include <iostream>
#include <iomanip> 
#include <sstream> 
using namespace std;

NhanVien::NhanVien(string ma, string ten, string cccd,
                   string dc, string sdt, string mail,
                   Date ns, Date nvl, TrangThaiLamViec tt,
                   string pb, string cd)
    : Nguoi(ten, cccd, dc, sdt, mail, ns),
      maNV(ma), ngayVaoLam(nvl), trangThai(tt), maPhongBan(pb), maChucDanh(cd) {}

NhanVien::~NhanVien() {}

// Hàm tạm để giữ tương thích (sẽ bị xóa)
void NhanVien::hienThiThongTin() const {
    hienThiThongTin(Role::NHAN_VIEN); // Mặc định xem ở quyền thấp nhất
}

void NhanVien::luuVaoFile(ostream& os) const {
    Nguoi::luuVaoFile(os);
    os << maNV << ","
       << ngayVaoLam.toString() << ","
       << static_cast<int>(trangThai) << ","
       << maPhongBan << ","
       << maChucDanh << ",";
}

void NhanVien::docTuFile(istream& is) {
    Nguoi::docTuFile(is);
    getline(is, maNV, ',');
    string ngayVaoLamStr;
    getline(is, ngayVaoLamStr, ',');
    ngayVaoLam = Date::fromString(ngayVaoLamStr);
    
    string trangThaiStr;
    getline(is, trangThaiStr, ',');
    try {
        if (trangThaiStr.empty()) {
            trangThai = TrangThaiLamViec::KHONG_XAC_DINH;
        } else {
            trangThai = static_cast<TrangThaiLamViec>(stoi(trangThaiStr));
        }
    } catch (...) {
        trangThai = TrangThaiLamViec::KHONG_XAC_DINH; 
    }
    
    getline(is, maPhongBan, ',');
    getline(is, maChucDanh, ',');
}

// Getters/Setters
string NhanVien::getMaNV() const { return maNV; }
void NhanVien::setMaNV(const string& ma) { maNV = ma; }
TrangThaiLamViec NhanVien::getTrangThai() const { return trangThai; }
void NhanVien::setTrangThai(TrangThaiLamViec tt) { trangThai = tt; }
string NhanVien::getMaPhongBan() const { return maPhongBan; }
void NhanVien::setMaPhongBan(const string& maPB) { maPhongBan = maPB; }
string NhanVien::getMaChucDanh() const { return maChucDanh; }
void NhanVien::setMaChucDanh(const string& maCD) { maChucDanh = maCD; }

// Hàm nhập thông tin chung
void NhanVien::nhapThongTinCoBan(const string& ma) {
    maNV = ma;
    cout << "--- Nhập Thông Tin Cơ Bản ---\n";
    Helper::inputName(hoTen);
    cmnd_cccd = Helper::nhapChuoi(" - Số CMND/CCCD: ");
    diaChi = Helper::nhapChuoi(" - Địa chỉ: ");
    soDienThoai = Helper::nhapChuoi(" - Số điện thoại: ");
    
    cout << " (Email sẽ được tạo tự động từ tên và ngày sinh)\n";

    // Nhập ngày sinh
    cout << " - Nhập ngày sinh (dd/mm/yyyy):\n";
    int d = Helper::nhapSoNguyen("   + Ngày: ", 1, 31);
    int m = Helper::nhapSoNguyen("   + Tháng: ", 1, 12);
    int y = Helper::nhapSoNguyen("   + Năm: ", 1920, 2010);
    ngaySinh.setDate(d, m, y);

    // Nhập ngày vào làm
    Date homNay = Date::layNgayHienTai();
    cout << " - Nhập ngày vào làm (dd/mm/yyyy) [Hôm nay là " << homNay << "]:\n";
    d = Helper::nhapSoNguyen("   + Ngày: ", 1, 31);
    m = Helper::nhapSoNguyen("   + Tháng: ", 1, 12);
    y = Helper::nhapSoNguyen("   + Năm: ", 2000, 2025);
    ngayVaoLam.setDate(d, m, y);

    maPhongBan = Helper::nhapChuoi(" - Mã phòng ban (ví dụ: PB01): ");
    maChucDanh = Helper::nhapChuoi(" - Mã chức danh (ví dụ: CD01): ");
    trangThai = TrangThaiLamViec::THU_VIEC;
    cout << " - Trạng thái ban đầu: Thử việc\n";
}