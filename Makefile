# Makefile - kellynelson 최소 부팅 커널
#
#   make / make all : kernel.elf 빌드
#   make run        : QEMU(x86_64)로 즉시 부팅
#   make clean      : 빌드 산출물 삭제
#
# QEMU 멀티부트 로더(-kernel)는 32비트 ELF만 적재하므로
# 초기 부트 단계는 x86_64-elf 툴체인의 32비트 모드(-m32 / elf_i386)로 빌드한다.

# 크로스 툴체인(x86_64-elf-gcc)이 없으면 호스트 gcc/ld로 자동 대체한다.
# 강제 지정: make CROSS=x86_64-elf-  또는  make CROSS=
CROSS   ?= $(if $(shell command -v x86_64-elf-gcc 2>/dev/null),x86_64-elf-,)
CC      := $(CROSS)gcc
LD      := $(CROSS)ld
AS      := nasm
QEMU    ?= qemu-system-x86_64

CFLAGS  := -m32 -ffreestanding -fno-builtin -fno-stack-protector -fno-pic \
           -nostdlib -nostdinc -O2 -Wall -Wextra
ASFLAGS := -f elf32
LDFLAGS := -m elf_i386 -T linker.ld -nostdlib

KERNEL  := kernel.elf
OBJS    := boot.o main.o

.PHONY: all run clean

all: $(KERNEL)

$(KERNEL): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

boot.o: boot.asm
	$(AS) $(ASFLAGS) $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(KERNEL)
	$(QEMU) -kernel $(KERNEL)

clean:
	rm -f $(OBJS) $(KERNEL)
