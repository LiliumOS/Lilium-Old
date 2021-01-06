add_subdirectory(loader)


add_library(phantom-arch-x86_64 STATIC src/start_kernel.c src/interrupts.S 
            include/MachineInfo.h src/machine_info.S include/types.h
            include/bus.h src/bus.S src/acpi.S include/acpi.h
            src/printk.c)

