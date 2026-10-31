/*
 * timer.h - 8253/8254 PIT 시스템 타이머
 */
#ifndef KN_TIMER_H
#define KN_TIMER_H

#define TIMER_HZ    100

void timer_init(void);
unsigned long timer_ticks(void);

#endif /* KN_TIMER_H */
