	.text
.globl main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rbp
	movl $1, -4(%rbp)
	cmpl $0, -4(%rbp)
	je .IF0
	movl $40, -8(%rbp)
.IF0:
	cmpl $2, -4(%rbp)
	jne .IF1
	movl $10, -12(%rbp)
.IF1:
	movl $100, -16(%rbp)
	movl $0, %eax
	popq %rbp
	ret
