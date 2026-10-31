; isr.asm - 인터럽트 진입 스텁 (x86_64)
;
; 벡터 0~31 : CPU 예외, 벡터 32~47 : 하드웨어 IRQ 0~15 (PIC 재매핑 후)
; 각 스텁은 (오류 코드, 벡터 번호)를 스택에 쌓아 공통 루틴으로 넘기고,
; 공통 루틴은 범용 레지스터를 저장한 뒤 isr_dispatch(struct int_frame *)를 호출한다.

bits 64
section .text
extern isr_dispatch
global isr_stub_table

; 오류 코드를 CPU가 넣지 않는 예외: 0 을 넣어 스택 모양을 통일
%macro ISR_NOERR 1
isr_%1:
    push 0
    push %1
    jmp isr_common
%endmacro

; CPU가 오류 코드를 넣는 예외 (8, 10~14, 17, 21, 29, 30)
%macro ISR_ERR 1
isr_%1:
    push %1
    jmp isr_common
%endmacro

isr_common:
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    cld
    mov rdi, rsp                            ; struct int_frame *
    call isr_dispatch

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    add rsp, 16                             ; 벡터 번호 + 오류 코드 제거
    iretq

%assign i 0
%rep 48
%if i == 8 || (i >= 10 && i <= 14) || i == 17 || i == 21 || i == 29 || i == 30
    ISR_ERR i
%else
    ISR_NOERR i
%endif
%assign i i + 1
%endrep

section .rodata
align 8
isr_stub_table:
%assign i 0
%rep 48
    dq isr_ %+ i
%assign i i + 1
%endrep
