/*
 * keyboard.h - PS/2 키보드 (스캔코드 세트 1, US 배열)
 */
#ifndef KN_KEYBOARD_H
#define KN_KEYBOARD_H

void keyboard_init(void);
int  keyboard_getc(void);   /* 입력 없으면 -1 */

#endif /* KN_KEYBOARD_H */
