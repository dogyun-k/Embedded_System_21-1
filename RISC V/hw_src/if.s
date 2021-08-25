	.file	"if.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$87, -8(%rbp)
	cmpl	$79, -8(%rbp)
	jle	.L2
	movl	$1, -4(%rbp)
	jmp	.L3
.L2:
	cmpl	$79, -8(%rbp)
	jg	.L4
	cmpl	$59, -8(%rbp)
	jle	.L4
	movl	$2, -4(%rbp)
	jmp	.L3
.L4:
	cmpl	$59, -8(%rbp)
	jg	.L5
	cmpl	$39, -8(%rbp)
	jle	.L5
	movl	$3, -4(%rbp)
	jmp	.L3
.L5:
	cmpl	$39, -8(%rbp)
	jg	.L6
	cmpl	$19, -8(%rbp)
	jle	.L6
	movl	$4, -4(%rbp)
	jmp	.L3
.L6:
	movl	$5, -4(%rbp)
.L3:
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 8.4.0-3ubuntu2) 8.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
