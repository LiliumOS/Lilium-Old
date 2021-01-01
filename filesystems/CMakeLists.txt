set(PHANTOMOS_KNOWN_FILESYSTEMS fat32)

set(PHANTOMOS_ENABLE_FILESYSTEMS ${PHANTOMOS_KNOWN_FILESYSTEMS} CACHE STRING "Specifies filesystems to build support for")

foreach(fs ${PHANTOMOS_ENABLE_FILESYSTEMS})
    add_subdirectory(${fs})
endforeach()
