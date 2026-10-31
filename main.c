/*
 * main.c - kellynelson 커널 메인
 *
 * boot.asm 에서 제어권을 넘겨받아 VGA 텍스트 버퍼(0xB8000)에 직접
 * 초기화 메시지를 출력한다. 호스트 C 표준 라이브러리는 사용하지 않는다.
 */

#define VGA_BUFFER   ((volatile unsigned short *)0xB8000)
#define VGA_COLS     80
#define VGA_ROWS     25
#define VGA_ATTR     0x0F    /* 검정 배경, 흰 글자 */

static void vga_clear(unsigned char attr)
{
	int i;

	for (i = 0; i < VGA_COLS * VGA_ROWS; i++)
		VGA_BUFFER[i] = (unsigned short)(attr << 8) | ' ';
}

static void vga_puts(int row, int col, const char *s, unsigned char attr)
{
	volatile unsigned short *p = VGA_BUFFER + row * VGA_COLS + col;

	while (*s)
		*p++ = (unsigned short)(attr << 8) | (unsigned char)*s++;
}

void kernel_main(unsigned int mb_magic, unsigned int mb_info)
{
	(void)mb_magic;
	(void)mb_info;

	vga_clear(VGA_ATTR);
	vga_puts(0, 0, "codename: kellynelson Initializing...", VGA_ATTR);

	for (;;)
		__asm__ volatile ("hlt");
}
