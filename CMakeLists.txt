cmake_minimum_required(VERSION 3.10)
project(MyCLib C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Common)
# add_subdirectory(esp-idf)
add_subdirectory(esp32)
add_subdirectory(RTOS)

add_executable(Main Main.c)
target_include_directories(Main PUBLIC ${CMAKE_SOURCE_DIR}/Common)
target_link_libraries(Main PRIVATE commonlib)
