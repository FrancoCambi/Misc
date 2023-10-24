.global func

func:
    pushq %rbp
    movq %rsp, %rbp

    cmpq $0x1, %rdi
    jg calc
    movq %rdi, %rax
    movq %rbp, %rsp
    popq %rbp
    ret

calc:
    decq %rdi
    pushq %rdi
    call func # Fib(n - 1)
    pushq %rax
    popq %r15
    popq %rdi
    pushq %r15
    decq %rdi
    call func # Fib(n - 2)
    popq %r15
    addq %r15, %rax

    movq %rbp, %rsp
    popq %rbp

    ret

