
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

#include "consolefont.c"

#define FONT_WIDTH 8

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

const char* messages[] = {
"We're no strangers to love",
"You know the rules and so do I",
"A full commitment's what I'm thinking of",
"You wouldn't get this from any other guy",
"I just wanna tell you how I'm feeling",
"Gonna make you understand",
"Never gonna give you up",
"Never gonna let you down",
"Never gonna run around and",
"Desert you",
"Never gonna make you cry",
"Never gonna say goodbye",
"Never gonna tell a lie",
"And hurt you"};

#define MESSAGES_COUNT 14

void drawRect(int beginX, int beginY, int width, int height, int color) {
	for (int y = beginY; y < beginY + height; y++) {
		for (int x = beginX; x < beginX + width; x++) {
			int loc = VIDEOBASE + (((y * WIDTH) + x) * 4);
			PUT32(loc, color);
		}
	}
}

void setPixel(int x, int y, int color) {
	int loc = VIDEOBASE + (((y * WIDTH) + x) * 4);
	PUT32(loc, color);
}

#define FONT_WIDTH 8

int drawCharacter(char mychar, int screenr, int screenc) {
	int index = ((int) mychar) * FONT_WIDTH;
	int rr, cc;
	for (rr = 0; rr < FONT_WIDTH; rr++) {
		int myrow = console_font[index + rr];
		for (cc = 0; cc < FONT_WIDTH; cc++) {
			int thisPixel = (myrow >> (FONT_WIDTH - 1 - cc)) & 0x1;
			if (thisPixel) {
				setPixel(screenc + cc, screenr + rr, 0xffffff);
			}
		}
	}
	return console_font_widths[(int) mychar] + 1;
}

void drawString(char* myStr, int screenr, int screenc) {
	char myChar;
	while ((myChar = *(myStr++)) != 0) {
		int width = drawCharacter(myChar, screenr, screenc);
		screenc += width;
	}
}

int notmain ( void )
{
	int col = 0;
	drawRect(0, 0, WIDTH, HEIGHT, col); //black background
	for (int i = 0; i < MESSAGES_COUNT; i++) {
		drawString((char*) messages[i], i * (FONT_WIDTH + 1), 0);
	}
	while(1){
	}
	return 0;
}
//The font is derived from the Minecraft font. Please don't sue me.
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

//Portions of this code pulled from the Raspberry Pi experiments by David Welch.
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

