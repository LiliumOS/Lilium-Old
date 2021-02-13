
add_library(phantom-kernel SHARED src/main.c)

set_property(TARGET phantom-kernel PROPERTY OUTPUT_NAME "${PHANTOMOS_KERNEL_NAME}")
set_property(TARGET phantom-kernel PROPERTY SUFFIX "${PHANTOMOS_KERNEL_SUFFIX}")
set_property(TARGET phantom-kernel PROPERTY PREFIX "${PHANTOMOS_KERNEL_PREFIX}")

install(TARGETS phantom-kernel DESTINATION ${PHANTOMOS_FULL_INSTALL_KERNELDIR})
