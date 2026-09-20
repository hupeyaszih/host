[org 0x7e00]
; stage 2 aims to enable long mode, prepare other things and jump to kmain

%include "boot/booting_helpers.asm"
; Start of code
jmp main

enable_A20:
    mov ax, 0x2401
    int 0x15
    jc .A20_err
    ret

    .A20_err :
        print_err ERR_A20
        ret

prepare_GDT:
    print_err ERR_DEFAULT
    ret

main:
    call enable_A20
    call prepare_GDT
    jmp $

; End of code
times 512-($-$$) db 0
