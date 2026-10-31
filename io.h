/*
 * io.h - x86 포트 입출력
 */
#ifndef KN_IO_H
#define KN_IO_H

static inline void outb(unsigned short port, unsigned char val)
{
	__asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline unsigned char inb(unsigned short port)
{
	unsigned char val;

	__asm__ volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
	return val;
}

#endif /* KN_IO_H */
