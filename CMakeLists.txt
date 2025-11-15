cmake_minimum_required(VERSION 3.10)
project(QuanLyNhanSu CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC_FILES "src/*.cpp")

set(ALL_SOURCE_FILES
Main.cpp
${SRC_FILES}
)

add_executable(HRM_App ${ALL_SOURCE_FILES})

target_include_directories(HRM_App PRIVATE ${PROJECT_SOURCE_DIR}/include)

if(WIN32)
target_link_libraries(HRM_App PRIVATE kernel32)
if(MSVC)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
elseif(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()
endif()