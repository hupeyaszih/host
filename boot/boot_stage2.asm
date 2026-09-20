[org 0x7e00]
; stage 2 aims to enable long mode, prepare other things and jump to kmain

%include "boot/booting_helpers.asm"
; Start of code

jmp main

some_func:
    print_err ERR_DEFAULT
    ret

main:
    call some_func
    jmp $

; End of code
times 512-($-$$) db 0
