/******** kbd.c file ******************/
#define USE_KEYSET2
#include "kbd.h"

#include "defines.h"
#include "exceptions.h"
#include "keymap.h"
#include "uart.h"
#include "vid.h"

UART* kbd_out;

volatile KBD kbd;  // KBD data structure

int kbd_init() {
  KBD* kp = &kbd;
  kp->base = (char*)0x10006000;
  *(kp->base + KCNTL) = 0x14;  // 00010100=INTenable, Enable
  *(kp->base + KCLK) = 8;      // PL051 manual says a value 0 to 15
  kp->data = 0;
  kp->room = 128;           // counters
  kp->head = kp->tail = 0;  // index to buffer
  kbd_out = &uart[0];
}

void kbd_handler() {  // KBD interrupt handler in C
  u8 scode, c;
  int i;
  KBD* kp = &kbd;
  color = RED;                        // int color in vid.c file
  scode = *(kp->base + KDATA);        // read scan code in data register
  if (scode & 0x80 || scode > NSCAN)  // ignore key releases
    return;
  c = ltab[scode];  // map scan code to ASCII
  if (c != '\r') printf("kbd interrupt: c=%x %c\n", c, c);
  kp->buf[kp->head++] = c;  // enter key into CIRCULAR buf[ ]
  kp->head %= 128;
  kp->data++;
  kp->room--;  // update counters
}

int kgetc() {  // main program calls kgetc() to return a char
  char c;
  KBD* kp = &kbd;
  unlock();  // enable IRQ interrupts
  while (kp->data <= 0);
  lock();                   // disable IRQ interrupts
  c = kp->buf[kp->tail++];  // get a c and update tail index
  kp->tail %= 128;
  kp->data--;
  kp->room++;  // update with interrupts OFF
  unlock();    // enable IRQ interrupts
  return c;
}

int kgets(char s[]) {  // get a string from KBD
  char c;
  while ((c = kgetc()) != '\r') {
    *s++ = c;
  }
  *s = 0;
  return strlen(s);
}