; src/asm/validate_int_input.asm
bits 64
default rel

section .text

global validateIntInputAsm
validateIntInputAsm:
    ; rcx = const char* str
    test rcx, rcx
    jz .return_false

.check_loop:
    mov al, [rcx]
    test al, al
    jz .return_true

    cmp al, '0'
    jl .return_false
    cmp al, '9'
    jg .return_false

    inc rcx
    jmp .check_loop

.return_true:
    mov rax, 1
    ret

.return_false:
    xor rax, rax
    ret