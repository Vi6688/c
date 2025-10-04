add_library(commonlib Memory.c List.c Vector.c)

# Make headers visible to anyone linking this library
target_include_directories(commonlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
