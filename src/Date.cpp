#include "../include/Date.h"
#include <iomanip> // Dùng cho setw, setfill
#include <sstream>
#include <ctime>   // Dùng để lấy ngày giờ hệ thống
using namespace std;

Date::Date(int d, int m, int y) {
    setDate(d, m, y);
}

void Date::setDate(int d, int m, int y) {
    // Tạm thời bỏ qua kiểm tra ngày hợp lệ phức tạp (ví dụ: tháng 2 có 28/29 ngày)
    // Để đơn giản hóa ví dụ
    nam = (y >= 1900) ? y : 1900;
    thang = (m >= 1 && m <= 12) ? m : 1;
    ngay = (d >= 1 && d <= 31) ? d : 1; // Giả định đơn giản
}

string Date::toString() const {
    stringstream ss;
    ss << setfill('0') << setw(2) << ngay << "/"
       << setw(2) << thang << "/" << nam;
    return ss.str();
}

ostream& operator<<(ostream& os, const Date& dt) {
    os << dt.toString();
    return os;
}

istream& operator>>(istream& is, Date& dt) {
    char slash1, slash2;
    is >> dt.ngay >> slash1 >> dt.thang >> slash2 >> dt.nam;
    // Nên có kiểm tra slash1 == '/' && slash2 == '/'
    return is;
}

Date Date::layNgayHienTai() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}

Date Date::fromString(const string& str) {
    int d, m, y;
    char slash1, slash2;
    stringstream ss(str);
    ss >> d >> slash1 >> m >> slash2 >> y;
    // Nên có kiểm tra slash1 == '/' && slash2 == '/'
    return Date(d, m, y);
}