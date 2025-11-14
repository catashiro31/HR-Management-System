#pragma once
#include <string>
#include <fstream>
#include "Date.h"
using namespace std;

// Lớp cơ sở trừu tượng "Nguoi" (Person)
// Chứa các thông tin chung nhất
// Thể hiện tính TRỪU TƯỢNG (Abstraction)
class Nguoi {
protected:
    string hoTen;
    string cmnd_cccd;
    string diaChi;
    string soDienThoai;
    string email;
    Date ngaySinh;

public:
    // Constructor
    Nguoi(string ten = "", string cccd = "", string dc = "",
          string sdt = "", string mail = "", Date ns = Date());
    
    // Destructor ảo - Bắt buộc phải có khi dùng kế thừa và đa hình
    virtual ~Nguoi();

    // Các hàm ảo thuần túy (pure virtual)
    // Bắt buộc các lớp con phải định nghĩa lại
    virtual void hienThiThongTin() const = 0; 

    // Các hàm ảo (virtual) cho phép đọc/ghi file
    // Cung cấp triển khai mặc định (ghi/đọc các trường chung)
    // Các lớp con sẽ gọi lại hàm này và ghi/đọc thêm phần riêng
    virtual void luuVaoFile(ostream& os) const;
    virtual void docTuFile(istream& is);

    // Getters/Setters (Thể hiện tính ĐÓNG GÓI)
    void setHoTen(const string& ten);
    string getHoTen() const;
    void setDiaChi(const string& dc);
    string getDiaChi() const;
    // ... (Thêm các getters/setters khác nếu cần)
};
