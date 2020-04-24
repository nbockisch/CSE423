	.text
.globl main
main:
	pushq %rbp
	movq %rsp, %rbp
	subq $12, %rbp
	ret
