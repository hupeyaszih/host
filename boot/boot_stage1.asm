bits 16

[org 0x7c00]

; Stage 1 aims to prepare stack, read stage 2 and jump to it
;; constants
SECTORS_TO_READ equ 4
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
    push ax

    mov ah, 0xE
    mov al, 'E'
    int 0x10

    pop ax
    mov al, ah

    call print_hex

    cli
    hlt

print_hex:
    push ax
    push bx
    push cx
    push dx

    mov cx, 2
.loop:
    rol al, 4
    mov bl, al
    and bl, 0x0F
    cmp bl, 10
    jl .num
    add bl, 7
.num:
    add bl, '0'

    mov ah, 0x0E
    mov al, bl
    int 0x10

    dec cx
    jnz .loop

    pop dx
    pop cx
    pop bx
    pop ax
    ret

times 510-($-$$) db 0
dw 0xaa55
