#pragma once
#include <string>
#include <fstream>
#include "GlobalConfig.h" // Cần cho Role
using namespace std;

class Account {
private:
    string username;
    string password; 
    Role role;
    string maNhanVien; // Mã NV liên kết với tài khoản này

public:
    Account(string user = "", string pass = "", Role r = Role::NHAN_VIEN, string maNV = "");
    
    // Getters
    string getUsername() const;
    Role getRole() const;
    string getMaNhanVien() const;

    // Check mật khẩu
    bool kiemTraMatKhau(const string& pass) const;

    // Hàm lưu file
    void luuVaoFile(ostream& os) const;
    void docTuFile(istream& is);
};