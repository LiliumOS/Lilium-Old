
add_library(phantom-threads SHARED src/main.c ${PHANTOMOS_TARGET_PROCESSOR}/src/main.c
    include/ThreadHandle.h)

target_include_directories(phantom-threads PRIVATE include)
target_link_libraries(phantom-threads PRIVATE phantom-module-ld-scripts)

install(TARGETS phantom-threads DESTINATION ${PHANTOMOS_FULL_INSTALL_DYNLIBDIR})