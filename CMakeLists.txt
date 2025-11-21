cmake_minimum_required(VERSION 3.10)
project(QuanLyNhanSu CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. Lấy code C++ (Giữ nguyên)
file(GLOB SRC_FILES "src/*.cpp")
set(ALL_SOURCE_FILES Main.cpp ${SRC_FILES})

# 2. Tạo file chạy (Executable)
add_executable(HRM_App ${ALL_SOURCE_FILES})

# ==============================================================================
# 3. ĐÂY LÀ PHẦN QUAN TRỌNG BẠN CẦN THÊM
# ==============================================================================
# Lệnh này sẽ tự động COPY cả thư mục 'data' từ nơi chứa code
# sang nơi chứa file .exe sau khi build xong.
add_custom_command(TARGET HRM_App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/data"
    "$<TARGET_FILE_DIR:HRM_App>/data"
    COMMENT "Dang copy thu muc data vao noi chua file exe..."
)
# ==============================================================================

# 4. Cấu hình Include (Giữ nguyên)
target_include_directories(HRM_App PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 5. Cấu hình riêng cho Windows (Giữ nguyên)
if(WIN32)
    target_link_libraries(HRM_App PRIVATE kernel32)
    if(MSVC)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    elseif(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
    endif()
endif()