%ifndef PROTECTED_MODE_HELPERS_ASM
%define PROTECTED_MODE_HELPERS_ASM

;globals
VGA_WIDTH  equ 80
VGA_HEIGHT equ 25
VGA_MEM    equ 0xB8000
;
%macro print_char 4
    push eax
    push ebx
    push edx

    mov eax, %2
    mov ebx, VGA_WIDTH
    mul ebx
    add eax, %3
    shl eax, 1
    mov edx, VGA_MEM
    add edx, eax

    mov ah, %4
    mov al, %1
    mov [edx], ax

    pop edx
    pop ebx
    pop eax
%endmacro

%macro fill_screen 1
    xor ecx, ecx
    .row_loop:
        xor eax, eax
        .col_loop:
            mov edx, ecx
            imul edx, VGA_WIDTH
            add edx, eax
            shl edx, 1
            add edx, VGA_MEM

            mov word [edx], %1

            inc eax
            cmp eax, VGA_WIDTH
            jne .col_loop

        inc ecx
        cmp ecx, VGA_HEIGHT
        jne .row_loop
%endmacro

%endif
