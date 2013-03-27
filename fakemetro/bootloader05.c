
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
#define HEIGHT 1280

extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern void PUT8 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern unsigned int GETPC ( void );
extern void BRANCHTO ( unsigned int );
extern void dummy ( unsigned int );

//------------------------------------------------------------------------
//unsigned char xstring[256];
//------------------------------------------------------------------------

void drawRect(int beginX, int beginY, int width, int height, int color) {
	for (int y = beginY; y < beginY + height; y++) {
		for (int x = beginX; x < beginX + width; x++) {
			int loc = VIDEOBASE + (((y * WIDTH) + x) * 4);
			PUT32(loc, color);
		}
	}
}

int notmain ( void )
{
	drawRect(0, 0, WIDTH, HEIGHT, 0xff0000); //blue background
        drawRect(WIDTH - 400 - 10, 10, 400, 640, 0x00ff00);
	drawRect(10, 10, 800 - 420 - 10, 315, 0x00ffff);
	drawRect(10, 340, 800 - 420 - 10, 315, 0xffff00);
	drawRect(WIDTH - 400 - 10, 10 + 640 + 10, 400, 310, 0xffaa00);
	drawRect(10, 10 + 640 + 10, 370, 310, 0x00aaff);
	drawRect(10, 10 + 640 + 10 + 310 + 10, 370, 310, 0x990011);
	drawRect(10 + 370 + 10, 10 + 640 + 10 + 310 + 10, 190, 310, 0xaa0011);
	drawRect(WIDTH - 205, 10 + 640 + 10 + 310 + 10, 195, 310, 0xaaaa11);
	while(1){}
	return 0;
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

