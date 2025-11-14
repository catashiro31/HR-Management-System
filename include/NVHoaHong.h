#pragma once
#include "NhanVien.h"

using namespace std;


// Lớp NhanVienHoaHong (Commission Employee)
class NVHoaHong : public NhanVien {
private:
    double luongCoBan; // Lương cứng tối thiểu
    double doanhSoBanHang; // Cập nhật hàng tháng
    double tyLeHoaHong; // Ví dụ: 0.05 (5%)

public:
    NVHoaHong(string ma = "", string ten = "", string cccd = "",
              string dc = "", string sdt = "", string mail = "",
              Date ns = Date(), Date nvl = Date(),
              TrangThaiLamViec tt = TrangThaiLamViec::THU_VIEC,
              string pb = "", string cd = "", 
              double luongCB = 0.0, double doanhSo = 0.0, double tyLe = 0.0);
    
    virtual ~NVHoaHong();

    // Triển khai các hàm ảo
    virtual double tinhLuong() const override;
    virtual void hienThiThongTin() const override;
    virtual LoaiNhanVien getLoaiNV() const override;
    virtual void luuVaoFile(ostream& os) const override;
    virtual void docTuFile(istream& is) override;

    // Phương thức riêng
    void nhapThongTinRieng();
    void setDoanhSo(double doanhSo);
};
