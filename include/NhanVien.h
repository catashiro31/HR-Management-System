#pragma once
#include "Nguoi.h"
#include "GlobalConfig.h"
#include "PhongBan.h" // Cần forward declaration hoặc include
#include "ChucDanh.h"

using namespace std;

// Forward declaration để tránh lỗi include vòng
class PhongBan;
class ChucDanh;

// Lớp NhanVien (Employee) kế thừa từ Nguoi
// Thể hiện tính KẾ THỪA
// Đây cũng là một lớp TRỪU TƯỢNG vì có hàm ảo thuần túy
class NhanVien : public Nguoi {
protected:
    string maNV;
    Date ngayVaoLam;
    TrangThaiLamViec trangThai;
    
    string maPhongBan; // Mã phòng ban
    string maChucDanh; // Mã chức danh

    // Con trỏ đến đối tượng, sẽ được liên kết bởi lớp Database
    // PhongBan* phongBan; 
    // ChucDanh* chucDanh;

public:
    NhanVien(string ma = "", string ten = "", string cccd = "",
             string dc = "", string sdt = "", string mail = "",
             Date ns = Date(), Date nvl = Date(),
             TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
             string pb = "", string cd = "");

    virtual ~NhanVien();

    // = 0 bắt buộc lớp con phải định nghĩa (pure virtual)
    // Thể hiện tính ĐA HÌNH (Polymorphism)
    virtual double tinhLuong() const = 0; 
    
    // Hàm hienThiThongTin cũng là đa hình
    virtual void hienThiThongTin() const = 0; 

    // Ghi đè (override) các hàm ảo từ lớp Nguoi
    virtual void luuVaoFile(ostream& os) const override;
    virtual void docTuFile(istream& is) override;

    // Hàm ảo để lấy loại nhân viên (cần cho việc lưu/tải file)
    virtual LoaiNhanVien getLoaiNV() const = 0;

    // Getters/Setters
    string getMaNV() const;
    void setMaNV(const string& ma);
    void setTrangThai(TrangThaiLamViec tt);
    TrangThaiLamViec getTrangThai() const;
    string getMaPhongBan() const;
    void setMaPhongBan(const string& maPB);
    string getMaChucDanh() const;
    void setMaChucDanh(const string& maCD);

    // Hàm tiện ích để nhập thông tin
    // Hàm này không ảo vì nó chung cho tất cả
    void nhapThongTinCoBan(const string& maNV);
};
