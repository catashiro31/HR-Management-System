#pragma once
#include <string>
#include <fstream>
#include "Date.h"

// Lớp cơ sở trừu tượng "Nguoi" (Person)
// Chứa các thông tin chung nhất
// Thể hiện tính TRỪU TƯỢNG (Abstraction)
class Nguoi {
protected:
    std::string hoTen;
    std::string cmnd_cccd;
    std::string diaChi;
    std::string soDienThoai;
    std::string email;
    Date ngaySinh;

public:
    // Constructor
    Nguoi(std::string ten = "", std::string cccd = "", std::string dc = "",
          std::string sdt = "", std::string mail = "", Date ns = Date());
    
    // Destructor ảo - Bắt buộc phải có khi dùng kế thừa và đa hình
    virtual ~Nguoi();

    // Các hàm ảo thuần túy (pure virtual)
    // Bắt buộc các lớp con phải định nghĩa lại
    virtual void hienThiThongTin() const = 0; 

    // Các hàm ảo (virtual) cho phép đọc/ghi file
    // Cung cấp triển khai mặc định (ghi/đọc các trường chung)
    // Các lớp con sẽ gọi lại hàm này và ghi/đọc thêm phần riêng
    virtual void luuVaoFile(std::ostream& os) const;
    virtual void docTuFile(std::istream& is);

    // Getters/Setters (Thể hiện tính ĐÓNG GÓI)
    void setHoTen(const std::string& ten);
    std::string getHoTen() const;
    void setDiaChi(const std::string& dc);
    std::string getDiaChi() const;
    // ... (Thêm các getters/setters khác nếu cần)
};
