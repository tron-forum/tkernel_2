/*
 * pic.c - 8259A PIC 재매핑 및 마스크/EOI 제어
 *
 * 기본 매핑(IRQ0~7 -> 벡터 8~15)은 CPU 예외와 겹치므로 32~47 로 옮긴다.
 */
#include "pic.h"
#include "io.h"

#define PIC1_CMD    0x20
#define PIC1_DATA   0x21
#define PIC2_CMD    0xA0
#define PIC2_DATA   0xA1

#define ICW1_INIT   0x11    /* 초기화 + ICW4 필요 */
#define ICW4_8086   0x01
#define PIC_EOI     0x20
#define PIC_READ_ISR 0x0B

static inline void io_wait(void)
{
	outb(0x80, 0);
}

void pic_init(int master_base, int slave_base)
{
	outb(PIC1_CMD, ICW1_INIT);  io_wait();
	outb(PIC2_CMD, ICW1_INIT);  io_wait();
	outb(PIC1_DATA, (unsigned char)master_base);  io_wait();
	outb(PIC2_DATA, (unsigned char)slave_base);   io_wait();
	outb(PIC1_DATA, 0x04);      io_wait();  /* IRQ2 에 슬레이브 연결 */
	outb(PIC2_DATA, 0x02);      io_wait();  /* 슬레이브 ID = 2 */
	outb(PIC1_DATA, ICW4_8086); io_wait();
	outb(PIC2_DATA, ICW4_8086); io_wait();

	/* 등록된 핸들러가 없는 IRQ 는 모두 마스크 (캐스케이드 IRQ2 만 허용) */
	outb(PIC1_DATA, 0xFB);
	outb(PIC2_DATA, 0xFF);
}

void pic_send_eoi(int irq)
{
	if (irq >= 8)
		outb(PIC2_CMD, PIC_EOI);
	outb(PIC1_CMD, PIC_EOI);
}

void pic_mask(int irq)
{
	unsigned short port = irq < 8 ? PIC1_DATA : PIC2_DATA;

	outb(port, inb(port) | (unsigned char)(1 << (irq & 7)));
}

void pic_unmask(int irq)
{
	unsigned short port = irq < 8 ? PIC1_DATA : PIC2_DATA;

	outb(port, inb(port) & (unsigned char)~(1 << (irq & 7)));
}

/* IRQ7/IRQ15 의 가짜(spurious) 인터럽트 판별: ISR 비트가 서 있지 않으면 가짜 */
int pic_is_spurious(int irq)
{
	if (irq == 7) {
		outb(PIC1_CMD, PIC_READ_ISR);
		return !(inb(PIC1_CMD) & 0x80);
	}
	if (irq == 15) {
		outb(PIC2_CMD, PIC_READ_ISR);
		if (!(inb(PIC2_CMD) & 0x80)) {
			outb(PIC1_CMD, PIC_EOI);    /* 마스터에는 캐스케이드 EOI 필요 */
			return 1;
		}
	}
	return 0;
}
