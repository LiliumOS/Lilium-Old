cmake_minimum_required(VERSION 3.15)
project(PhantomOS C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include_directories(include)

add_subdirectory(ld)
add_subdirectory(loader)

include(GNUInstallDirs)

set(PHANTOMOS_INSTALL_BOOTDIR boot CACHE PATH "Path to install the kernel and map into")

if(IS_ABSOLUTE ${PHANTOMOS_INSTALL_BOOTDIR})
    set(PHANTOMOS_FULL_INSTALL_BOOTDIR ${PHANTOMOS_INSTALL_BOOTDIR})
elseif(CMAKE_INSTALL_PREFIX STREQUAL "/usr" OR CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
    set(PHANTOMOS_FULL_INSTALL_BOOTDIR "/${PHANTOMOS_INSTALL_BOOTDIR}")
else()
    set(PHANTOMOS_FULL_INSTALL_BOOTDIR "${CMAKE_INSTALL_PREFIX}/${PHANTOMOS_INSTALL_BOOTDIR}")
endif()

add_executable(phantom src/start_kernel.c src/printk.c src/interrupts.S include/MachineInfo.h src/machine_info.S include/types.h
        src/memcpy.c include/bus.h src/bus.S)

target_compile_options(phantom PRIVATE -mno-red-zone -mno-sse -mno-mmx)

target_link_options(phantom PRIVATE "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/phantom.map")

target_link_libraries(phantom loader-amd64 phantom-kernel-ld-scripts)


