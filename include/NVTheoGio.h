#pragma once
#include "NhanVien.h"

using namespace std;

class NVTheoGio : public NhanVien {
private:
    double mucLuongGio;
    double soGioLamTrongThang; 

public:
    NVTheoGio(string ma = "", string ten = "", string cccd = "",
              string dc = "", string sdt = "", string mail = "",
              Date ns = Date(), Date nvl = Date(),
              TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
              string pb = "", string cd = "", 
              double luongGio = 0.0, double soGio = 0.0);
    
    virtual ~NVTheoGio();

    virtual double tinhLuong() const override;
    virtual void hienThiThongTin(Role vaiTro) const override;
    virtual void hienThiThongTinBang(Role vaiTro) const override; // <-- THÊM DÒNG NÀY
    virtual LoaiNhanVien getLoaiNV() const override;
    virtual void luuVaoFile(ostream& os) const override;
    virtual void docTuFile(istream& is) override;

    void nhapThongTinRieng();
    void setMucLuongGio(double luong);
    void setSoGioLam(double gio);
};