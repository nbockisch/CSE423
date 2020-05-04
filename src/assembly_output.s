	.text
.globl testfunc
testfunc:
	pushq %rbp
	movq %rsp, %rbp
	movl %edi, -12(%rbp)
	movl -16(%rbp), %eax
	imull $10, %eax
	popq %rbp
	ret
	.text
.globl main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $8, %rbp
	movl $5, -4(%rbp)
	movl 0(%rbp), %eax
	addl $2, %eax
	movl %eax, -8(%rbp)
	cmpl $7, 0(%rbp)
	jne .IF0
	jmp .IF1
.IF0:
.IF1:
	movl 0(%rbp), %eax
	addl $1, %eax
	movl %eax, -12(%rbp)
	movl 0(%rbp), %eax
	subl $1, %eax
	movl %eax, -16(%rbp)
	movl 0(%rbp), %eax
	addl $1, %eax
	movl %eax, -20(%rbp)
	movl 0(%rbp), %edi
	call testfunc
	movl $1, %eax
	popq %rbp
	ret
