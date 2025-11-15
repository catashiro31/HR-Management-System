
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN // Loại bỏ các header không cần thiết
#include <windows.h> 
#endif
#include "../include/Helper.h"
#include <iostream>
#include <map>
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
    // Bỏ dấu trước
    string tenKhongDau = boDauTiengViet(hoTen);
    
    stringstream ss(tenKhongDau);
    string word;
    string result = "";
    
    while (ss >> word) {
        // Viết hoa chữ cái đầu, viết thường phần còn lại
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
string Helper::boDauTiengViet(const string& str) {
    // Map các ký tự tiếng Việt có dấu sang không dấu
    map <string, string> bangChuyenDoi = {
        // Chữ thường
        {"à", "a"}, {"á", "a"}, {"ạ", "a"}, {"ả", "a"}, {"ã", "a"},
        {"â", "a"}, {"ầ", "a"}, {"ấ", "a"}, {"ậ", "a"}, {"ẩ", "a"}, {"ẫ", "a"},
        {"ă", "a"}, {"ằ", "a"}, {"ắ", "a"}, {"ặ", "a"}, {"ẳ", "a"}, {"ẵ", "a"},
        {"è", "e"}, {"é", "e"}, {"ẹ", "e"}, {"ẻ", "e"}, {"ẽ", "e"},
        {"ê", "e"}, {"ề", "e"}, {"ế", "e"}, {"ệ", "e"}, {"ể", "e"}, {"ễ", "e"},
        {"ì", "i"}, {"í", "i"}, {"ị", "i"}, {"ỉ", "i"}, {"ĩ", "i"},
        {"ò", "o"}, {"ó", "o"}, {"ọ", "o"}, {"ỏ", "o"}, {"õ", "o"},
        {"ô", "o"}, {"ồ", "o"}, {"ố", "o"}, {"ộ", "o"}, {"ổ", "o"}, {"ỗ", "o"},
        {"ơ", "o"}, {"ờ", "o"}, {"ớ", "o"}, {"ợ", "o"}, {"ở", "o"}, {"ỡ", "o"},
        {"ù", "u"}, {"ú", "u"}, {"ụ", "u"}, {"ủ", "u"}, {"ũ", "u"},
        {"ư", "u"}, {"ừ", "u"}, {"ứ", "u"}, {"ự", "u"}, {"ử", "u"}, {"ữ", "u"},
        {"ỳ", "y"}, {"ý", "y"}, {"ỵ", "y"}, {"ỷ", "y"}, {"ỹ", "y"},
        {"đ", "d"},
        // Chữ hoa
        {"À", "A"}, {"Á", "A"}, {"Ạ", "A"}, {"Ả", "A"}, {"Ã", "A"},
        {"Â", "A"}, {"Ầ", "A"}, {"Ấ", "A"}, {"Ậ", "A"}, {"Ẩ", "A"}, {"Ẫ", "A"},
        {"Ă", "A"}, {"Ằ", "A"}, {"Ắ", "A"}, {"Ặ", "A"}, {"Ẳ", "A"}, {"Ẵ", "A"},
        {"È", "E"}, {"É", "E"}, {"Ẹ", "E"}, {"Ẻ", "E"}, {"Ẽ", "E"},
        {"Ê", "E"}, {"Ề", "E"}, {"Ế", "E"}, {"Ệ", "E"}, {"Ể", "E"}, {"Ễ", "E"},
        {"Ì", "I"}, {"Í", "I"}, {"Ị", "I"}, {"Ỉ", "I"}, {"Ĩ", "I"},
        {"Ò", "O"}, {"Ó", "O"}, {"Ọ", "O"}, {"Ỏ", "O"}, {"Õ", "O"},
        {"Ô", "O"}, {"Ồ", "O"}, {"Ố", "O"}, {"Ộ", "O"}, {"Ổ", "O"}, {"Ỗ", "O"},
        {"Ơ", "O"}, {"Ờ", "O"}, {"Ớ", "O"}, {"Ợ", "O"}, {"Ở", "O"}, {"Ỡ", "O"},
        {"Ù", "U"}, {"Ú", "U"}, {"Ụ", "U"}, {"Ủ", "U"}, {"Ũ", "U"},
        {"Ư", "U"}, {"Ừ", "U"}, {"Ứ", "U"}, {"Ự", "U"}, {"Ử", "U"}, {"Ữ", "U"},
        {"Ỳ", "Y"}, {"Ý", "Y"}, {"Ỵ", "Y"}, {"Ỷ", "Y"}, {"Ỹ", "Y"},
        {"Đ", "D"}
    };
    
    string result = "";
    size_t i = 0;
    
    while (i < str.length()) {
        bool found = false;
        
        // Thử match 2-3 bytes (ký tự UTF-8 tiếng Việt)
        for (int len = 3; len >= 2; len--) {
            if (i + len <= str.length()) {
                string sub = str.substr(i, len);
                if (bangChuyenDoi.find(sub) != bangChuyenDoi.end()) {
                    result += bangChuyenDoi[sub];
                    i += len;
                    found = true;
                    break;
                }
            }
        }
        
        // Nếu không phải ký tự đặc biệt, giữ nguyên
        if (!found) {
            result += str[i];
            i++;
        }
    }
    
    return result;
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