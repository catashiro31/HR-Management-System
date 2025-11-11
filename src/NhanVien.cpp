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

// Ghi đè hàm luuVaoFile
void NhanVien::luuVaoFile(ostream& os) const {
    // 1. Gọi hàm của lớp cha (Nguoi) để lưu thông tin chung
    Nguoi::luuVaoFile(os);
    
    // 2. Lưu thông tin riêng của NhanVien
    os << maNV << ","
       << ngayVaoLam.toString() << ","
       << static_cast<int>(trangThai) << "," // Lưu enum dưới dạng số
       << maPhongBan << ","
       << maChucDanh << ",";
}

// Ghi đè hàm docTuFile
void NhanVien::docTuFile(istream& is) {
    // 1. Gọi hàm của lớp cha (Nguoi) để đọc thông tin chung
    Nguoi::docTuFile(is);

    // 2. Đọc thông tin riêng của NhanVien
    getline(is, maNV, ',');
    
    string ngayVaoLamStr;
    getline(is, ngayVaoLamStr, ',');

    try {
        int d, m, y;
        char slash1, slash2; // Sửa lỗi logic (cần 2 biến slash)
        stringstream ss(ngayVaoLamStr);
        ss >> d >> slash1 >> m >> slash2 >> y;
        
        // Nếu stream bị lỗi (ví dụ: chuỗi rỗng) hoặc không đúng định dạng
        if (ss.fail() || slash1 != '/' || slash2 != '/') {
            ngayVaoLam.setDate(1, 1, 2000); // Đặt ngày mặc định
        } else {
            ngayVaoLam.setDate(d, m, y);
        }
    } catch (const exception& e) {
        ngayVaoLam.setDate(1, 1, 2000); // Đặt ngày mặc định nếu có lỗi
    }

    string trangThaiStr;
    getline(is, trangThaiStr, ',');

    try {
        // Lệnh stoi(trangThaiStr) sẽ gây crash nếu trangThaiStr là rỗng ""
        trangThai = static_cast<TrangThaiLamViec>(stoi(trangThaiStr));
    } catch (const exception& e) {
        // Nếu lỗi (do file hỏng hoặc dòng trống), đặt trạng thái mặc định
        trangThai = TrangThaiLamViec::THU_VIEC; 
        // cerr << "(!) Loi doc file: Trang thai khong hop le cho NV " << maNV << ". Dat mac dinh Thu Viec.\n";
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
    hoTen = Helper::nhapChuoi(" - Họ và tên: ");
    cmnd_cccd = Helper::nhapChuoi(" - Số CMND/CCCD: ");
    diaChi = Helper::nhapChuoi(" - Địa chỉ: ");
    soDienThoai = Helper::nhapChuoi(" - Số điện thoại: ");
    email = Helper::nhapChuoi(" - Email: ");

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
    trangThai = TrangThaiLamViec::THU_VIEC; // Mặc định là thử việc
    cout << " - Trạng thái ban đầu: Thử việc\n";
}
