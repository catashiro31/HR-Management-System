#pragma once
#include "Nguoi.h"
#include "GlobalConfig.h"
#include "PhongBan.h" 
#include "ChucDanh.h"

// Forward declaration để tránh lỗi include vòng
class PhongBan;
class ChucDanh;

// Lớp NhanVien (Employee) kế thừa từ Nguoi
// Thể hiện tính KẾ THỪA
// Đây cũng là một lớp TRỪU TƯỢNG vì có hàm ảo thuần túy
class NhanVien : public Nguoi {
protected:
    std::string maNV;
    Date ngayVaoLam;
    TrangThaiLamViec trangThai;
    
    std::string maPhongBan; // Mã phòng ban
    std::string maChucDanh; // Mã chức danh

    // Con trỏ đến đối tượng, sẽ được liên kết bởi lớp Database
    // PhongBan* phongBan; 
    // ChucDanh* chucDanh;

public:
    NhanVien(std::string ma = "", std::string ten = "", std::string cccd = "",
             std::string dc = "", std::string sdt = "", std::string mail = "",
             Date ns = Date(), Date nvl = Date(),
             TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
             std::string pb = "", std::string cd = "");

    virtual ~NhanVien();

    // = 0 bắt buộc lớp con phải định nghĩa (pure virtual)
    // Thể hiện tính ĐA HÌNH (Polymorphism)
    virtual double tinhLuong() const = 0; 
    
    // Hàm hienThiThongTin cũng là đa hình
    virtual void hienThiThongTin() const = 0; 

    // Ghi đè (override) các hàm ảo từ lớp Nguoi
    virtual void luuVaoFile(std::ostream& os) const override;
    virtual void docTuFile(std::istream& is) override;

    // Hàm ảo để lấy loại nhân viên (cần cho việc lưu/tải file)
    virtual LoaiNhanVien getLoaiNV() const = 0;

    // Getters/Setters
    std::string getMaNV() const;
    void setMaNV(const std::string& ma);
    void setTrangThai(TrangThaiLamViec tt);
    TrangThaiLamViec getTrangThai() const;
    std::string getMaPhongBan() const;
    void setMaPhongBan(const std::string& maPB);
    std::string getMaChucDanh() const;
    void setMaChucDanh(const std::string& maCD);

    // Hàm tiện ích để nhập thông tin
    // Hàm này không ảo vì nó chung cho tất cả
    void nhapThongTinCoBan(const std::string& maNV);
};
