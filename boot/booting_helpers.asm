%ifndef BOOTING_HELPERS_ASM
%define BOOTING_HELPERS_ASM

;TASK CODES
ALL_TASKS            equ '0'
TASK_DEFAULT         equ '1'
TASK_TURN_ON_A20     equ '2'
TASK_PREP_GDT        equ '3'
TASK_CREATE_MEM_MAP  equ '4'
;

%macro print 1
mov ah, 0xE
mov al, %1
int 0x10
%endmacro

%macro print_err 1
print 'e'
print 'r'
print 'r'
print ':'
print ' '
print %1
print ' '
%endmacro

%macro print_ok 1
print 'o'
print 'k'
print ':'
print ' '
print %1
print ' '
%endmacro

%endif
