	.text
	.globl	my_mmap
	.type	my_mmap, @function
my_mmap:
.LFB5:
	.cfi_startproc
	push   %ebp
	push   %edi
	push   %esi
	push   %ebx
	mov    %esp,%ebx
	add    $0x14,%ebx
	mov    $0x5a,%eax
	int    $0x80
	pop    %ebx
	pop    %esi
	pop    %edi
	pop    %ebp
	ret
	.cfi_endproc
.LFE5:
	.size	my_mmap, .-my_mmap
	.globl	my_munmap
	.type	my_munmap, @function
my_munmap:
.LFB6:
	.cfi_startproc
	push   %ebp
	push   %edi
	push   %esi
	push   %ebx
	mov    0x14(%esp),%ebx
	mov    0x18(%esp),%ecx
	mov    $0x5b,%eax
	int    $0x80
	pop    %ebx
	pop    %esi
	pop    %edi
	pop    %ebp
	ret
	.cfi_endproc
.LFE6:
	.size	my_munmap, .-my_munmap
	.section	.note.GNU-stack,"",@progbits
