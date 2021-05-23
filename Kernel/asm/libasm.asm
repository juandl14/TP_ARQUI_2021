GLOBAL cpuVendor
GLOBAL RTC
GLOBAL getKey

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

RTC:
	push rbp
	mov rbp, rsp

	mov rax, rdi
	out 70h, al
	in al, 71h

	mov rsp, rbp
	pop rbp
	ret

getKey:
	push rbp
	mov rbp, rsp
	mov rax, 0	
loop:
	in al, 0x64
	and al, 0x01
	cmp al, 0
	je loop
	in al, 0x60

	mov rsp, rbp
	pop rbp
	ret