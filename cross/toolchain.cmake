# ld/CMakeLists.txt
# 
# This file is part of PhantomOS.
#
# PhantomOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PhantomOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PhantomOS.  If not, see <https://www.gnu.org/licenses/>.
#
# PhantomOS is additionally distributed with a system call exemption
# As an exeption to the above license, 
#  proprietary software may interface with this software through the use of 
#  "system calls" to access any of the routines made available by the PhantomOS 
#  to programs written to be employed by the user.

string(TOLOWER ${CMAKE_HOST_SYSTEM_PROCESSOR} _PHANTOMOS_HOST_SYSTEM)
if(_PHANTOMOS_HOST_SYSTEM STREQUAL "amd64")
    set(_PHANTOMOS_HOST_SYSTEM "x86_64")
endif()


set(CMAKE_CROSSCOMPILING ON)
set(PHANTOMOS_TARGET_PROCESSOR ${_PHANTOMOS_HOST_SYSTEM} CACHE STRING "Set the name of the target. Only x86_64 is supported currently")
set(PHANTOM_TARGET_NAME ${PHANTOMOS_TARGET_PROCESSOR}-pc-phantom-kernel)

find_program(CMAKE_C_COMPILER NAMES $ENV{CC} clang ${PHANTOM_TARGET_NAME}-clang ${PHANTOM_TARGET_NAME}-cc ${PHANTOM_TARGET_NAME}-gcc
        REQUIRED)

find_program(QEMU qemu-system-${PHANTOMOS_TARGET_PROCESSOR})

if(QEMU)
    set(CMAKE_CROSSCOMPILING_EMULATOR ${QEMU} -kernel)
endif()

set(CMAKE_C_COMPILER_TARGET ${PHANTOM_TARGET_NAME})
set(CMAKE_ASM_COMPILER_TARGET ${PHANTOM_TARGET_NAME})

find_program(CMAKE_AR NAMES $ENV{AR} ${PHANTOM_TARGET_NAME}-ar llvm-ar ${PHANTOM_TARGET_NAME}-llvm-ar ar
        REQUIRED)
find_program(CMAKE_RANLIB NAMES $ENV{RANLIB} ${PHANTOM_TARGET_NAME}-ranlib llvm-ranlib ${PHANTOM_TARGET_NAME}-llvm-ranlib ranlib
        REQUIRED)

find_program(CMAKE_STRIP NAMES $ENV{STRIP} ${PHANTOM_TARGET_NAME}-strip llvm-strip ${PHANTOM_TARGET_NAME}-llvm-strip strip
        REQUIRED)
find_program(CMAKE_OBJCOPY NAMES $ENV{OBJCOPY} ${PHANTOM_TARGET_NAME}-objcopy llvm-objcopy ${PHANTOM_TARGET_NAME}-llvm-objcopy objcopy
        REQUIRED)

set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -fno-lto")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -static")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -nodefaultlibs -nostartfiles -flinker-output=dyn")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(PHANTOM_TOOLCHAIN_PRESENT "yes")
