#pragma once
#include "Nguoi.h"
#include "GlobalConfig.h" // <-- Cần cho Role
#include "PhongBan.h" 
#include "ChucDanh.h"

using namespace std;

// Forward declaration
class PhongBan;
class ChucDanh;

class NhanVien : public Nguoi {
protected:
    string maNV;
    Date ngayVaoLam;
    TrangThaiLamViec trangThai;
    string maPhongBan;
    string maChucDanh;

public:
    NhanVien(string ma = "", string ten = "", string cccd = "",
             string dc = "", string sdt = "", string mail = "",
             Date ns = Date(), Date nvl = Date(),
             TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
             string pb = "", string cd = "");
    virtual ~NhanVien();

    virtual double tinhLuong() const = 0; 
     
    // --- THAY ĐỔI ---
    virtual void hienThiThongTin(Role vaiTro) const = 0; 

    // Ghi đè (override) các hàm ảo từ lớp Nguoi
    virtual void hienThiThongTin() const override; // <-- Giữ tương thích
    virtual void luuVaoFile(ostream& os) const override;
    virtual void docTuFile(istream& is) override;

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

    void nhapThongTinCoBan(const string& maNV);
};