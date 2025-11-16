#include "../include/Account.h"
#include <sstream>

Account::Account(string user, string pass, Role r, string maNV)
    : username(user), password(pass), role(r), maNhanVien(maNV) {}

string Account::getUsername() const { return username; }
Role Account::getRole() const { return role; }
string Account::getMaNhanVien() const { return maNhanVien; }

bool Account::kiemTraMatKhau(const string& pass) const {
    return this->password == pass;
}

void Account::luuVaoFile(ostream& os) const {
    os << username << ","
       << password << ","
       << static_cast<int>(role) << ","
       << maNhanVien << "\n";
}

void Account::docTuFile(istream& is) {
    string roleStr;
    
    getline(is, username, ',');
    getline(is, password, ',');
    getline(is, roleStr, ',');
    getline(is, maNhanVien); // Đọc đến hết dòng

    try {
        role = static_cast<Role>(stoi(roleStr));
    } catch (...) {
        role = Role::CHUA_PHAN_LOAI;
    }
}