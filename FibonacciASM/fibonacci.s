.data
strError: .asciz "Cantidad de argumentos invalida. %d \n"
str: .asciz "Resultado: %d\n"

.text
.global main

main:
    # Prologo
    pushq %rbp
    movq %rsp, %rbp

    #Chequeo argumentos
    movq %rsi, -0x8(%rbp) # argv
    decq %rdi
    cmp $1, %rdi
    je seguir
    leaq strError, %rdi
    xorq %rax, %rax
    call printf
    xorq %rax, %rax
    movq %rbp, %rsp
    popq %rbp
    ret

seguir:
    movq -0x8(%rbp), %rax
    movq 8(%rax), %rax
    movq %rax, %rdi
    xorq %rax, %rax
    call atoi
    movq %rax, %rdi # rdi <- argv[1]
    call func
    leaq str, %rdi
    movq %rax, %rsi
    call printf

fin:
    # Epilogo 
    movq %rbp, %rsp
    popq %rbp
    xorq %rax, %rax
    ret

