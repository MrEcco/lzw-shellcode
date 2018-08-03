	.text
	.globl	my_mmap
	.type	my_mmap, @function
my_mmap:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edx, -8(%rbp)
	movl	%ecx, -12(%rbp)
	movl	%r8d, -16(%rbp)
	movl -0x8(%rbp),%edx
	movl -0xC(%rbp),%r10d
	movl -0x10(%rbp),%r8d
	movq $9,%rax
	syscall
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	my_mmap, .-my_mmap
	.globl	my_munmap
	.type	my_munmap, @function
my_munmap:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq $11,%rax
	syscall
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	my_munmap, .-my_munmap
	.section	.note.GNU-stack,"",@progbits
