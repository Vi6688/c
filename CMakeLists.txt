cmake_minimum_required(VERSION 3.10)
project(MyCLib C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Common)
add_executable(Main Main.c)
target_link_libraries(Main PRIVATE commonlib)

# Optional warnings
if (MSVC)
    target_compile_options(Main PRIVATE /W4)
else()
    target_compile_options(Main PRIVATE -Wall -Wextra -pedantic)
endif()
