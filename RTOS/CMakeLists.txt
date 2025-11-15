include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Common)

add_library(RTOScommon
    Scheduler.c)

add_executable(RTOSengine Main.c)
target_include_directories(RTOSengine PUBLIC ${CMAKE_SOURCE_DIR}/Common)
target_link_libraries(RTOSengine PUBLIC RTOScommon commonlib)
