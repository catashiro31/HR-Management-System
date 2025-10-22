# HR-Management-System

## 📁 Cấu trúc đề xuất

```
hr_management_system/
├── include/
│   ├── benefits.h
│   ├── commissionemployee.h
│   ├── dentalbenefit.h
│   ├── dentalhealth.h
│   ├── department.h
│   ├── employee.h
│   ├── healthbenefit.h
│   ├── hourlyemployee.h
│   ├── hrsystem.h
│   ├── manageremployee.h
│   └── salariedemployee.h
│
├── src/
│   ├── main.cpp
│   ├── benefits.cpp
│   ├── employee.cpp
│   ├── department.cpp
│   ├── hrsystem.cpp
│   ├── commissionemployee.cpp
│   ├── hourlyemployee.cpp
│   ├── manageremployee.cpp
│   └── salariedemployee.cpp
│
├── build/                  # (tự tạo khi compile)
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

Tạo file `Makefile` trong thư mục gốc:

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)
TARGET = build/hr_management_system.exe

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)
```

Cách chạy:

```bash
make        # biên dịch
make run    # chạy chương trình
make clean  # xoá file build
```