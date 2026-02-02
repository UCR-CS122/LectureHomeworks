#ifndef _VID_H_
#define _VID_H_
extern int fbuf_init();
extern unsigned char _binary_font_start[];
extern int volatile *fb;
extern char image2_start;
extern int color;
extern int kprintf(char *fmt,...);
#endif