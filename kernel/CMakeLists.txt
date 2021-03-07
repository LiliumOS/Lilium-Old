
add_library(phantom-loader SHARED src/libstubs.c ${PHANTOMOS_TARGET_PROCESSOR}/libstubs.c)

set_property(TARGET phantom-loader PROPERTY PREFIX "")

add_library(phantom-kernel SHARED src/main.c)

target_link_libraries(phantom-kernel phantom-loader phantom-threads phantom-fs phantom-module-ld-scripts)

set_property(TARGET phantom-kernel PROPERTY OUTPUT_NAME "${PHANTOMOS_KERNEL_NAME}")
set_property(TARGET phantom-kernel PROPERTY SUFFIX "${PHANTOMOS_KERNEL_SUFFIX}")
set_property(TARGET phantom-kernel PROPERTY PREFIX "${PHANTOMOS_KERNEL_PREFIX}")

install(TARGETS phantom-kernel DESTINATION ${PHANTOMOS_FULL_INSTALL_KERNELDIR})
