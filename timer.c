/*
 * timer.c - PIT 채널 0 을 TIMER_HZ 주기로 설정하고 틱을 센다 (IRQ0)
 */
#include "timer.h"
#include "idt.h"
#include "io.h"

#define PIT_CH0     0x40
#define PIT_CMD     0x43
#define PIT_BASE_HZ 1193182

static volatile unsigned long ticks;

static void timer_irq(struct int_frame *f)
{
	(void)f;
	ticks++;
}

void timer_init(void)
{
	unsigned int divisor = PIT_BASE_HZ / TIMER_HZ;

	outb(PIT_CMD, 0x36);    /* 채널0, lo/hi 바이트, 모드3(구형파) */
	outb(PIT_CH0, (unsigned char)(divisor & 0xFF));
	outb(PIT_CH0, (unsigned char)(divisor >> 8));

	irq_register(IRQ_TIMER, timer_irq);
}

unsigned long timer_ticks(void)
{
	return ticks;
}
