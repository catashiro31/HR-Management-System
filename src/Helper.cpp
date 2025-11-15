
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN // Loại bỏ các header không cần thiết
#include <windows.h> 
#endif
#include "../include/Helper.h"
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept> 
#include "../include/GlobalConfig.h"
// (Block #include <windows.h> cũ đã được xóa khỏi đây)
using namespace std;


void Helper::setConsoleUTF8() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    #endif
}

void Helper::xoaManHinh() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void Helper::dungManHinh() {
    cout << "\nNhấn Enter để tiếp tục...";
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cin.get();
}

string Helper::nhapChuoi(const string& prompt, bool choPhepRong) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty() && !choPhepRong) {
            cout << " (!) Đầu vào không được để trống. Vui lòng nhập lại.\n";
        } else {
            return input;
        }
    }
}
bool Helper::isVietnamese(const string& str) {
    for (char c : str) {
        // Ký tự tiếng Việt có dấu thường có mã > 127 (nằm ngoài ASCII chuẩn)
        if (static_cast<unsigned char>(c) > 127) {
            return true;
        }
    }
    return false;
}

void Helper::inputName(string& name) {
    do {
        cout << "Nhập họ tên (không dấu, VD: Le Van Dung): ";
        getline(cin, name);
        
        if (Helper::isVietnamese(name)) {
            cout << "Lỗi: Vui lòng nhập tên không dấu!\n";
        }
    } while (Helper::isVietnamese(name));
}

int Helper::nhapSoNguyen(const string& prompt, int min, int max) {
    int value;
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            value = stoi(input);
            if (value >= min && value <= max) {
                return value;
            } else {
                cout << " (!) Giá trị phải trong khoảng [" << min << ", " << max << "]. Vui lòng nhập lại.\n";
            }
        } catch (...) {
            cout << " (!) Đầu vào không hợp lệ. Vui lòng nhập một số nguyên.\n";
        }
    }
}

double Helper::nhapSoThuc(const string& prompt, double min) {
    double value;
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            value = stod(input);
            if (value >= min) {
                return value;
            } else {
                cout << " (!) Giá trị lớn hơn hoặc bằng " << min << ". Vui lòng nhập lại.\n";
            }
        } catch (...) {
            cout << " (!) Đầu vào không hợp lệ. Vui lòng nhập một số thực.\n";
        }
    }
}

string Helper::trangThaiToString(TrangThaiLamViec trangThai) {
    switch (trangThai) {
        case TrangThaiLamViec::THU_VIEC: return "Thử việc";
        case TrangThaiLamViec::CHINH_THUC: return "Chính thức";
        case TrangThaiLamViec::DA_NGHI: return "Đã nghỉ";
        default: return "Không xác định";
    }
}

TrangThaiLamViec Helper::stringToTrangThai(const string& str) {
    if (str == "1" || str == "Thử việc") return TrangThaiLamViec::THU_VIEC;
    if (str == "2" || str == "Chính thức") return TrangThaiLamViec::CHINH_THUC;
    if (str == "3" || str == "Đã nghỉ") return TrangThaiLamViec::DA_NGHI;
    return TrangThaiLamViec::KHONG_XAC_DINH;
}

string Helper::toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string Helper::formatCurrency(double value, bool showVND) {
    long long val = static_cast<long long>(round(value));
    if (val == 0) { return showVND ? "0 VND" : "0"; }
    string s = to_string(abs(val));
    string result = "";
    int count = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        result += s[i];
        count++;
        if (count == 3 && i != 0) {
            result += ","; 
            count = 0;
        }
    }
    reverse(result.begin(), result.end());
    if (val < 0) { result = "-" + result; }
    if (showVND) { result += " VND"; }
    return result;
}

string Helper::taoMaTuDong(const string& tienTo, int soThuTu) {
    stringstream ss;
    ss << tienTo << setw(3) << setfill('0') << soThuTu;
    return ss.str();
}

// --- HÀM MỚI CHO BƯỚC 2 ---
string Helper::chuanHoaTen(const string& hoTen) {
    stringstream ss(hoTen);
    string word;
    string result = "";
    while (ss >> word) {
        word[0] = toupper(word[0]);
        for (size_t i = 1; i < word.length(); ++i) {
            word[i] = tolower(word[i]);
        }
        result += word;
    }
    return result;
}

string Helper::taoEmail(const string& tenChuanHoa, const Date& ngaySinh) {
    // Tạm thời dùng logic: LeVanDung2006@gmail.com
    // Nâng cao: Cần kiểm tra trùng lặp, nếu trùng thì dùng LeVanDung05022006@gmail.com
    return tenChuanHoa + to_string(ngaySinh.getNam()) + "@gmail.com";
}

string Helper::taoPassword(const Date& ngaySinh) {
    stringstream ss;
    ss << setfill('0')
       << setw(2) << ngaySinh.getNgay()
       << setw(2) << ngaySinh.getThang()
       << setw(4) << ngaySinh.getNam();
    return ss.str();
}

string Helper::roleToString(Role role) {
    switch (role) {
        case Role::CHU_TICH: return "Chủ Tịch";
        case Role::TRUONG_PHONG: return "Trưởng Phòng";
        case Role::KE_TOAN: return "Kế Toán";
        case Role::NHAN_VIEN: return "Nhân Viên";
        default: return "Chưa phân loại";
    }
}