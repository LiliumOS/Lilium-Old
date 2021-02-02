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

set(PHANTOMOS_USE_LINKER "" CACHE STRING "The linker to pass to the host compiler")

if(NOT PHANTOMOS_USE_LINKER STREQUAL "")
    add_link_options("-fuse-ld=${PHANTOMOS_USE_LINKER}")
    message(STATUS "Building with linker ${PHANTOMOS_USE_LINKER}")
endif()


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include_directories(include ${PHANTOMOS_TARGET_PROCESSOR}/include)

add_compile_options(-Wno-multichar -Wno-int-to-pointer-cast -nostdinc)

add_subdirectory(filesystems)

add_subdirectory(ld)
add_subdirectory(${PHANTOMOS_TARGET_PROCESSOR})

include(GNUInstallDirs)

set(PHANTOMOS_INSTALL_BOOTDIR boot CACHE PATH "Path to install the kernel and map into")

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


add_executable(phantom src/memcpy.c include/elf.h include/memcpy.h include/memory.h)

target_link_options(phantom PRIVATE "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/phantom.map")

target_link_libraries(phantom loader-${PHANTOMOS_TARGET_PROCESSOR} phantom-arch-${PHANTOMOS_TARGET_PROCESSOR} phantom-kernel-ld-scripts)

add_custom_command(TARGET phantom POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:phantom> ${CMAKE_CURRENT_BINARY_DIR}/phantom.debug
        COMMENT "Extracting kernel debug symbols to phantom.debug")

add_custom_command(TARGET phantom POST_BUILD 
        COMMAND ${CMAKE_STRIP} $<TARGET_FILE:phantom>
        COMMENT "Removing kernel debug symbols")


install(TARGETS phantom-image DESTINATION ${PHANTOMOS_INSTALL_FULL_BOOTDIR})

add_subdirectory(threads)
