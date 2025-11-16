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

void NhanVien::hienThiThongTin() const {
    hienThiThongTin(Role::NHAN_VIEN);
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
    Date dateUtil; // <-- Phải tạo đối tượng
    ngayVaoLam = dateUtil.fromString(ngayVaoLamStr);
    
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
void NhanVien::nhapThongTinCoBan(const string& ma, bool yeuCauPhongBan) {
    Helper helper; 
    Date dateUtil; // <-- BẠN BỊ THIẾU DÒNG NÀY

    maNV = ma;
    cout << "--- Nhập Thông Tin Cơ Bản ---\n";
    hoTen = helper.nhapChuoi(" - Họ và tên (Không dấu, VD: Le Van Dung): ");
    cmnd_cccd = helper.nhapChuoiSo(" - Số CMND/CCCD: ");
    diaChi = helper.nhapChuoi(" - Địa chỉ: ");
    soDienThoai = helper.nhapChuoiSo(" - Số điện thoại: ");
    
    cout << " (Email sẽ được tạo tự động từ tên và ngày sinh)\n";

    // Nhập ngày sinh
    cout << " - Nhập ngày sinh (dd/mm/yyyy):\n";
    int d_ns = helper.nhapSoNguyen("   + Năm: ", 1950, 2010); 
    int m_ns = helper.nhapSoNguyen("   + Tháng: ", 1, 12);
    int maxDay_ns = dateUtil.soNgayTrongThang(m_ns, d_ns); // <-- Lỗi sẽ hết
    int n_ns = helper.nhapSoNguyen("   + Ngày: ", 1, maxDay_ns);
    ngaySinh.setDate(n_ns, m_ns, d_ns); 

    // Nhập ngày vào làm
    Date homNay = dateUtil.layNgayHienTai(); // <-- Lỗi sẽ hết
    cout << " - Nhập ngày vào làm (dd/mm/yyyy) [Hôm nay là " << homNay << "]:\n";
    
    while (true) {
        int y = helper.nhapSoNguyen("   + Năm: ", 2000, 2100); 
        int m = helper.nhapSoNguyen("   + Tháng: ", 1, 12);
        int maxDay = dateUtil.soNgayTrongThang(m, y); // <-- Lỗi sẽ hết
        int d = helper.nhapSoNguyen("   + Ngày: ", 1, maxDay); 

        Date ngayNhap(d, m, y); 

        if (ngayNhap <= homNay) {
            ngayVaoLam.setDate(d, m, y); 
            break; 
        } else {
            cout << " (!) Lỗi: Ngày vào làm không được sau ngày hôm nay (" << homNay << "). Vui lòng nhập lại.\n";
        }
    }

    if (yeuCauPhongBan) {
        maPhongBan = helper.nhapChuoi(" - Mã phòng ban (ví dụ: PB01): ");
    } else {
        maPhongBan = "KETOAN"; 
        cout << " - Phòng ban: KETOAN (Mặc định)\n";
    }

    maChucDanh = helper.nhapChuoi(" - Mã chức danh (ví dụ: CD01): ");
    trangThai = TrangThaiLamViec::THU_VIEC;
    cout << " - Trạng thái ban đầu: Thử việc\n";
}