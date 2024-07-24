%define ALIGN 1 << 0
%define MEMINFO 1 << 1
%define FLAGS (ALIGN | MEMINFO)
%define MAGIC 0x1BADB002
%define CHECKSUM -(MAGIC + FLAGS)

extern _init
extern kernel_main

section .multiboot
    align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
    align 16
stack_btm:
    resb 16384
stack_top:

section .text
    global _start
_start:
    mov esp, stack_top
    cli

    call _init
    call kernel_main
loop:
    cli
    hlt
    jmp loop
