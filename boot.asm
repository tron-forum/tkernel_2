; boot.asm - kellynelson 초기 부팅 코드 (NASM, Multiboot v1)
;
; QEMU의 -kernel 옵션(멀티부트 로더)이 이 커널을 32비트 보호 모드로 적재한다.
; 진입 직후 VGA 텍스트 버퍼(0xB8000)에 부팅 표시를 남기고,
; 스택을 설정한 뒤 C 커널 메인(kernel_main)으로 제어권을 넘긴다.

MB_MAGIC    equ 0x1BADB002
MB_FLAGS    equ (1 << 0) | (1 << 1)         ; 모듈 페이지 정렬 + 메모리 정보 요청
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

VGA_BUFFER  equ 0xB8000

section .multiboot
align 4
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384                              ; 16 KiB 커널 스택
stack_top:

section .text
bits 32
global _start
extern kernel_main

_start:
    cli
    mov esp, stack_top

    ; 0xB8000 직접 제어: 화면 좌상단에 "OK" 표시 (부트 코드 도달 확인용)
    mov dword [VGA_BUFFER], 0x0A4B0A4F      ; 'O','K' / 밝은 초록

    push ebx                                ; multiboot info 구조체 주소
    push eax                                ; multiboot magic (0x2BADB002)
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
