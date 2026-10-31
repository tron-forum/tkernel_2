/*
 * vga.c - VGA 텍스트 모드 콘솔
 *
 * 0xB8000 버퍼에 직접 쓰며 줄바꿈/탭/백스페이스, 스크롤,
 * 하드웨어 커서 갱신, 10진/16진 숫자 출력, 간단한 kprintf 를 제공한다.
 */
#include "vga.h"
#include "io.h"

#define VGA_BUFFER   ((volatile unsigned short *)0xB8000)
#define VGA_COLS     80
#define VGA_ROWS     25
#define VGA_TAB      8

#define VGA_CRTC_INDEX  0x3D4
#define VGA_CRTC_DATA   0x3D5

static int cur_row;
static int cur_col;
static unsigned char cur_attr = (VGA_BLACK << 4) | VGA_LIGHT_GREY;

static inline unsigned short vga_entry(char c, unsigned char attr)
{
	return (unsigned short)(attr << 8) | (unsigned char)c;
}

static void vga_update_cursor(void)
{
	unsigned short pos = (unsigned short)(cur_row * VGA_COLS + cur_col);

	outb(VGA_CRTC_INDEX, 0x0F);
	outb(VGA_CRTC_DATA, (unsigned char)(pos & 0xFF));
	outb(VGA_CRTC_INDEX, 0x0E);
	outb(VGA_CRTC_DATA, (unsigned char)(pos >> 8));
}

static void vga_enable_cursor(void)
{
	/* 커서 모양: 스캔라인 14~15 (밑줄형) */
	outb(VGA_CRTC_INDEX, 0x0A);
	outb(VGA_CRTC_DATA, (inb(VGA_CRTC_DATA) & 0xC0) | 14);
	outb(VGA_CRTC_INDEX, 0x0B);
	outb(VGA_CRTC_DATA, (inb(VGA_CRTC_DATA) & 0xE0) | 15);
}

static void vga_scroll(void)
{
	int i;

	for (i = 0; i < (VGA_ROWS - 1) * VGA_COLS; i++)
		VGA_BUFFER[i] = VGA_BUFFER[i + VGA_COLS];
	for (; i < VGA_ROWS * VGA_COLS; i++)
		VGA_BUFFER[i] = vga_entry(' ', cur_attr);
	cur_row = VGA_ROWS - 1;
}

static void vga_newline(void)
{
	cur_col = 0;
	if (++cur_row >= VGA_ROWS)
		vga_scroll();
}

void vga_init(void)
{
	vga_enable_cursor();
	vga_clear();
}

void vga_clear(void)
{
	int i;

	for (i = 0; i < VGA_ROWS * VGA_COLS; i++)
		VGA_BUFFER[i] = vga_entry(' ', cur_attr);
	cur_row = 0;
	cur_col = 0;
	vga_update_cursor();
}

void vga_set_color(enum vga_color fg, enum vga_color bg)
{
	cur_attr = (unsigned char)((bg << 4) | (fg & 0x0F));
}

static void vga_putc_raw(char c)
{
	switch (c) {
	case '\n':
		vga_newline();
		break;
	case '\r':
		cur_col = 0;
		break;
	case '\t':
		do
			vga_putc_raw(' ');
		while (cur_col % VGA_TAB != 0);
		break;
	case '\b':
		if (cur_col > 0) {
			cur_col--;
			VGA_BUFFER[cur_row * VGA_COLS + cur_col] = vga_entry(' ', cur_attr);
		}
		break;
	default:
		VGA_BUFFER[cur_row * VGA_COLS + cur_col] = vga_entry(c, cur_attr);
		if (++cur_col >= VGA_COLS)
			vga_newline();
		break;
	}
}

void vga_putc(char c)
{
	vga_putc_raw(c);
	vga_update_cursor();
}

void vga_puts(const char *s)
{
	while (*s)
		vga_putc_raw(*s++);
	vga_update_cursor();
}

void vga_put_udec(unsigned long v)
{
	char buf[21];
	int i = 0;

	do {
		buf[i++] = (char)('0' + v % 10);
		v /= 10;
	} while (v);
	while (i)
		vga_putc_raw(buf[--i]);
	vga_update_cursor();
}

void vga_put_dec(long v)
{
	if (v < 0) {
		vga_putc_raw('-');
		vga_put_udec(-(unsigned long)v);
	} else {
		vga_put_udec((unsigned long)v);
	}
}

void vga_put_hex(unsigned long v)
{
	static const char digits[] = "0123456789abcdef";
	char buf[16];
	int i = 0;

	do {
		buf[i++] = digits[v & 0xF];
		v >>= 4;
	} while (v);
	vga_putc_raw('0');
	vga_putc_raw('x');
	while (i)
		vga_putc_raw(buf[--i]);
	vga_update_cursor();
}

void kprintf(const char *fmt, ...)
{
	__builtin_va_list ap;
	int lng;

	__builtin_va_start(ap, fmt);
	for (; *fmt; fmt++) {
		if (*fmt != '%') {
			vga_putc_raw(*fmt);
			continue;
		}

		lng = 0;
		while (*++fmt == 'l')
			lng++;

		switch (*fmt) {
		case 'c':
			vga_putc_raw((char)__builtin_va_arg(ap, int));
			break;
		case 's': {
			const char *s = __builtin_va_arg(ap, const char *);
			vga_puts(s ? s : "(null)");
			break;
		}
		case 'd':
		case 'i':
			vga_put_dec(lng ? __builtin_va_arg(ap, long)
					: __builtin_va_arg(ap, int));
			break;
		case 'u':
			vga_put_udec(lng ? __builtin_va_arg(ap, unsigned long)
					 : __builtin_va_arg(ap, unsigned int));
			break;
		case 'x':
			vga_put_hex(lng ? __builtin_va_arg(ap, unsigned long)
					: __builtin_va_arg(ap, unsigned int));
			break;
		case 'p':
			vga_put_hex((unsigned long)__builtin_va_arg(ap, void *));
			break;
		case '%':
			vga_putc_raw('%');
			break;
		case '\0':
			fmt--;
			break;
		default:
			vga_putc_raw('%');
			vga_putc_raw(*fmt);
			break;
		}
	}
	__builtin_va_end(ap);
	vga_update_cursor();
}
