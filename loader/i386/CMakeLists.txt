
set(CMAKE_C_COMPILER_TARGET i386-pc-none-elf)
set(CMAKE_ASM_COMPILER_TARGET i386-pc-none-elf)

file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/img-include.s
        INPUT ${CMAKE_CURRENT_SOURCE_DIR}/img-include.s)


add_executable(phantom-image loader-i386.S osimg.c ${CMAKE_CURRENT_BINARY_DIR}/img-include.s memcpy.c)
set_target_properties(phantom-image
        PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/i386-pc-phantom-loader.ld)

target_link_options(phantom-image PRIVATE "-Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/i386-pc-phantom-loader.ld")

add_dependencies(phantom-image phantom)