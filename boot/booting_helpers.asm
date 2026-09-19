;ERR CODES
ERR_DEFAULT equ '1'
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
