#pragma once
#include <string>
using namespace std;

class PhongBan {
private:
    string maPB;
    string tenPB;
    string maTruongPhong; // Chỉ lưu mã NV của trưởng phòng

public:
    PhongBan(string ma = "", string ten = "", string maTP = "");
    ~PhongBan();

    void hienThi() const;

    // Getters/Setters
    string getMaPB() const;
    string getTenPB() const;
    void setTenPB(const string& ten);
    string getMaTruongPhong() const;
    void setMaTruongPhong(const string& maNV);
};
