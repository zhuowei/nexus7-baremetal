
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

// The raspberry pi firmware at the time this was written defaults
// loading at address 0x8000.  Although this bootloader could easily
// load at 0x0000, it loads at 0x8000 so that the same binaries built
// for the SD card work with this bootloader.  Change the ARMBASE
// below to use a different location.

#define ARMBASE 0x8000
#define VIDEOBASE 0xabe01000
#define WIDTH 800

extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern void PUT8 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern unsigned int GETPC ( void );
extern void BRANCHTO ( unsigned int );
extern void dummy ( unsigned int );
extern void hang(void);

//------------------------------------------------------------------------
unsigned char xstring[256];
//------------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;
    //unsigned int rb;
    unsigned int rx;
    unsigned int addr;
    unsigned int block;
    unsigned int state;

    unsigned int crc;

    unsigned int currentPc = GETPC();

    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < (32 << 4); x++) {
            int color = 0x808080;
            if (x >> 4 & 0x1) color = 0xffffff;
            PUT32(VIDEOBASE + (x * 4) + (y * 4 * WIDTH), color);
        }
    }

    for (int y = 16; y < 32; y++) {
        for (int x = 0; x < (32 << 4); x++) {
            int color = 0;
            if (currentPc & (1 << ((x >> 4) % 32))) color = 0xffffff;
            PUT32(VIDEOBASE + (x * 4) + (y * 4 * WIDTH), color);
        }
    }

    /*for (int y = 0; y < 16; y++) {
    for (int i = 0; i < WIDTH; i++) {
        int color = 0;
	if (y < 4) {
		color = 0xffffff;
	}
        else if (currentPc & (1 << ((i >> 2) % 32))) {
		color = 0xffffff;
	} else {
		if (i >> 2 & 1) color = 0xff0000;
	}
        PUT32(VIDEOBASE + (i * 4) + (y * 4 * WIDTH), color);
    }*/
    if (currentPc & 0xffff0000 == 0x80a00000) {
    for (int i = 0; i < WIDTH; i++) {
        PUT32(VIDEOBASE + (i * 4), 0xffffff);
    }
    }

    while(1) {}
    return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------

