# Multiboot2-compatible entry boundary placeholder for the first freestanding milestone
.section .text
.global _start
.extern kernel_main
_start:
  cli
  call kernel_main
1: hlt
  jmp 1b
.section .note.GNU-stack,"",@progbits
