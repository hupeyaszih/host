%ifndef LONG_MODE_ASSEMBLY
%define LONG_MODE_ASSEMBLY
; long_mode.asm aims to enable long_mode and jump to the kernel

[bits 32]
EFLAGS_ID equ 1 << 21
CPUID_EXTENSIONS equ 0x80000000
CPUID_EXT_FEATURES equ 0x80000001

check_CPUID:
    pushfd
    pop eax

    mov ecx, eax
    xor eax, EFLAGS_ID

    push eax
    popfd
    pushfd
    pop eax

    push ecx
    popfd

    xor eax, ecx
    jnz .supported
    .not_supported:
        mov eax, 0
        ret
    .supported:
        mov eax, 1
        ret

does_support_long_mode:
    mov eax, CPUID_EXTENSIONS
    cpuid
    cmp eax, CPUID_EXT_FEATURES
    ret

CR0_PAGING equ 1 << 31
disable_paging_for_32:
    mov eax, cr0
    and eax, ~CR0_PAGING
    mov cr0, eax
    ret



PML4T_ADDR equ 0x1000
SIZEOF_PAGE_TABLE equ 4096

PML4T_ADDR equ 0x1000
PDPT_ADDR equ 0x2000
PDT_ADDR equ 0x3000
PT_ADDR equ 0x4000

PT_ADDR_MASK equ 0xffffffffff000
PT_PRESENT equ 1
PT_READABLE equ 2

ENTRIES_PER_PT equ 512
SIZEOF_PT_ENTRY equ 8
PAGE_SIZE equ 0x1000

CR4_PAE_ENABLE equ 1 << 5
enable_paging_for_64:
    mov edi, PML4T_ADDR
    mov cr3, edi

    xor eax, eax
    mov ecx, SIZEOF_PAGE_TABLE
    rep stosd
    mov edi, cr3

    mov DWORD [edi], PDPT_ADDR & PT_ADDR_MASK | PT_PRESENT | PT_READABLE

    mov edi, PDPT_ADDR
    mov DWORD [edi], PDT_ADDR & PT_ADDR_MASK | PT_PRESENT | PT_READABLE

    mov edi, PDT_ADDR
    mov DWORD [edi], PT_ADDR & PT_ADDR_MASK | PT_PRESENT | PT_READABLE


    mov edi, PT_ADDR
    mov ebx, PT_PRESENT
    mov ecx, ENTRIES_PER_PT

    ;PAE

    mov edi, PT_ADDR
    mov ebx, PT_PRESENT | PT_READABLE
    mov ecx, ENTRIES_PER_PT

    .SetEntry:
        mov DWORD [edi], ebx
        add ebx, PAGE_SIZE
        add edi, SIZEOF_PT_ENTRY

        loop .SetEntry

    mov eax, cr4
    or eax, CR4_PAE_ENABLE
    mov cr4, eax
    ret

EFER_MSR equ 0xC0000080
EFER_LM_ENABLE equ 1 << 8

CR0_PM_ENABLE equ 1 << 0
CR0_PG_ENABLE equ 1 << 31
switch_to_compatibility_mode:
    mov ecx, EFER_MSR
    rdmsr
    or eax, EFER_LM_ENABLE
    wrmsr


    mov eax, cr0
    or eax, CR0_PG_ENABLE | CR0_PM_ENABLE

    mov cr0, eax
    ret

enable_long_mode:
    call check_CPUID
    cmp eax, 0
    je no_cpuid_instruction_support

    call does_support_long_mode
    jz no_long_mode_support
    ; I have to implement 32-bit support in the future. But now, it only supports x86-64 CPUs

    print_char '0', 0, 0, 0x0B ; step 1 is successful

    call disable_paging_for_32

    print_char '1', 0, 0, 0x0B ; step 2 is successful

    call enable_paging_for_64

    print_char '2', 0, 0, 0x0B ; step 3 is successful

    call switch_to_compatibility_mode

    print_char '3', 0, 0, 0x0B ; step 4 is successful

    jmp $

no_cpuid_instruction_support:
    jmp $

no_long_mode_support:
    jmp $


;Note: Some implementation details, structures, and initialization sequences are based on tutorials and guides provided by the OSDev Wiki

%endif
