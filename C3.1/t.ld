ENTRY(reset_handler)
SECTIONS
{
    . = 0x10000; /* loading address */
    .text : { CMakeFiles/timer.elf.dir/src/ts.s.obj *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
    .data : { image3.o } /* include image.o as a data section */
                         /* include more image files, if any */
    . = ALIGN(8);
    . = . + 0x1000; /* 4kB of SVC stack space */
    svc_stack_top = .;
    . = . + 0x1000; /* 4kB of IRQ stack space */
    irq_stack_top = .;
}