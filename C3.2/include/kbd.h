#ifndef __KBD_H__
#define __KBD_H__
#define KCNTL 0x00  // 7-6- 5(0=AT)4=RxIntEn 3=TxIntEn
#define KSTAT 0x04  // 7-6=TxE 5=TxBusy 4=RXFull 3=RxBusy
#define KDATA 0x08  // data register;
#define KCLK 0x0C   // clock divisor register; (not used)
#define KISTA 0x10  // interrupt status register;(not used)

typedef volatile struct kbd {  // base = 0x10006000
  char* base;                  // base address of KBD, as char *
  char buf[128];               // input buffer
  int head, tail, data, room;  // control variables
} KBD;

extern volatile KBD kbd;  // KBD data structure

extern int kbd_init();
extern void kbd_handler();
extern int kgetc();
extern int kgets(char s[]);

#endif