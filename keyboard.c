/*
 * keyboard.c - PS/2 키보드 드라이버 (IRQ1)
 *
 * 스캔코드 세트 1 을 ASCII 로 변환하여 링 버퍼에 쌓는다.
 * Shift / Caps Lock 을 처리하며, 0xE0 확장 키는 현재 무시한다.
 */
#include "keyboard.h"
#include "idt.h"
#include "io.h"

#define KBD_DATA    0x60
#define KBD_STATUS  0x64

#define SC_LSHIFT   0x2A
#define SC_RSHIFT   0x36
#define SC_CAPS     0x3A
#define SC_RELEASE  0x80
#define SC_EXTENDED 0xE0

#define KBD_BUF_SIZE 128

static const char keymap[128] = {
	0,   27,  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0,   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0,   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	'*', 0,   ' ',
};

static const char keymap_shift[128] = {
	0,   27,  '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
	'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	0,   'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
	0,   '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
	'*', 0,   ' ',
};

static volatile char buf[KBD_BUF_SIZE];
static volatile unsigned int head, tail;
static int shift, caps, extended;

static void kbd_push(char c)
{
	unsigned int next = (head + 1) % KBD_BUF_SIZE;

	if (next != tail) {     /* 가득 차면 버림 */
		buf[head] = c;
		head = next;
	}
}

static void keyboard_irq(struct int_frame *f)
{
	unsigned char sc = inb(KBD_DATA);
	char c;

	(void)f;

	if (sc == SC_EXTENDED) {
		extended = 1;
		return;
	}
	if (extended) {
		extended = 0;
		return;
	}

	if (sc & SC_RELEASE) {
		sc &= ~SC_RELEASE;
		if (sc == SC_LSHIFT || sc == SC_RSHIFT)
			shift = 0;
		return;
	}

	switch (sc) {
	case SC_LSHIFT:
	case SC_RSHIFT:
		shift = 1;
		return;
	case SC_CAPS:
		caps = !caps;
		return;
	}

	c = shift ? keymap_shift[sc] : keymap[sc];
	if (caps && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
		c ^= 0x20;
	if (c)
		kbd_push(c);
}

void keyboard_init(void)
{
	/* 남아 있는 출력 버퍼 비우기 */
	while (inb(KBD_STATUS) & 0x01)
		(void)inb(KBD_DATA);

	irq_register(IRQ_KEYBOARD, keyboard_irq);
}

int keyboard_getc(void)
{
	int c;

	if (head == tail)
		return -1;
	c = (unsigned char)buf[tail];
	tail = (tail + 1) % KBD_BUF_SIZE;
	return c;
}
