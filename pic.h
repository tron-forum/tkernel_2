/*
 * pic.h - 8259A PIC
 */
#ifndef KN_PIC_H
#define KN_PIC_H

void pic_init(int master_base, int slave_base);
void pic_send_eoi(int irq);
void pic_mask(int irq);
void pic_unmask(int irq);
int  pic_is_spurious(int irq);

#endif /* KN_PIC_H */
