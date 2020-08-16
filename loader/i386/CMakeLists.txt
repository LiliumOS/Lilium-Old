

file(GENERATE OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/img-include.s
        INPUT ${CMAKE_CURRENT_SOURCE_DIR}/img-include.s)


add_executable(phantom-image loader-i386.S osimg.c ${CMAKE_CURRENT_BINARY_DIR}/img-include.s memcpy.c)
target_compile_options(phantom-image PRIVATE "-m32" "-mno-sse" "-mno-mmx")
set_target_properties(phantom-image
        PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/i386-pc-phantom-loader.ld)

target_link_options(phantom-image PRIVATE -m32 "-Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/i386-pc-phantom-loader.ld")

add_dependencies(phantom-image phantom)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/img-include.s PROPERTIES
        OBJECT_DEPENDS phantom)