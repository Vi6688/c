idf_component_register(
    SRCS "Main.c" "source/GPIO.c" "source/Timer.c"
    INCLUDE_DIRS "." "${CMAKE_SOURCE_DIR}/main/include"
)