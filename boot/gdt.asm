%ifndef PREPARE_GDT_ASM
%define PREPARE_GDT_ASM

; PREPARE_GDT_ASM aims to prepare gdt (so it called PREPARE_GDT_ASM), and then jump to enable_long_mode

[bits 16]
prepare_GDT:
    cli 
 
    xor ax, ax
    mov ds, ax
 
    lgdt [gdt]
 
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:init_protected_mode


[bits 32]

%include "boot/protected_mode_helpers.asm"
%include "boot/long_mode.asm"

init_protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov esp, 0x90000

    jmp enable_long_mode


gdt_start:
    dq 0x0000000000000000 ; NULL DESCRIPTOR

    ; Kernel Code Segment
    dw 0xFFFF ; Limit (LOW)
    dw 0x0000 ; BASE (LOW)
    db 0x00   ; BASE (MID)
    db 0b10011010 ; ACCESS BYTE           ;   [Is Active (1 bit) | Privelege Level (2 bit) | Descriptor Type (1 bit) | Executable (1 bit) | DC (1 bit) | RW (1 bit) | Accessed (1 bit)]
    db 0b11001111 ; Flags and Limit (HIGH);   [Granularity (1 bit) | DB (1 bit) | Long Mode (1 bit)]
    db 0b00   ; BASE (HIGH)

    ; Kernel Data Segment
    dw 0xFFFF ; Limit (LOW)
    dw 0x0000 ; BASE (LOW)
    db 0x00   ; BASE (MID)
    db 0b10010010 ; ACCESS BYTE           ;   [Is Active (1 bit) | Privelege Level (2 bit) | Descriptor Type (1 bit) | Executable (1 bit) | DC (1 bit) | RW (1 bit) | Accessed (1 bit)]
    db 0b11001111 ; Flags and Limit (HIGH);   [Granularity (1 bit) | DB (1 bit) | Long Mode (1 bit)]
    db 0b00   ; BASE (HIGH)
gdt_end:

gdt:
    dw gdt_end - gdt_start - 1
    dd gdt_start

%endif
