
add_library(phantomos-threads SHARED src/main.c ${PHANTOMOS_TARGET_PROCESSOR}/src/main.c
    include/ThreadHandle.h)

target_include_directories(phantomos-threads PRIVATE include)
