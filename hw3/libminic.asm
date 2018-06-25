%macro gen_sys 2
	global sys_%2:function
sys_%2:
	push	r10
	mov		r10, rcx
	mov		rax, %1
	syscall
	pop		r10
	ret

	global %2:function
%2:
	call	sys_%2
	ret

%endmacro

	section .data

	section .text

	gen_sys	0, read
	gen_sys 1, write
	gen_sys 13, rt_sigaction
	gen_sys 14, rt_sigprocmask
	gen_sys 34, pause
	gen_sys 35, nanosleep
	gen_sys 37, alarm
	gen_sys 60, exit

	global sleep:function
sleep:
	sub		rsp, 16
	mov		QWORD [rsp+8], 0
	mov		[rsp], rdi
	xor		rax, rax
	mov		rdi, rsp
	xor		rsi, rsi
	call	sys_nanosleep
	add		rsp, 16
	ret

	global sigaction:function
sigaction:
	push	rcx
	or		QWORD [rsi+8], 0x04000000
	lea		rcx, [rel sys_rt_sigreturn]
	mov		[rsi+16], rcx
	mov		rcx, 8
	call	sys_rt_sigaction
	pop		rcx
	ret

	global sigprocmask:function
sigprocmask:
	push	rcx
	mov		rcx, 8
	call	sys_rt_sigprocmask
	pop		rcx
	ret

	global setjmp:function
setjmp:
	pop		rdx
	mov		[rdi], rbx
	mov		[rdi+8], rsp
	mov		[rdi+16], rbp
	mov		[rdi+24], r12
	mov		[rdi+32], r13
	mov		[rdi+40], r14
	mov		[rdi+48], r15
	mov		[rdi+56], rdx
	push	rdx
	lea		rdx, [rdi+64]		;old_set
	mov		rsi, 0			;set
	mov		rdi, 2			;how
	call	sigprocmask
	xor		rax, rax
	pop		rdx
	jmp		rdx

	global longjmp:function
longjmp:
	mov		rax, rsi
	mov		rbx, [rdi]
	mov		rsp, [rdi+8]
	mov		rbp, [rdi+16]
	mov		r12, [rdi+24]
	mov		r13, [rdi+32]
	mov		r14, [rdi+40]
	mov		r15, [rdi+48]
	mov		rdx, [rdi+56]
	push	rdx
	push	rax
	mov		rdx, 0			;old_set
	lea		rsi, [rdi+64]		;set
	mov		rdi, 2			;how
	call	sigprocmask
	pop		rax
	pop		rdx
	test	rax, rax
	jne		.Lskip
	mov		rax, 1
.Lskip:	
	jmp		rdx

	global sys_rt_sigreturn:function
sys_rt_sigreturn:
	mov		rax, 15
	syscall
	ret

