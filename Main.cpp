#include "../include/QuanLyNhanSu.h"
#include "../include/Helper.h"
#include <iostream>

int main() {
    // Thiết lập console để hỗ trợ tiếng Việt (chỉ hoạt động trên Windows)
    Helper::setConsoleUTF8();

    QuanLyNhanSu heThongQLNS;
    heThongQLNS.chay(); // Bắt đầu chạy ứng dụng

    return 0;
}