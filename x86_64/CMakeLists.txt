add_library(phantom-arch-x86_64-options INTERFACE)
target_compile_options(phantom-arch-x86_64-options INTERFACE -fno-exceptions -mcmodel=large -mno-red-zone -msse -mno-mmx -msse2 -mno-sse3 -mno-ssse3 -mno-sse4 -fPIE -static-pie)
target_link_options(phantom-arch-x86_64-options INTERFACE -mcmodel=large)

add_subdirectory(loader)

option(PHANTOMOS_ENABLE_L5PAGING "Enables use of the PML5T on processors that support it" OFF)
mark_as_advanced(PHANTOMOS_ENABLE_L5PAGING)


add_library(phantom-arch-x86_64 STATIC src/start_kernel.c src/interrupts.S src/kmap.c src/kalloc.c
            include/MachineInfo.h src/machine_info.S include/types.h
            include/bus.h src/bus.S src/acpi.S include/acpi.h src/memcpy.c
            src/printk.c  include/memory.h)


target_link_libraries(phantom-arch-x86_64 PUBLIC phantom-arch-x86_64-options)
