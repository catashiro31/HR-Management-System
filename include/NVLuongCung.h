#pragma once
#include "NhanVien.h"

using namespace std;

class NVLuongCung : public NhanVien {
private:
    double luongCoBan; 

public:
    NVLuongCung(string ma = "", string ten = "", string cccd = "",
                string dc = "", string sdt = "", string mail = "",
                Date ns = Date(), Date nvl = Date(),
                TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
                string pb = "", string cd = "", double luong = 0.0);
    
    virtual ~NVLuongCung();

    virtual double tinhLuong() const override;
    virtual void hienThiThongTin(Role vaiTro) const override;
    virtual void hienThiThongTinBang(Role vaiTro) const override; // <-- THÊM DÒNG NÀY
    virtual LoaiNhanVien getLoaiNV() const override;

    virtual void luuVaoFile(ostream& os) const override;
    virtual void docTuFile(istream& is) override;

    void nhapThongTinRieng();
    void setLuongCoBan(double luong);
    double getLuongCoBan() const;
};