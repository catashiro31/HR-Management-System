#include "../include/Date.h"
#include <iomanip>
#include <sstream>
#include <ctime> 
using namespace std;

Date::Date(int d, int m, int y) {
    setDate(d, m, y);
}

void Date::setDate(int d, int m, int y) {
    nam = (y >= 1900) ? y : 1900;
    thang = (m >= 1 && m <= 12) ? m : 1;
    ngay = (d >= 1 && d <= 31) ? d : 1;
}

string Date::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << ngay << "/"
       << setw(2) << thang << "/" << nam;
    return ss.str();
}

int Date::getNgay() const { return ngay; }
int Date::getThang() const { return thang; }
int Date::getNam() const { return nam; }

ostream& operator<<(ostream& os, const Date& dt) {
    os << dt.toString();
    return os;
}

istream& operator>>(istream& is, Date& dt) {
    char slash1, slash2;
    is >> dt.ngay >> slash1 >> dt.thang >> slash2 >> dt.nam;
    return is;
}

// --- BỎ STATIC ---
Date Date::layNgayHienTai() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}

// --- BỎ STATIC ---
Date Date::fromString(const string& str) {
    int d, m, y;
    char slash1, slash2;
    stringstream ss(str);
    ss >> d >> slash1 >> m >> slash2 >> y;
    if (ss.fail()) {
        return Date(1, 1, 1990); // Mặc định nếu lỗi
    }
    return Date(d, m, y);
}