#pragma once
#include <string>
#include <iostream>

using namespace std;

class Date {
private:
    int ngay;
    int thang;
    int nam;

public:
    Date(int d = 1, int m = 1, int y = 2000);

    // Setters
    void setDate(int d, int m, int y);

    // Getters
    string toString() const;
    int getNgay() const;
    int getThang() const;
    int getNam() const;

    friend ostream& operator<<(ostream& os, const Date& dt);
    friend istream& operator>>(istream& is, Date& dt);

    // --- BỎ STATIC ---
    Date layNgayHienTai();
    Date fromString(const string& str);
};