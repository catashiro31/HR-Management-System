#pragma once
#include "NhanVien.h"

// Lớp NhanVienLuongCung (Salaried Employee)
// Kế thừa từ NhanVien
class NVLuongCung : public NhanVien {
private:
    double luongCoBan; // Lương cứng hàng tháng

public:
    NVLuongCung(std::string ma = "", std::string ten = "", std::string cccd = "",
                std::string dc = "", std::string sdt = "", std::string mail = "",
                Date ns = Date(), Date nvl = Date(),
                TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
                std::string pb = "", std::string cd = "", double luong = 0.0);
    
    virtual ~NVLuongCung();

    // Triển khai (implement) các hàm ảo thuần túy từ NhanVien
    virtual double tinhLuong() const override;
    virtual void hienThiThongTin() const override;
    virtual LoaiNhanVien getLoaiNV() const override;

    // Ghi đè các hàm ảo đọc/ghi file
    virtual void luuVaoFile(std::ostream& os) const override;
    virtual void docTuFile(std::istream& is) override;

    // Phương thức riêng
    void nhapThongTinRieng();
    void setLuongCoBan(double luong);
    double getLuongCoBan() const;
};
