#pragma once
#include "NhanVien.h"

using namespace std;


class NVLuongCung : public NhanVien {
private:
    double luongCoBan; // Lương cứng hàng tháng

public:
    NVLuongCung(string ma = "", string ten = "", string cccd = "",
                string dc = "", string sdt = "", string mail = "",
                Date ns = Date(), Date nvl = Date(),
                TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
                string pb = "", string cd = "", double luong = 0.0);
    
    virtual ~NVLuongCung();

    // Triển khai (implement) các hàm ảo thuần túy từ NhanVien
    virtual double tinhLuong() const override;
    virtual void hienThiThongTin() const override;
    virtual LoaiNhanVien getLoaiNV() const override;

    // Ghi đè các hàm ảo đọc/ghi file
    virtual void luuVaoFile(ostream& os) const override;
    virtual void docTuFile(istream& is) override;

    // Phương thức riêng
    void nhapThongTinRieng();
    void setLuongCoBan(double luong);
    double getLuongCoBan() const;
};
