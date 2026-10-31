# Makefile - kellynelson 최소 부팅 커널
#
#   make / make all : kernel.elf 빌드
#   make run        : QEMU(x86_64)로 즉시 부팅
#   make clean      : 빌드 산출물 삭제
#
# 커널은 64비트(ELF64)로 컴파일/링크하지만, QEMU 멀티부트 로더(-kernel)는
# 32비트 ELF만 적재하므로 최종 이미지는 objcopy 로 elf32-i386 형식으로 감싼다.
# (boot.asm 이 32비트 진입 후 직접 롱 모드로 전환한다.)

# 크로스 툴체인(x86_64-elf-gcc)이 없으면 호스트 gcc/ld로 자동 대체한다.
# 강제 지정: make CROSS=x86_64-elf-  또는  make CROSS=
CROSS   ?= $(if $(shell command -v x86_64-elf-gcc 2>/dev/null),x86_64-elf-,)
CC      := $(CROSS)gcc
LD      := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
AS      := nasm
QEMU    ?= qemu-system-x86_64

CFLAGS  := -m64 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -ffreestanding -fno-builtin -fno-stack-protector -fno-pic \
           -nostdlib -nostdinc -O2 -Wall -Wextra
ASFLAGS := -f elf64
LDFLAGS := -m elf_x86_64 -z max-page-size=0x1000 -T linker.ld -nostdlib

KERNEL  := kernel.elf
OBJS    := boot.o main.o

.PHONY: all run clean

all: $(KERNEL)

kernel64.elf: $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(KERNEL): kernel64.elf
	$(OBJCOPY) -O elf32-i386 $< $@

boot.o: boot.asm
	$(AS) $(ASFLAGS) $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(KERNEL)
	$(QEMU) -kernel $(KERNEL)

clean:
	rm -f $(OBJS) $(KERNEL) kernel64.elf
