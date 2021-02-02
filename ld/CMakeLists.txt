
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

add_library(phantom-kernel-ld-scripts INTERFACE)

add_dependencies(phantom-kernel-ld-scripts ${CMAKE_CURRENT_SOURCE_DIR}/${PHANTOMOS_TARGET_PROCESSOR}-pc-phantom-kernel.ld)

set_target_properties(phantom-kernel-ld-scripts PROPERTIES
        INTERFACE_LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PHANTOMOS_TARGET_PROCESSOR}-pc-phantom-kernel.ld)

target_link_options(phantom-kernel-ld-scripts INTERFACE "-Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_PROCESSOR}-pc-phantom-kernel.ld")

add_library(phantom-module-ld-scripts INTERFACE)
add_dependencies(phantom-module-ld-scripts ${CMAKE_CURRENT_SOURCE_DIR}/${PHANTOMOS_TARGET_PROCESSOR}-pc-phantom-kernel-modules.ld)

set_target_properties(phantom-module-ld-scripts PROPERTIES
        INTERFACE_LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PHANTOMOS_TARGET_PROCESSOR}-pc-phantom-kernel-modules.ld)

target_link_options(phantom-module-ld-scripts INTERFACE "-Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_SYSTEM_PROCESSOR}-pc-phantom-kernel-modules.ld")

install(FILES x86_64-pc-phantom-kernel-modules.ld
        DESTINATION ${PHANTOMSOS_FULL_INSTALL_DYNLIBDIR}/)
