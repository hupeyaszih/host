bits 16

[org 0x7c00]

; Stage 1 aims to prepare stack, read stage 2 and jump to it
;; constants
SECTORS_TO_READ equ 2
CYLINDER        equ 0
HEAD            equ 0
SECTOR          equ 2

;; variables
BOOT_DRIVE db 0
;

cli

; prepare stack
mov ax, 0x9000
mov ss, ax
mov sp, 0xFFFF
;

mov [BOOT_DRIVE], dl

; reset disk
mov ah, 0x0
mov dl, [BOOT_DRIVE]
int 0x13

; read stage 2 from disk
mov ah, 0x2
mov al, SECTORS_TO_READ
mov ch, CYLINDER
mov cl, SECTOR
mov dh, HEAD
mov dl, [BOOT_DRIVE]

xor bx, bx
mov es, bx
mov bx, 0x7e00

int 0x13

; handle errors
jc .err
; jump to stage 2 
sti
jmp 0x7e00

; if an error occurs, this label is where we should jump
.err:
    mov ah, 0xE
    mov al, '1'
    int 0x10

    cli
    hlt

times 510-($-$$) db 0
dw 0xaa55
