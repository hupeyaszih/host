[org 0x7e00]
%include "boot/booting_helpers.asm"
; Start of code

print_err ERR_DEFAULT

; End of code
jmp $
times 512-($-$$) db 0
