# LectureHomeworks
Code and other information for UCR's CS 122 course. All material is attributed to the textbook "Embedded &amp; Real-Time Operating Systems" by K.C. Wang.

## Notes

Here's a couople of notes to get things running. 

### Running in QEMU
```sh
qemu-system-arm -M versatilepb -m 128M -kernel C2.6/vid.bin -serial mon:stdio
```

This command should work for all the examples. Just change C2.6/vid.bin to the bin file in each C directory.