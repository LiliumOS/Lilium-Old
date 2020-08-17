cmake_minimum_required(VERSION 3.15)
project(PhantomOS C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include_directories(include)

add_subdirectory(ld)
add_subdirectory(loader)

add_executable(phantom src/start_kernel.c src/printk.c src/interrupts.S)

target_compile_options(phantom PRIVATE -mno-red-zone)

target_link_options(phantom PRIVATE "-Wl,-Map=phantom.map")

target_link_libraries(phantom loader-amd64 phantom-kernel-ld-scripts)


