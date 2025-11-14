#pragma once
#include "NhanVien.h"

using namespace std;

// Lớp NhanVienTheoGio (Hourly Employee)
class NVTheoGio : public NhanVien {
private:
    double mucLuongGio;
    double soGioLamTrongThang; // Sẽ được cập nhật từ module Chấm công

public:
    NVTheoGio(string ma = "", string ten = "", string cccd = "",
              string dc = "", string sdt = "", string mail = "",
              Date ns = Date(), Date nvl = Date(),
              TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
              string pb = "", string cd = "", 
              double luongGio = 0.0, double soGio = 0.0);
    
    virtual ~NVTheoGio();

    // Triển khai các hàm ảo
    virtual double tinhLuong() const override;
    virtual void hienThiThongTin() const override;
    virtual LoaiNhanVien getLoaiNV() const override;
    virtual void luuVaoFile(ostream& os) const override;
    virtual void docTuFile(istream& is) override;

    // Phương thức riêng
    void nhapThongTinRieng();
    void setMucLuongGio(double luong);
    void setSoGioLam(double gio);
};
