
.global __head

.section .data.img, "w"
__head:
.incbin "$<TARGET_FILE:phantom>"