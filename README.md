# LectureHomeworks
Code and other information for UCR's CS 122 course. All material is attributed to the textbook "Embedded &amp; Real-Time Operating Systems" by K.C. Wang.

## Notes

Here's a couople of notes to get things running. The objcopy command will be changed by a CMake target. In the meantime, run the following commands to get things working in a CodeSpace.

### Making Object Files from Images

The following commands will set up the UCR Logo Bitmaps to be included in the executable.

```sh
arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm UC_Riverside_Vert_BluBG_sm.bmp image0.o
arm-none-eabi-objcopy -I binary -O elf32-littlearm -B arm UC_Riverside_Vert_WhtBG_sm.bmp image1.o
cp image0.o image1.o C2.6
```

One you've executed this commands, C2.6 should build properly. To build all the code type the following command:

```sh
make
```

### Running C2.6 in QEMU
```sh
qemu-system-arm -M versatilepb -m 128M -kernel C2.6/vid.bin -serial mon:stdio
```

This command should work for all the examples. Just change C2.6/vid.bin to the bin file in each C directory.