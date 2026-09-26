[org 0x7e00]
; stage 2 aims to enable A20 line and jump to prepare_GDT

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

READ_MEM_COUNT dd 0
create_mem_map:
    xor ebx, ebx
    mov di, 0x500
    .loop:
        mov edx, 0x534D4150
        mov ecx, 24
        mov eax, 0x0000E820
        int 0x15
        jc .done

        cmp eax, 0x534D4150
        jne .err

        test ecx, ecx
        jz .skip_store

        add di, 24

        .skip_store:
            mov eax, [READ_MEM_COUNT]
            add eax, 1
            mov [READ_MEM_COUNT], eax
            mov [0x4FC], eax

            test ebx, ebx
            jz .done

        jmp .loop

    .err:
        print_err TASK_CREATE_MEM_MAP
        hlt
        jmp $

    .done:
        ret

main:
    ; real hardware comes here and having triple fault, I'll fix that tomorrow
    call enable_A20
    print_err ALL_TASKS
    call create_mem_map
    print_err ALL_TASKS
    jmp prepare_GDT

; End of code
times 1024-($-$$) db 0
