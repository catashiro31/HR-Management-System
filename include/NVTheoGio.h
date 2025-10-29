#pragma once
#include "NhanVien.h"

// Lớp NhanVienTheoGio (Hourly Employee)
class NVTheoGio : public NhanVien {
private:
    double mucLuongGio;
    double soGioLamTrongThang; // Sẽ được cập nhật từ module Chấm công

public:
    NVTheoGio(std::string ma = "", std::string ten = "", std::string cccd = "",
              std::string dc = "", std::string sdt = "", std::string mail = "",
              Date ns = Date(), Date nvl = Date(),
              TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
              std::string pb = "", std::string cd = "", 
              double luongGio = 0.0, double soGio = 0.0);
    
    virtual ~NVTheoGio();

    // Triển khai các hàm ảo
    virtual double tinhLuong() const override;
    virtual void hienThiThongTin() const override;
    virtual LoaiNhanVien getLoaiNV() const override;
    virtual void luuVaoFile(std::ostream& os) const override;
    virtual void docTuFile(std::istream& is) override;

    // Phương thức riêng
    void nhapThongTinRieng();
    void setMucLuongGio(double luong);
    void setSoGioLam(double gio);
};
