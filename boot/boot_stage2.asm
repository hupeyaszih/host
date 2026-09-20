[org 0x7e00]
; stage 2 aims to enable long mode, prepare other things and jump to kmain

jmp main

%include "boot/booting_helpers.asm"
%include "boot/gdt.asm"
[bits 16]
; Start of code

enable_A20:
    in al, 0x92
    test al, 2
    jnz .done

    mov ax, 0x2401
    int 0x15
    jnc .done

    in al, 0x92
    or al, 2
    out 0x92, al
    jmp .done

    print_err TASK_TURN_ON_A20
    .done :
        ret

main:
    call enable_A20
    jmp prepare_GDT

; End of code
times 512-($-$$) db 0
