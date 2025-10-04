cmake_minimum_required(VERSION 3.10)
project(MyCLib C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(Common)
add_executable(test Main.c)
target_link_libraries(test PRIVATE commonlib)

# Optional warnings
if (MSVC)
    target_compile_options(test PRIVATE /W4)
else()
    target_compile_options(test PRIVATE -Wall -Wextra -pedantic)
endif()
