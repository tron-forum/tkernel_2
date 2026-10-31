/*
 * idt.c - IDT 구성, 예외 처리, IRQ 디스패치
 */
#include "idt.h"
#include "pic.h"
#include "vga.h"

#define IDT_ENTRIES     256
#define ISR_STUBS       48
#define KERNEL_CS       0x08    /* boot.asm gdt64.code */
#define GATE_INTERRUPT  0x8E    /* Present, DPL0, 64비트 인터럽트 게이트 */

struct idt_entry {
	unsigned short offset_low;
	unsigned short selector;
	unsigned char  ist;
	unsigned char  type_attr;
	unsigned short offset_mid;
	unsigned int   offset_high;
	unsigned int   reserved;
} __attribute__((packed));

struct idt_ptr {
	unsigned short limit;
	unsigned long  base;
} __attribute__((packed));

extern void *isr_stub_table[ISR_STUBS];

static struct idt_entry idt[IDT_ENTRIES] __attribute__((aligned(16)));
static irq_handler_t irq_handlers[16];

static const char *const exception_names[32] = {
	"Divide Error", "Debug", "NMI", "Breakpoint",
	"Overflow", "BOUND Range Exceeded", "Invalid Opcode", "Device Not Available",
	"Double Fault", "Coprocessor Segment Overrun", "Invalid TSS", "Segment Not Present",
	"Stack-Segment Fault", "General Protection", "Page Fault", "Reserved",
	"x87 FPU Error", "Alignment Check", "Machine Check", "SIMD Exception",
	"Virtualization", "Control Protection", "Reserved", "Reserved",
	"Reserved", "Reserved", "Reserved", "Reserved",
	"Hypervisor Injection", "VMM Communication", "Security", "Reserved",
};

static void idt_set_gate(int vec, void *handler)
{
	unsigned long addr = (unsigned long)handler;

	idt[vec].offset_low  = (unsigned short)(addr & 0xFFFF);
	idt[vec].selector    = KERNEL_CS;
	idt[vec].ist         = 0;
	idt[vec].type_attr   = GATE_INTERRUPT;
	idt[vec].offset_mid  = (unsigned short)((addr >> 16) & 0xFFFF);
	idt[vec].offset_high = (unsigned int)(addr >> 32);
	idt[vec].reserved    = 0;
}

void idt_init(void)
{
	struct idt_ptr ptr;
	int i;

	for (i = 0; i < ISR_STUBS; i++)
		idt_set_gate(i, isr_stub_table[i]);

	ptr.limit = sizeof(idt) - 1;
	ptr.base  = (unsigned long)idt;
	__asm__ volatile ("lidt %0" : : "m"(ptr));

	pic_init(IRQ_BASE, IRQ_BASE + 8);
}

void irq_register(int irq, irq_handler_t handler)
{
	irq_handlers[irq] = handler;
	pic_unmask(irq);
}

static void exception_panic(struct int_frame *f)
{
	unsigned long cr2;

	__asm__ volatile ("mov %%cr2, %0" : "=r"(cr2));

	vga_set_color(VGA_WHITE, VGA_RED);
	kprintf("\n*** CPU EXCEPTION %lu: %s ***\n", f->vector,
		exception_names[f->vector]);
	vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
	kprintf("  err=%lx rip=%lx cs=%lx rflags=%lx\n",
		f->err_code, f->rip, f->cs, f->rflags);
	kprintf("  rsp=%lx ss=%lx cr2=%lx\n", f->rsp, f->ss, cr2);
	kprintf("  rax=%lx rbx=%lx rcx=%lx rdx=%lx\n", f->rax, f->rbx, f->rcx, f->rdx);
	kprintf("  rsi=%lx rdi=%lx rbp=%lx\n", f->rsi, f->rdi, f->rbp);
	kprintf("System halted.");

	for (;;) {
		cpu_cli();
		cpu_hlt();
	}
}

void isr_dispatch(struct int_frame *f)
{
	int irq;

	if (f->vector < IRQ_BASE) {
		exception_panic(f);
		return;
	}

	irq = (int)(f->vector - IRQ_BASE);
	if (pic_is_spurious(irq))
		return;
	if (irq_handlers[irq])
		irq_handlers[irq](f);
	pic_send_eoi(irq);
}
