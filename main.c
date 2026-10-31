/*
 * main.c - kellynelson 커널 메인
 *
 * boot.asm 이 64비트 롱 모드로 전환한 뒤 제어권을 넘겨받는다.
 * 화면 출력은 vga.c 콘솔(0xB8000 직접 제어)을 사용하며,
 * 호스트 C 표준 라이브러리는 사용하지 않는다.
 */
#include "vga.h"

#define MULTIBOOT_BOOTLOADER_MAGIC  0x2BADB002

void kernel_main(unsigned int mb_magic, unsigned int mb_info)
{
	vga_init();

	vga_set_color(VGA_WHITE, VGA_BLACK);
	vga_puts("codename: kellynelson Initializing...\n");

	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	kprintf("  multiboot magic : %x %s\n", mb_magic,
		mb_magic == MULTIBOOT_BOOTLOADER_MAGIC ? "(ok)" : "(invalid)");
	kprintf("  multiboot info  : %x\n", mb_info);
	kprintf("  kernel_main     : %p\n", (void *)kernel_main);

	vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
	vga_puts("[ OK ] ");
	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	vga_puts("64-bit long mode\n");

	vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
	vga_puts("[ OK ] ");
	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	vga_puts("VGA console\n");

	for (;;)
		__asm__ volatile ("hlt");
}
