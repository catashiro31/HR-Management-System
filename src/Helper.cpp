#include "../include/Helper.h"
#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept> // Dùng cho stoi, stod
#include "../include/GlobalConfig.h"
#ifdef _WIN32
#include <windows.h> // Dùng cho SetConsoleOutputCP
#endif
using namespace std;


void Helper::setConsoleUTF8() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

void Helper::xoaManHinh() {
    system("cls");
}

void Helper::dungManHinh() {

    cout << "\nNhấn Enter để tiếp tục...";
    cin.clear(); // Xóa mọi cờ lỗi (nếu có)
    
    // Xóa bộ đệm đầu vào (xóa mọi ký tự '\n' còn sót lại từ lần nhapSoNguyen trước)
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    // Đợi người dùng gõ Enter MỚI
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
        } catch (const invalid_argument&) {
            cout << " (!) Đầu vào không hợp lệ. Vui lòng nhập một số nguyên.\n";
        } catch (const out_of_range&) {
            cout << " (!) Số quá lớn hoặc quá nhỏ vui lòng nhập lại.\n";
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
        } catch (const invalid_argument&) {
            cout << " (!) Đầu vào không hợp lệ. Vui lòng nhập một số thực.\n";
        } catch (const out_of_range&) {
            cout << " (!) Số quá lớn hoặc quá nhỏ. Vui lòng nhập lại.\n";
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


string Helper::formatCurrency(double value, bool showVND) {
    // Làm tròn thành số nguyên (VND không dùng số lẻ)
    long long val = static_cast<long long>(round(value));

    // Xử lý số 0
    if (val == 0) {
        return showVND ? "0 VND" : "0";
    }

    // Chuyển sang chuỗi
    string s = to_string(abs(val));
    string result = "";
    int count = 0;

    // Thêm dấu phẩy từ phải sang trái
    for (int i = s.length() - 1; i >= 0; i--) {
        result += s[i];
        count++;
        if (count == 3 && i != 0) {
            result += ","; // Dùng dấu phẩy
            count = 0;
        }
    }

    // Đảo ngược chuỗi
    reverse(result.begin(), result.end());

    // Thêm dấu âm nếu cần
    if (val < 0) {
        result = "-" + result;
    }

    if (showVND) {
        result += " VND";
    }
    return result;
}

string Helper::taoMaTuDong(const string& tienTo, int soThuTu) {
    stringstream ss;
    ss << tienTo << setw(3) << setfill('0') << soThuTu;
    return ss.str();
}