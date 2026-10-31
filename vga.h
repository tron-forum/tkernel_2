/*
 * vga.h - VGA 텍스트 모드(0xB8000) 콘솔
 */
#ifndef KN_VGA_H
#define KN_VGA_H

enum vga_color {
	VGA_BLACK = 0, VGA_BLUE, VGA_GREEN, VGA_CYAN,
	VGA_RED, VGA_MAGENTA, VGA_BROWN, VGA_LIGHT_GREY,
	VGA_DARK_GREY, VGA_LIGHT_BLUE, VGA_LIGHT_GREEN, VGA_LIGHT_CYAN,
	VGA_LIGHT_RED, VGA_LIGHT_MAGENTA, VGA_YELLOW, VGA_WHITE,
};

void vga_init(void);
void vga_clear(void);
void vga_set_color(enum vga_color fg, enum vga_color bg);
void vga_putc(char c);
void vga_puts(const char *s);
void vga_put_dec(long v);
void vga_put_udec(unsigned long v);
void vga_put_hex(unsigned long v);

/* 커서를 움직이지 않고 지정 위치에 문자열을 쓴다 (상태 표시용) */
void vga_write_at(int row, int col, const char *s, unsigned char attr);

/* 지원 서식: %c %s %d %i %u %x %p %% (l/ll 길이 수식어 허용) */
void kprintf(const char *fmt, ...);

#endif /* KN_VGA_H */
