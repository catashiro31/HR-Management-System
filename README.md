# HR-Management-System

## 📁 Cấu trúc đề xuất

```
hr_management_system/
|── *.h
|── *.cpp
├── README.md
└── Makefile                # (hoặc file CMakeLists.txt nếu dùng CMake)
```

---

## 🧩 Giải thích

| Thư mục / File | Mục đích                                                       |
| -------------- | -------------------------------------------------------------- |
| `include/`     | Chứa **header (.h)** – định nghĩa class, struct, prototype hàm |
| `src/`         | Chứa **source (.cpp)** – phần triển khai của class và hàm      |
| `main.cpp`     | Chứa `int main()` – chương trình chính                         |
| `build/`       | Thư mục chứa file `.o` và file chạy `.exe` sau khi biên dịch   |
| `Makefile`     | File build tự động                                             |
| `README.md`    | Hướng dẫn chạy, compile, và mô tả dự án                        |

---

## 🧱 Makefile (đơn giản nhất)

Cách chạy: Tại đường dẫn file Main.cpp
Gõ lần lượt lệnh sau:
```
g++ *.cpp src/*cpp -o app.exe
.\app.exe
```
