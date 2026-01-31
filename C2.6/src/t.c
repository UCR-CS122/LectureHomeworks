/************** t.c file of program C2.6 ******************/
#include "defines.h" // device base addresses, etc.
#include "vid.h" // LCD driver
#include "uart.h" // UART driver

extern char _binary_UC_Riverside_Vert_BluBG_sm_bmp_start, _binary_UC_Riverside_Vert_WhtBG_sm_bmp_start;

UART *up;

#define WIDTH 640
int show_bmp(char *p, int start_row, int start_col) {
    int h, w, pixel, rsize, i, j;
    unsigned char r, g, b;
    char *pp;
    int *q = (int *)(p+14); // skip over 14-byte file header
    w = *(q+1); // image width in pixels
    h = *(q+2); // image height in pixels
    p += 54; // p-> pixels in image
    //BMP images are upside down, each row is a multiple of 4 bytes
    rsize = 4*(w + 0); // multiple of 4
    p += (h-1)*rsize; // last row of pixels
    for (i=start_row; i<start_row + h; i++){
        pp = p;
        for (j=start_col; j<start_col + w; j++){
            b = *pp; g = *(pp+1); r = *(pp+2); // BRG values
            pixel = (b<<16) | (g<<8) | r; // pixel value
            fb[i*WIDTH + j] = pixel; // write to frame buffer
            pp += 4; // advance pp to next pixel
        }
        p -= rsize; // to preceding row
    }
    uprintf(up, "\nBMP image height=%d width=%d\n", h, w);
}

int main() {
    char c,* p;
    uart_init(); // initialize UARTs
    up = &uart[0]; // use UART0
    fbuf_init(0); // default to VGA mode

    uprintf(up, "Hello, World, %u\n", -1);
    while(1){
        p = &_binary_UC_Riverside_Vert_BluBG_sm_bmp_start;
        show_bmp(p, 0, 0); // display image1
        uprintf(up, "enter a key from this UART : ");
        ugetc(up);
        p = &_binary_UC_Riverside_Vert_WhtBG_sm_bmp_start;
        show_bmp(p,229, 321); // display image2
    }

    while(1); // loop here
}