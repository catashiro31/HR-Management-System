#include "../include/Date.h"
#include <iomanip>
#include <sstream>
#include <ctime> 
#include <stdexcept> 
using namespace std;

bool Date::laNamNhuan(int nam) const {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

int Date::soNgayTrongThang(int thang, int nam) const {
    if (thang == 2) {
        return laNamNhuan(nam) ? 29 : 28;
    } else if (thang == 4 || thang == 6 || thang == 9 || thang == 11) {
        return 30;
    } else {
        return 31;
    }
}

Date::Date(int d, int m, int y) {
    setDate(d, m, y); 
}

void Date::setDate(int d, int m, int y) {
    if (y < 1900 || y > 2100) y = 1990; 
    if (m < 1 || m > 12) m = 1; 
    this->nam = y;
    this->thang = m;
    int maxDay = soNgayTrongThang(m, y);
    if (d < 1 || d > maxDay) {
        this->ngay = 1; 
    } else {
        this->ngay = d;
    }
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
    if (ss.fail()) {
        return Date(1, 1, 1990); 
    }
    return Date(d, m, y); 
}

// --- HÀM MỚI (Hàm bạn đang gọi bị lỗi) ---
bool Date::operator<=(const Date& other) const {
    if (this->nam < other.nam) return true;
    if (this->nam > other.nam) return false;
    
    if (this->thang < other.thang) return true;
    if (this->thang > other.thang) return false;
    
    return this->ngay <= other.ngay;
}