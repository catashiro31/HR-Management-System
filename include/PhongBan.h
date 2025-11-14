#pragma once
#include <string>

// Lớp Phòng Ban (Department)
// Thể hiện tính ĐÓNG GÓI
class PhongBan {
private:
    std::string maPB;
    std::string tenPB;
    std::string maTruongPhong; // Chỉ lưu mã NV của trưởng phòng

public:
    PhongBan(std::string ma = "", std::string ten = "", std::string maTP = "");
    ~PhongBan();

    void hienThi() const;
 
    // Getters/Setters
    std::string getMaPB() const;
    std::string getTenPB() const;
    void setTenPB(const std::string& ten);
    std::string getMaTruongPhong() const;
    void setMaTruongPhong(const std::string& maNV);
};
