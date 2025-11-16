#pragma once
#include "NhanVien.h"

using namespace std;

class NVHoaHong : public NhanVien {
private:
    double luongCoBan; 
    double doanhSoBanHang; 
    double tyLeHoaHong; 

public:
    NVHoaHong(string ma = "", string ten = "", string cccd = "",
              string dc = "", string sdt = "", string mail = "",
              Date ns = Date(), Date nvl = Date(),
              TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
              string pb = "", string cd = "", 
              double luongCB = 0.0, double doanhSo = 0.0, double tyLe = 0.0);
    
    virtual ~NVHoaHong();

    virtual double tinhLuong() const override;
    virtual void hienThiThongTin(Role vaiTro) const override;
    virtual void hienThiThongTinBang(Role vaiTro) const override; // <-- THÊM DÒNG NÀY
    virtual LoaiNhanVien getLoaiNV() const override;
    virtual void luuVaoFile(ostream& os) const override;
    virtual void docTuFile(istream& is) override;

    void nhapThongTinRieng();
    void setDoanhSo(double doanhSo);
};