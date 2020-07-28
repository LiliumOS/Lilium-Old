
add_library(phantom-kernel-ld-scripts INTERFACE)

add_dependencies(phantom-kernel-ld-scripts ${CMAKE_CURRENT_SOURCE_DIR}/x86_64-pc-phantom-kernel.ld)

set_target_properties(phantom-kernel-ld-scripts PROPERTIES
        INTERFACE_LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/x86_64-pc-phantom-kernel.ld)

target_link_options(phantom-kernel-ld-scripts INTERFACE "-Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/x86_64-pc-phantom-kernel.ld")