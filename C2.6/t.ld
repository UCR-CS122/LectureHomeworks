#---- linker script file t.ld -------
ENTRY(reset_start)
SECTIONS
{   . = 0x10000;
    .text : { CMakeFiles/vid.elf.dir/src/ts.s.obj *( .text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
    .data : { image0.o } /* include image.o as a data section */
                        /* include more image files, if any */
    .data : { image1.o } /* include image.o as a data section */
                        /* include more image files, if any */
    /* stack areas */
    . = ALIGN(8);
    . = . + 0x1000; /* 4KB stack space */
    stack_top = .; /* stack_top is a symbol exported by linker */
}