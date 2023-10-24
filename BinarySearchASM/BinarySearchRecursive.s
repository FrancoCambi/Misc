.global BSRecursive

# rdi -> arr
# rsi -> low
# rdx -> high
# rcx -> target

BSRecursive:

    # Prologo
    pushq %rbp
    movq %rsp, %rbp

    cmpq %rdx, %rsi # Comparacion de caso base
    jle recursion
    xorq %rax, %rax

    # Epilogo
    movq %rbp, %rsp
    popq %rbp
    ret

recursion:

    # rbx -> int mid

    addq %rsi, %rdx
    movq %rdx, %rax
    movq %rdx, %r15  # preservo rdx
    xorq %rdx, %rdx
    movq $2, %r14
    divq %r14
    movq %r15, %rdx # recupero rdx
    movq %rax, %rbx # Ahora (low + high) / 2 esta en rbx

    # Chequear arr[mid]

    movl (%rdi, %rbx, 4), %eax # Ahora arr[mid] esta en rax
    cmpq %rax, %rcx
    jne buscarIzqDer
    movq $1, %rax
    movq %rbp, %rsp
    popq %rbp
    ret

buscarIzqDer:

    cmpq %rax, %rcx
    jle buscarIzq # Buscamos izquierda, si no seguimos y buscamos derecha

    # low -> mid + 1 y recursion
    movq %rbx, %rsi
    incq %rsi
    call BSRecursive
    movq %rbp, %rsp
    popq %rbp
    ret

buscarIzq:

    # high -> mid - 1 y recursion

    movq %rbx, %rdx
    decq %rdx
    call BSRecursive
    movq %rbp, %rsp
    popq %rbp
    ret






