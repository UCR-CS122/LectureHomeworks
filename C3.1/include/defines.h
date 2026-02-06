#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdint.h>

extern int kstrcpy(char *dest, char *src);

#define printf kprintf
#define bcopy  kbcopy
#define memcpy kmemcpy
#define strcpy kstrcpy
#define strlen kstrlen

#define RED 0
#define BLUE 1
#define GREEN 2
#define WHITE 3

#define VIC_BASE_ADDR 0x10140000
#define VIC_STATUS    (*((volatile u32 *)(VIC_BASE_ADDR + 0x000)))
#define VIC_INTENABLE (*((volatile u32 *)(VIC_BASE_ADDR + 0x010)))
#define VIC_VADDR     (*((volatile u32 *)(VIC_BASE_ADDR + 0x030)))
#define VIC_CLEAR     (*((volatile u32 *)(VIC_BASE_ADDR + 0x01C)))
#define SIC_BASE_ADDR 0x10003000
#define SIC_STATUS    (*((volatile u32 *)(SIC_BASE_ADDR + 0x000)))
#define SIC_INTENABLE (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
#define SIC_ENSET     (*((volatile u32 *)(SIC_BASE_ADDR + 0x008)))
#define SIC_PICENSET  (*((volatile u32 *)(SIC_BASE_ADDR + 0x020)))

typedef uint32_t u32;

#endif