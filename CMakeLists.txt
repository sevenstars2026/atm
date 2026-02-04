cmake_minimum_required(VERSION 3.20)
project(ATM)

# 1. 必须使用 C++17 或更高
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. 告诉 CMake 你的源文件有哪些
add_executable(ATM main.cpp DBHelper.cpp DBHelper.h)

# 3. 寻找并链接数据库库 (Linux 下最通用的写法)
# 如果你是通过 sudo apt install libpqxx-dev 安装的，这样写就能找到
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

target_include_directories(ATM PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(ATM PRIVATE ${PQXX_LIBRARIES})