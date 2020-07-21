cmake_minimum_required(VERSION 3.15)
project(FireworkOS C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

add_subdirectory(ld)
add_subdirectory(loader)

add_executable(phantom src/start_kernel.c src/printk.c)

target_link_libraries(phantom loader-amd64 phantom-kernel-ld-scripts)


