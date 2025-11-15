#pragma once
#include <string>
#include <fstream>
#include "Date.h"
using namespace std;

class Nguoi {
protected:
    string hoTen;
    string cmnd_cccd;
    string diaChi;
    string soDienThoai;
    string email;
    Date ngaySinh;

public:
    Nguoi(string ten = "", string cccd = "", string dc = "",
          string sdt = "", string mail = "", Date ns = Date());
    virtual ~Nguoi();

    virtual void hienThiThongTin() const = 0; 
    virtual void luuVaoFile(ostream& os) const;
    virtual void docTuFile(istream& is);

    // Getters/Setters
    void setHoTen(const string& ten);
    string getHoTen() const;
    void setDiaChi(const string& dc);
    string getDiaChi() const;
    
    // --- HÀM MỚI ---
    void setEmail(const string& mail);
    Date getNgaySinh() const;
};