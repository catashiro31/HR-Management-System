// FIX lỗi 'byte' ambiguous
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h> 
#endif
#include<bits/stdc++.h>
#include "../include/Helper.h"
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept> 
#include "../include/GlobalConfig.h"
using namespace std;

// --- BỎ TOÀN BỘ Helper:: ---

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
string Helper::nhapChuoiSo(const string& prompt, bool choPhepRong) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);

        if (input.empty()) {
            if (!choPhepRong) {
                cout << " (!) Đầu vào không được để trống. Vui lòng nhập lại.\n";
                continue;
            } else {
                return input; // Cho phép rỗng nếu choPhepRong = true
            }
        }
        if (input.find_first_not_of("0123456789") == string::npos) {
            return input; // Hợp lệ, chỉ chứa số
        } else {
            cout << " (!) Đầu vào chỉ được phép chứa số (0-9). Vui lòng nhập lại.\n";
        }
    }
}

string Helper::nhapTen(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << " (!) Tên không được để trống.\n";
            continue;
        }
        
        bool hopLe = true;
        for (char c : input) {
            if (!isalpha(c) && !isspace(c)) {
                hopLe = false;
                break;
            }
        }
        
        if (hopLe) {
            return input;
        } else {
            cout << " (!) Tên chỉ được chứa chữ cái và khoảng trắng (Không số, không ký tự đặc biệt).\n";
        }
    }
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

string Helper::taoEmail(const string& tenChuanHoa, const Date& ngaySinh, const string& maNV, bool dungMaNV) {
    string base = tenChuanHoa + to_string(ngaySinh.getNam());
    if (dungMaNV) {
        base += maNV;
    }
    return base + "@team4.group";
}

string Helper::taoPassword(const Date& ngaySinh, const string& maNV, bool dungMaNV) {
    stringstream ss;
    ss << setfill('0')
       << setw(2) << ngaySinh.getNgay()
       << setw(2) << ngaySinh.getThang()
       << setw(4) << ngaySinh.getNam();
    string base = ss.str();
    if (dungMaNV) {
        base += maNV;
    }
    return base;
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

string Helper::removeVietnameseAccent(const string &s) {
    static const unordered_map<string, string> mp = {
        {"á","a"},{"à","a"},{"ả","a"},{"ã","a"},{"ạ","a"},
        {"ă","a"},{"ắ","a"},{"ằ","a"},{"ẳ","a"},{"ẵ","a"},{"ặ","a"},
        {"â","a"},{"ấ","a"},{"ầ","a"},{"ẩ","a"},{"ẫ","a"},{"ậ","a"},
        {"đ","d"},

        {"é","e"},{"è","e"},{"ẻ","e"},{"ẽ","e"},{"ẹ","e"},
        {"ê","e"},{"ế","e"},{"ề","e"},{"ể","e"},{"ễ","e"},{"ệ","e"},

        {"í","i"},{"ì","i"},{"ỉ","i"},{"ĩ","i"},{"ị","i"},

        {"ó","o"},{"ò","o"},{"ỏ","o"},{"õ","o"},{"ọ","o"},
        {"ô","o"},{"ố","o"},{"ồ","o"},{"ổ","o"},{"ỗ","o"},{"ộ","o"},
        {"ơ","o"},{"ớ","o"},{"ờ","o"},{"ở","o"},{"ỡ","o"},{"ợ","o"},

        {"ú","u"},{"ù","u"},{"ủ","u"},{"ũ","u"},{"ụ","u"},
        {"ư","u"},{"ứ","u"},{"ừ","u"},{"ử","u"},{"ữ","u"},{"ự","u"},

        {"ý","y"},{"ỳ","y"},{"ỷ","y"},{"ỹ","y"},{"ỵ","y"},

        // CHỮ HOA
        {"Á","A"},{"À","A"},{"Ả","A"},{"Ã","A"},{"Ạ","A"},
        {"Ă","A"},{"Ắ","A"},{"Ằ","A"},{"Ẳ","A"},{"Ẵ","A"},{"Ặ","A"},
        {"Â","A"},{"Ấ","A"},{"Ầ","A"},{"Ẩ","A"},{"Ẫ","A"},{"Ậ","A"},
        {"Đ","D"},
        {"É","E"},{"È","E"},{"Ẻ","E"},{"Ẽ","E"},{"Ẹ","E"},
        {"Ê","E"},{"Ế","E"},{"Ề","E"},{"Ể","E"},{"Ễ","E"},{"Ệ","E"},
        {"Í","I"},{"Ì","I"},{"Ỉ","I"},{"Ĩ","I"},{"Ị","I"},
        {"Ó","O"},{"Ò","O"},{"Ỏ","O"},{"Õ","O"},{"Ọ","O"},
        {"Ô","O"},{"Ố","O"},{"Ồ","O"},{"Ổ","O"},{"Ỗ","O"},{"Ộ","O"},
        {"Ơ","O"},{"Ớ","O"},{"Ờ","O"},{"Ở","O"},{"Ỡ","O"},{"Ợ","O"},
        {"Ú","U"},{"Ù","U"},{"Ủ","U"},{"Ũ","U"},{"Ụ","U"},
        {"Ư","U"},{"Ứ","U"},{"Ừ","U"},{"Ử","U"},{"Ữ","U"},{"Ự","U"},
        {"Ý","Y"},{"Ỳ","Y"},{"Ỷ","Y"},{"Ỹ","Y"},{"Ỵ","Y"}
    };

    string res;
    int i = 0;
    while (i < s.size()) {
        // Lấy đúng 1 ký tự UTF-8
        unsigned char c = s[i];
        int len = 1;
        if (c >= 0xC0 && c <= 0xDF) len = 2;     // 2-byte UTF-8
        else if (c >= 0xE0 && c <= 0xEF) len = 3; // 3-byte UTF-8

        string ch = s.substr(i, len);

        if (mp.count(ch)) res += mp.at(ch);
        else res += ch;

        i += len;
    }
    return res;
}