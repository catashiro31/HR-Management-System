#include "../include/Nguoi.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Nguoi::Nguoi(string ten, string cccd, string dc,
             string sdt, string mail, Date ns)
    : hoTen(ten), cmnd_cccd(cccd), diaChi(dc), soDienThoai(sdt), email(mail), ngaySinh(ns) {}

Nguoi::~Nguoi() {}

void Nguoi::luuVaoFile(ostream& os) const {
    os << hoTen << ","
       << cmnd_cccd << ","
       << diaChi << ","
       << soDienThoai << ","
       << email << ","
       << ngaySinh.toString() << ",";
}

void Nguoi::docTuFile(istream& is) {
    getline(is, hoTen, ',');
    getline(is, cmnd_cccd, ',');
    getline(is, diaChi, ',');
    getline(is, soDienThoai, ',');
    getline(is, email, ',');

    string ngaySinhStr;
    getline(is, ngaySinhStr, ',');

    Date dateUtil; 
    ngaySinh = dateUtil.fromString(ngaySinhStr); 
}

// Implement getters/setters
void Nguoi::setHoTen(const string& ten) {
    hoTen = ten;
}

string Nguoi::getHoTen() const {
    return hoTen;
}

void Nguoi::setDiaChi(const string& dc) {
    diaChi = dc;
}

string Nguoi::getDiaChi() const {
    return diaChi;
}

void Nguoi::setEmail(const string& mail) {
    email = mail;
}

Date Nguoi::getNgaySinh() const {
    return ngaySinh;
}