# CMakeLists.txt
# 
# This file is part of PhantomOS.

# PhantomOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# PhantomOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with PhantomOS.  If not, see <https://www.gnu.org/licenses/>.

# PhantomOS is additionally distributed with a system call exemption
# As an exeption to the above license, 
#  proprietary software may interface with this software through the use of 
#  "system calls" to access any of the routines made available by the PhantomOS 
#  to programs written to be employed by the user.




cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cross/toolchain.cmake CACHE FILEPATH "Use the toolchain provided by the build script by default")
project(PhantomOS C ASM)

message(STATUS "Building Phantom for ${PHANTOM_TARGET_NAME}")
if(NOT DEFINED PHANTOMOS_USE_LLD_INIT_SET)
    if(WIN32)
    set(_PHANTOMOS_USE_LLD_INIT ON)
    else()
    find_program(DETECT_LLD NAMES ld.lld ${PHANTOM_TARGET_NAME}-ld.lld)
    if(DETECT_LLD)
        set(_PHANTOMOS_USE_LLD_INIT ON)
    else()
        set(_PHANTOMOS_USE_LLD_INIT OFF)
    endif()
    endif()
    set(PHANTOMOS_USE_LLD_INIT_SET "" CACHE INTERNAL "")
endif()
option(PHANTOMOS_USE_LLD "Use lld to link, instead of gnu ld" ${_PHANTOMOS_USE_LLD_INIT})

if(PHANTOMOS_USE_LLD)
    message(STATUS "Linking with lld")
    add_link_options(-fuse-ld=lld)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include_directories(include)

add_compile_options(-Wno-multichar -Wno-int-to-pointer-cast -nostdinc)

add_subdirectory(filesystems)

add_subdirectory(ld)
add_subdirectory(loader)

include(GNUInstallDirs)

set(PHANTOMOS_INSTALL_BOOTDIR boot CACHE PATH "Path to install the kernel and map into")

option(PHANTOMOS_ENABLE_L5PAGING "Enables use of the PML5T on processors that support it" OFF)
mark_as_advanced(PHANTOMOS_ENABLE_L5PAGING)
option(PHANTOMOS_ENABLE_UEFI_SUPPORT "Enables support for UEFI Platforms" OFF)


if(IS_ABSOLUTE ${PHANTOMOS_INSTALL_BOOTDIR})
    set(PHANTOMOS_FULL_INSTALL_BOOTDIR ${PHANTOMOS_INSTALL_BOOTDIR})
elseif(CMAKE_INSTALL_PREFIX STREQUAL "/usr" OR CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
    set(PHANTOMOS_FULL_INSTALL_BOOTDIR "/${PHANTOMOS_INSTALL_BOOTDIR}")
else()
    set(PHANTOMOS_FULL_INSTALL_BOOTDIR "${CMAKE_INSTALL_PREFIX}/${PHANTOMOS_INSTALL_BOOTDIR}")
endif()

message(STATUS "Installing Kernel to ${PHANTOMOS_FULL_INSTALL_BOOTDIR}")


set(PHANTOMOS_KERNEL_DYNLIBPATH /system/lib CACHE PATH "Path within the Search prefix to search for kernel libraries")
set(PHANTOMOS_KERNEL_SEARCH_PREFIX /boot;/ CACHE PATH "Paths to Search for the kernel and modules") 
set(PHANTOMOS_INSTALL_DYNLIBDIR system/lib CACHE PATH "Path to install kernel libraries into (relative to PHANTOMOS_INSTALL_BOOTDIR)")
if(IS_ABSOLUTE ${PHANTOMOS_INSTALL_DYNLIBDIR})
    set(PHANTOMSOS_FULL_INSTALL_DYNLIBDIR ${PHANTOMOS_INSTALL_DYNLIBDIR})
else()
    set(PHANTOMSOS_FULL_INSTALL_DYNLIBDIR ${PHANTOMOS_FULL_INSTALL_BOOTDIR}/${PHANTOMOS_INSTALL_DYNLIBDIR})
endif()


message(STATUS "Installing Kernel Libraries to ${PHANTOMSOS_FULL_INSTALL_DYNLIBDIR}")


add_executable(phantom src/start_kernel.c src/printk.c src/interrupts.S include/MachineInfo.h src/machine_info.S include/types.h
        src/memcpy.c include/bus.h src/bus.S src/acpi.S
        include/acpi.h include/elf.h include/memcpy.h include/memory.h)

target_compile_options(phantom PRIVATE -mno-red-zone -msse -mno-mmx -msse2 -mno-sse3 -mno-ssse3 -mno-sse4)

target_link_options(phantom PRIVATE "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/phantom.map")

target_link_libraries(phantom loader-amd64 phantom-kernel-ld-scripts)

install(TARGETS phantom-image DESTINATION ${PHANTOMOS_INSTALL_BOOTDIR})

