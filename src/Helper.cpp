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

void Helper::setConsoleUTF8() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

void Helper::xoaManHinh() {
    system("cls");
}

void Helper::dungManHinh() {

    std::cout << "\nNhấn Enter để tiếp tục...";
    std::cin.clear(); // Xóa mọi cờ lỗi (nếu có)
    
    // Xóa bộ đệm đầu vào (xóa mọi ký tự '\n' còn sót lại từ lần nhapSoNguyen trước)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    
    // Đợi người dùng gõ Enter MỚI
    std::cin.get();
}

std::string Helper::nhapChuoi(const std::string& prompt, bool choPhepRong) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.empty() && !choPhepRong) {
            std::cout << " (!) Đầu vào không được để trống. Vui lòng nhập lại.\n";
        } else {
            return input;
        }
    }
}

int Helper::nhapSoNguyen(const std::string& prompt, int min, int max) {
    int value;
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        try {
            value = std::stoi(input);
            if (value >= min && value <= max) {
                return value;
            } else {
                std::cout << " (!) Giá trị phải trong khoảng [" << min << ", " << max << "]. Vui lòng nhập lại.\n";
            }
        } catch (const std::invalid_argument&) {
            std::cout << " (!) Đầu vào không hợp lệ. Vui lòng nhập một số nguyên.\n";
        } catch (const std::out_of_range&) {
            std::cout << " (!) Số quá lớn hoặc quá nhỏ vui lòng nhập lại.\n";
        }
    }
}

double Helper::nhapSoThuc(const std::string& prompt, double min) {
    double value;
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        try {
            value = std::stod(input);
            if (value >= min) {
                return value;
            } else {
                std::cout << " (!) Giá trị lớn hơn hoặc bằng " << min << ". Vui lòng nhập lại.\n";
            }
        } catch (const std::invalid_argument&) {
            std::cout << " (!) Đầu vào không hợp lệ. Vui lòng nhập một số thực.\n";
        } catch (const std::out_of_range&) {
            std::cout << " (!) Số quá lớn hoặc quá nhỏ. Vui lòng nhập lại.\n";
        }
    }
}

std::string Helper::trangThaiToString(TrangThaiLamViec trangThai) {
    switch (trangThai) {
        case TrangThaiLamViec::THU_VIEC: return "Thử việc";
        case TrangThaiLamViec::CHINH_THUC: return "Chính thức";
        case TrangThaiLamViec::DA_NGHI: return "Đã nghỉ";
        default: return "Không xác định";
    }
}

TrangThaiLamViec Helper::stringToTrangThai(const std::string& str) {
    if (str == "1" || str == "Thử việc") return TrangThaiLamViec::THU_VIEC;
    if (str == "2" || str == "Chính thức") return TrangThaiLamViec::CHINH_THUC;
    if (str == "3" || str == "Đã nghỉ") return TrangThaiLamViec::DA_NGHI;
    return TrangThaiLamViec::KHONG_XAC_DINH;
}


std::string Helper::formatCurrency(double value, bool showVND) {
    // Làm tròn thành số nguyên (VND không dùng số lẻ)
    long long val = static_cast<long long>(std::round(value));

    // Xử lý số 0
    if (val == 0) {
        return showVND ? "0 VND" : "0";
    }

    // Chuyển sang chuỗi
    std::string s = std::to_string(std::abs(val));
    std::string result = "";
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
    std::reverse(result.begin(), result.end());

    // Thêm dấu âm nếu cần
    if (val < 0) {
        result = "-" + result;
    }

    if (showVND) {
        result += " VND";
    }
    return result;
}

std::string Helper::taoMaTuDong(const std::string& tienTo, int soThuTu) {
    std::stringstream ss;
    ss << tienTo << std::setw(3) << std::setfill('0') << soThuTu;
    return ss.str();
}