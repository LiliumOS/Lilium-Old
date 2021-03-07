
link_libraries(phantom-arch-${PHANTOMOS_TARGET_PROCESSOR}-options)

add_subdirectory(fat32)
add_subdirectory(ext)

set(PHANTOMOS_KNOWN_FILESYSTEMS "fat32;ext")

set(PHANTOMOS_LOADER_FILESYSTEMS "fat32;ext" CACHE STRING "List of filesystems to build into the loader")
set(PHANTOMOS_KERNEL_FILESYSTEMS "all" CACHE STRING "List of filesystems to build into the kernel")

if(PHANTOMOS_LOADER_FILESYSTEMS STREQUAL "all")
    set(PHANTOMOS_LOADER_FILESYSTEMS "${PHANTOMOS_KNOWN_FILESYSTEMS}")
endif()

if(PHANTOMOS_KERNEL_FILESYSTEMS STREQUAL "all")
    set(PHANTOMOS_KERNEL_FILESYSTEMS "${PHANTOMOS_KNOWN_FILESYSTEMS}")
endif()

add_library(phantom-fs-loader STATIC fsdrv.c)
foreach(fs ${PHANTOMOS_LOADER_FILESYSTEMS})
    target_link_libraries(phantom-fs-loader ${fs})
endforeach()

add_library(phantom-fs SHARED fsdrv.c)
target_link_libraries(phantom-fs phantom-module-ld-scripts)
foreach(fs ${PHANTOMOS_KERNEL_FILESYSTEMS})
    target_link_libraries(phantom-fs ${fs})
endforeach()
