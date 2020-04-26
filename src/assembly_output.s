	.text
.globl main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $12, %rbp
	movl $3, -4(%rbp)
	movl $0, %eax
	popq %rbp
	ret
