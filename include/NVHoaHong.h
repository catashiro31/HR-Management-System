#pragma once
#include "NhanVien.h"

// Lớp NhanVienHoaHong (Commission Employee)
class NVHoaHong : public NhanVien {
private:
    double luongCoBan; // Lương cứng tối thiểu
    double doanhSoBanHang; // Cập nhật hàng tháng
    double tyLeHoaHong; // Ví dụ: 0.05 (5%)

public:
    NVHoaHong(std::string ma = "", std::string ten = "", std::string cccd = "",
              std::string dc = "", std::string sdt = "", std::string mail = "",
              Date ns = Date(), Date nvl = Date(),
              TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
              std::string pb = "", std::string cd = "", 
              double luongCB = 0.0, double doanhSo = 0.0, double tyLe = 0.0);
    
    virtual ~NVHoaHong();

    // Triển khai các hàm ảo
    virtual double tinhLuong() const override;
    virtual void hienThiThongTin() const override;
    virtual LoaiNhanVien getLoaiNV() const override;
    virtual void luuVaoFile(std::ostream& os) const override;
    virtual void docTuFile(std::istream& is) override;

    // Phương thức riêng
    void nhapThongTinRieng();
    void setDoanhSo(double doanhSo);
};
