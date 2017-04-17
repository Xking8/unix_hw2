	.file	"hw2.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.local	_ZL10old_getuid
	.comm	_ZL10old_getuid,8,8
	.local	_ZL10old_getenv
	.comm	_ZL10old_getenv,8,8
	.local	_ZL11old_opendir
	.comm	_ZL11old_opendir,8,8
	.globl	out
	.bss
	.align 8
	.type	out, @object
	.size	out, 8
out:
	.zero	8
	.section	.rodata
.LC0:
	.string	"w"
.LC1:
	.string	"monitor.out"
.LC2:
	.string	"MONITOR_OUTPUT"
.LC3:
	.string	"stderr"
.LC4:
	.string	"n=%d\n"
	.text
	.type	_ZL6myinitv, @function
_ZL6myinitv:
.LFB1085:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$.LC0, %esi
	movl	$.LC1, %edi
	call	fopen
	movq	%rax, out(%rip)
	movl	$.LC2, %edi
	call	getenv
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L4
	movq	-8(%rbp), %rax
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	strcmp
	testl	%eax, %eax
	jne	.L4
	movq	out(%rip), %rax
	movq	%rax, %rdi
	call	fileno
	movl	%eax, %esi
	movl	$2, %edi
	call	dup2
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
.L4:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1085:
	.size	_ZL6myinitv, .-_ZL6myinitv
	.section	.init_array,"aw"
	.align 8
	.quad	_ZL6myinitv
	.section	.rodata
.LC5:
	.string	"libc.so.6"
.LC6:
	.string	"getuid"
.LC7:
	.string	"[monitor] getuid() = %d\n"
	.align 8
.LC8:
	.string	"---[monitor]old_getuid is NULL"
	.text
	.globl	getuid
	.type	getuid, @function
getuid:
.LFB1086:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	_ZL10old_getuid(%rip), %rax
	testq	%rax, %rax
	jne	.L6
	movl	$1, %esi
	movl	$.LC5, %edi
	call	dlopen
	movq	%rax, -32(%rbp)
	call	dlerror
	movq	%rax, -24(%rbp)
	cmpq	$0, -32(%rbp)
	je	.L6
	call	dlerror
	movl	$_ZL10old_getuid, %ebx
	movq	-32(%rbp), %rax
	movl	$.LC6, %esi
	movq	%rax, %rdi
	call	dlsym
	movq	%rax, (%rbx)
.L6:
	movq	_ZL10old_getuid(%rip), %rax
	testq	%rax, %rax
	je	.L8
	movq	_ZL10old_getuid(%rip), %rax
	call	*%rax
	movl	%eax, %edx
	movq	out(%rip), %rax
	movl	$.LC7, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	jmp	.L9
.L8:
	movq	out(%rip), %rax
	movq	%rax, %rcx
	movl	$30, %edx
	movl	$1, %esi
	movl	$.LC8, %edi
	call	fwrite
.L9:
	movq	_ZL10old_getuid(%rip), %rax
	call	*%rax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1086:
	.size	getuid, .-getuid
	.section	.rodata
.LC9:
	.string	"getenv"
	.align 8
.LC10:
	.string	"[monitor] getenv('%s') = '%s'\n"
	.align 8
.LC11:
	.string	"---[monitor]old_getenv is NULL"
	.text
	.globl	getenv
	.type	getenv, @function
getenv:
.LFB1087:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1087
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	_ZL10old_getenv(%rip), %rax
	testq	%rax, %rax
	jne	.L12
	movl	$1, %esi
	movl	$.LC5, %edi
	call	dlopen
	movq	%rax, -32(%rbp)
	call	dlerror
	movq	%rax, -24(%rbp)
	cmpq	$0, -32(%rbp)
	je	.L12
	call	dlerror
	movl	$_ZL10old_getenv, %ebx
	movq	-32(%rbp), %rax
	movl	$.LC9, %esi
	movq	%rax, %rdi
	call	dlsym
	movq	%rax, (%rbx)
.L12:
	movq	_ZL10old_getenv(%rip), %rax
	testq	%rax, %rax
	je	.L14
	movq	-40(%rbp), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L15
	movq	_ZL10old_getenv(%rip), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rdi
.LEHB0:
	call	*%rax
	movq	%rax, %rcx
	movq	out(%rip), %rax
	movq	-40(%rbp), %rdx
	movl	$.LC10, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	jmp	.L15
.L14:
	movq	out(%rip), %rax
	movq	%rax, %rcx
	movl	$30, %edx
	movl	$1, %esi
	movl	$.LC11, %edi
	call	fwrite
.L15:
	movq	_ZL10old_getenv(%rip), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
.LEHE0:
	jmp	.L20
.L19:
	cmpq	$-1, %rdx
	je	.L18
	movq	%rax, %rdi
.LEHB1:
	call	_Unwind_Resume
.L18:
	movq	%rax, %rdi
	call	__cxa_call_unexpected
.LEHE1:
.L20:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1087:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
	.align 4
.LLSDA1087:
	.byte	0xff
	.byte	0x3
	.uleb128 .LLSDATT1087-.LLSDATTD1087
.LLSDATTD1087:
	.byte	0x1
	.uleb128 .LLSDACSE1087-.LLSDACSB1087
.LLSDACSB1087:
	.uleb128 .LEHB0-.LFB1087
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L19-.LFB1087
	.uleb128 0x1
	.uleb128 .LEHB1-.LFB1087
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE1087:
	.byte	0x7f
	.byte	0
	.align 4
.LLSDATT1087:
	.byte	0
	.text
	.size	getenv, .-getenv
	.section	.rodata
.LC12:
	.string	"opendir"
	.align 8
.LC13:
	.string	"[monitor] opendir('%s') = '%d'\n"
	.align 8
.LC14:
	.string	"---[monitor]old_opendir is NULL"
	.text
	.globl	opendir
	.type	opendir, @function
opendir:
.LFB1088:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	_ZL11old_opendir(%rip), %rax
	testq	%rax, %rax
	jne	.L22
	movl	$1, %esi
	movl	$.LC5, %edi
	call	dlopen
	movq	%rax, -32(%rbp)
	call	dlerror
	movq	%rax, -24(%rbp)
	cmpq	$0, -32(%rbp)
	je	.L22
	call	dlerror
	movl	$_ZL11old_opendir, %ebx
	movq	-32(%rbp), %rax
	movl	$.LC12, %esi
	movq	%rax, %rdi
	call	dlsym
	movq	%rax, (%rbx)
.L22:
	movq	_ZL11old_opendir(%rip), %rax
	testq	%rax, %rax
	je	.L24
	movq	_ZL11old_opendir(%rip), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	movq	%rax, %rcx
	movq	out(%rip), %rax
	movq	-40(%rbp), %rdx
	movl	$.LC13, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	jmp	.L25
.L24:
	movq	out(%rip), %rax
	movq	%rax, %rcx
	movl	$31, %edx
	movl	$1, %esi
	movl	$.LC14, %edi
	call	fwrite
.L25:
	movq	_ZL11old_opendir(%rip), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1088:
	.size	opendir, .-opendir
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1089:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L29
	cmpl	$65535, -8(%rbp)
	jne	.L29
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L29:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1089:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_out, @function
_GLOBAL__sub_I_out:
.LFB1090:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1090:
	.size	_GLOBAL__sub_I_out, .-_GLOBAL__sub_I_out
	.section	.init_array
	.align 8
	.quad	_GLOBAL__sub_I_out
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
