	.text
.globl main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rbp
	ret
