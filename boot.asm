; boot.asm - kellynelson 초기 부팅 코드 (NASM, Multiboot v1)
;
; QEMU의 -kernel 옵션(멀티부트 로더)이 이 커널을 32비트 보호 모드로 적재한다.
; 32비트 진입부에서 롱 모드 지원 여부를 확인하고, 4단계 페이지 테이블로
; 첫 1 GiB를 아이덴티티 매핑(2 MiB 페이지)한 뒤 PAE -> EFER.LME -> PG 순서로
; 64비트 롱 모드에 진입하여 C 커널 메인(kernel_main)으로 제어권을 넘긴다.

MB_MAGIC    equ 0x1BADB002
MB_FLAGS    equ (1 << 0) | (1 << 1)         ; 모듈 페이지 정렬 + 메모리 정보 요청
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

VGA_BUFFER  equ 0xB8000

CR0_PG      equ 1 << 31
CR4_PAE     equ 1 << 5
EFER_MSR    equ 0xC0000080
EFER_LME    equ 1 << 8

PTE_P       equ 1 << 0                      ; Present
PTE_W       equ 1 << 1                      ; Writable
PTE_PS      equ 1 << 7                      ; 2 MiB 큰 페이지

section .multiboot
align 4
    dd MB_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM

section .bss
align 4096
pml4:       resb 4096
pdpt:       resb 4096
pd:         resb 4096
stack_bottom:
    resb 16384                              ; 16 KiB 커널 스택
stack_top:

section .rodata
align 8
gdt64:
    dq 0                                    ; 널 디스크립터
.code: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)   ; 64비트 코드 세그먼트
.data: equ $ - gdt64
    dq (1 << 41) | (1 << 44) | (1 << 47)                ; 데이터 세그먼트
.ptr:
    dw $ - gdt64 - 1
    dq gdt64

; ------------------------------------------------------------------
; 32비트 보호 모드 진입부
; ------------------------------------------------------------------
section .text
bits 32
global _start
extern kernel_main

_start:
    cli
    mov esp, stack_top
    mov edi, eax                            ; multiboot magic 보존
    mov esi, ebx                            ; multiboot info 주소 보존

    call check_cpuid
    call check_long_mode
    call setup_page_tables
    call enable_paging

    lgdt [gdt64.ptr]
    jmp gdt64.code:long_mode_start

; CPUID 명령 지원 여부: EFLAGS.ID(비트 21)를 토글할 수 있는지 확인
check_cpuid:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    je .no_cpuid
    ret
.no_cpuid:
    mov al, '1'
    jmp boot_error

; 확장 CPUID 0x80000001 의 EDX.LM(비트 29) 확인
check_long_mode:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode
    ret
.no_long_mode:
    mov al, '2'
    jmp boot_error

; PML4[0] -> PDPT[0] -> PD[0..511] (2 MiB x 512 = 1 GiB 아이덴티티 매핑)
setup_page_tables:
    mov eax, pdpt
    or eax, PTE_P | PTE_W
    mov [pml4], eax

    mov eax, pd
    or eax, PTE_P | PTE_W
    mov [pdpt], eax

    xor ecx, ecx
.map_pd:
    mov eax, 0x200000
    mul ecx                                 ; eax = ecx * 2 MiB
    or eax, PTE_P | PTE_W | PTE_PS
    mov [pd + ecx * 8], eax
    inc ecx
    cmp ecx, 512
    jne .map_pd
    ret

enable_paging:
    mov eax, pml4
    mov cr3, eax

    mov eax, cr4
    or eax, CR4_PAE
    mov cr4, eax

    mov ecx, EFER_MSR
    rdmsr
    or eax, EFER_LME
    wrmsr

    mov eax, cr0
    or eax, CR0_PG
    mov cr0, eax
    ret

; 부팅 실패 시 0xB8000 에 "ERR: n" 을 빨간색으로 표시하고 정지
boot_error:
    mov dword [VGA_BUFFER],     0x4F524F45  ; 'E','R'
    mov dword [VGA_BUFFER + 4], 0x4F3A4F52  ; 'R',':'
    mov dword [VGA_BUFFER + 8], 0x4F204F20  ; ' ',' '
    mov byte  [VGA_BUFFER + 10], al
.hang:
    cli
    hlt
    jmp .hang

; ------------------------------------------------------------------
; 64비트 롱 모드
; ------------------------------------------------------------------
bits 64
long_mode_start:
    mov ax, gdt64.data
    mov ds, ax
    mov es, ax
    mov ss, ax
    xor ax, ax
    mov fs, ax
    mov gs, ax

    ; 0xB8000 직접 제어: 화면 좌상단에 "64" 표시 (롱 모드 진입 확인용)
    mov dword [VGA_BUFFER], 0x0A340A36      ; '6','4' / 밝은 초록

    ; System V AMD64 호출 규약: rdi = magic, rsi = multiboot info
    mov edi, edi
    mov esi, esi
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
