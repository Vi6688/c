add_library(commonlib
    Memory.c
    List.c
    Vector.c
    Thread.c
    Time.c
    Mutex.c
    Map.c)

target_include_directories(commonlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
