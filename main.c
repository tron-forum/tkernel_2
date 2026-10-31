/*
 * main.c - kellynelson 커널 메인
 *
 * boot.asm 이 64비트 롱 모드로 전환한 뒤 제어권을 넘겨받는다.
 * 화면 출력은 vga.c 콘솔(0xB8000 직접 제어)을 사용하며,
 * 호스트 C 표준 라이브러리는 사용하지 않는다.
 */
#include "vga.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"

#define MULTIBOOT_BOOTLOADER_MAGIC  0x2BADB002

#define STATUS_ATTR  ((VGA_BLACK << 4) | VGA_YELLOW)

static void boot_ok(const char *what)
{
	vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
	vga_puts("[ OK ] ");
	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	vga_puts(what);
	vga_putc('\n');
}

/* 화면 우측 상단에 가동 시간 표시: "uptime HH:MM:SS" */
static void show_uptime(unsigned long sec)
{
	char s[16] = "uptime 00:00:00";
	unsigned long h = sec / 3600 % 100, m = sec / 60 % 60, x = sec % 60;

	s[7]  = (char)('0' + h / 10);  s[8]  = (char)('0' + h % 10);
	s[10] = (char)('0' + m / 10);  s[11] = (char)('0' + m % 10);
	s[13] = (char)('0' + x / 10);  s[14] = (char)('0' + x % 10);
	vga_write_at(0, 80 - 15, s, STATUS_ATTR);
}

void kernel_main(unsigned int mb_magic, unsigned int mb_info)
{
	unsigned long last_sec = (unsigned long)-1;
	int c;

	vga_init();

	vga_set_color(VGA_WHITE, VGA_BLACK);
	vga_puts("codename: kellynelson Initializing...\n");

	vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
	kprintf("  multiboot magic : %x %s\n", mb_magic,
		mb_magic == MULTIBOOT_BOOTLOADER_MAGIC ? "(ok)" : "(invalid)");
	kprintf("  multiboot info  : %x\n", mb_info);

	boot_ok("64-bit long mode");
	boot_ok("VGA console");

	idt_init();
	boot_ok("IDT + exception handlers (vectors 0-31)");
	boot_ok("8259A PIC remapped to vectors 32-47");

	timer_init();
	kprintf("[ OK ] PIT timer %d Hz (IRQ0)\n", TIMER_HZ);

	keyboard_init();
	boot_ok("PS/2 keyboard (IRQ1)");

	cpu_sti();

	vga_set_color(VGA_WHITE, VGA_BLACK);
	vga_puts("\nType something:\n> ");

	for (;;) {
		unsigned long sec = timer_ticks() / TIMER_HZ;

		if (sec != last_sec) {
			last_sec = sec;
			show_uptime(sec);
		}

		while ((c = keyboard_getc()) >= 0) {
			vga_putc((char)c);
			if (c == '\n')
				vga_puts("> ");
		}

		cpu_hlt();  /* 다음 인터럽트(타이머/키보드)까지 대기 */
	}
}
