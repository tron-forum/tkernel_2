/*
 * idt.h - 인터럽트 디스크립터 테이블 및 인터럽트 프레임
 */
#ifndef KN_IDT_H
#define KN_IDT_H

#define IRQ_BASE    32      /* PIC 재매핑 후 IRQ0 의 벡터 번호 */
#define IRQ_TIMER   0
#define IRQ_KEYBOARD 1

/* isr.asm 의 isr_common 이 쌓는 스택 레이아웃과 동일한 순서 */
struct int_frame {
	unsigned long r15, r14, r13, r12, r11, r10, r9, r8;
	unsigned long rbp, rdi, rsi, rdx, rcx, rbx, rax;
	unsigned long vector, err_code;
	unsigned long rip, cs, rflags, rsp, ss;     /* CPU 가 쌓는 부분 */
};

typedef void (*irq_handler_t)(struct int_frame *f);

void idt_init(void);
void irq_register(int irq, irq_handler_t handler);

static inline void cpu_sti(void) { __asm__ volatile ("sti"); }
static inline void cpu_cli(void) { __asm__ volatile ("cli"); }
static inline void cpu_hlt(void) { __asm__ volatile ("hlt"); }

#endif /* KN_IDT_H */
