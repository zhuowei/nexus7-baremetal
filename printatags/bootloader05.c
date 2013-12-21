#define VIDEOBASE 0xabe01000
#define WIDTH 800
#define HEIGHT 1280

#include "consolefont.c"
#include "linux_atags.h"

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

char buffer[80];

void drawRect(int beginX, int beginY, int width, int height, int color) {
	for (int y = beginY; y < beginY + height; y++) {
		for (int x = beginX; x < beginX + width; x++) {
			int loc = VIDEOBASE + (((y * WIDTH) + x) * 4);
			*((int*) loc) = color;
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

void drawString(const char* myStr, int screenr, int screenc) {
	char myChar;
	while ((myChar = *(myStr++)) != 0) {
		int width = drawCharacter(myChar, screenr, screenc);
		screenc += width;
		if (screenc > WIDTH) {
			screenc = 0;
			screenr += (FONT_WIDTH + 1);
		}
	}
}

int curLine = 0;

void newline() {
	curLine += (FONT_WIDTH + 1);
}

void puts(const char *myStr) {
	char myChar;
	int screenc = 0;
	while ((myChar = *(myStr++)) != 0) {
		int width = drawCharacter(myChar, curLine, screenc);
		screenc += width;
		if (screenc + 8 > WIDTH) {
			screenc = 0;
			curLine += (FONT_WIDTH + 1);
		}
	}
	curLine += (FONT_WIDTH + 1);
}

char* itox(int value, char* str) {
	int i;
	for (i = 0; i < 8; i++) {
		int digit = (value >> (32 - 4 - (i * 4))) & 0xf;
		char mychar;
		if (digit < 10) {
			mychar = '0' + digit;
		} else {
			mychar = 'A' + (digit - 10);
		}
		str[i] = mychar;
	}
	str[i] = (char) 0;
	return str;
}

void printNvidiaTag(struct atag_tegra *tag) {
	puts(itox(tag->bootarg_key, buffer));
	puts(itox(tag->bootarg_len, buffer));
	switch(tag->bootarg_key) {
		case ATAG_NVIDIA_RM:
			//http://searchcode.com/codesearch/view/42047343
			puts("Resource manager");
			break;
		case ATAG_NVIDIA_DISPLAY:
			puts("Display");
			break;
		case ATAG_NVIDIA_FRAMEBUFFER:
			puts("Framebuffer");
			break;
		default:
			puts("Unknown");
			break;
	}
}

int notmain (int alwaysZero, int armMachineType, struct atag *atags) {
    drawRect(0, 0, WIDTH, HEIGHT, 0); //black background
    curLine = 0; //we do not clear BSS, so set this manually
    //Thanks, winocm
    /*
     * Set up boot_args based on atag data, the rest will be filled out during
     * initialization.
     */
    if (atags == 0) {
        puts("ATAGS IS NULL!");
        while(1){}
    }
    struct atag_header *atag_base = (struct atag_header *)atags;
    uint32_t tag = atag_base->tag;

    while (tag != ATAG_NONE) {
        tag = atag_base->tag;
        struct atag* mytag = (struct atag *) atag_base;

        switch (tag) {
        case ATAG_MEM:
            puts("MEMORY: ");
            //puts(itox(mytag->u.mem.size, buffer));
            //puts(itox(mytag->u.mem.start, buffer));
            break;
        case ATAG_CMDLINE:
            puts("Cmdline: ");
            puts(mytag->u.cmdline.cmdline);
            break;
        case ATAG_INITRD2:
            puts("INITRD: ");
            //puts(itox(mytag->u.initrd2.start, buffer));
            //puts(itox(mytag->u.initrd2.size, buffer));
            break;
        case ATAG_NVIDIA:
            puts("Nvidia:");
            printNvidiaTag(&mytag->u.tegra);
            break;
        case ATAG_CORE:
            puts("Core");
            break;
        case ATAG_NONE:
            puts("None");
            break;
        case ATAG_SERIAL:
            puts("Serial");
            puts(itox(mytag->u.serialnr.low, buffer));
            puts(itox(mytag->u.serialnr.high, buffer));
            break;
        default:
            puts("UNKNOWN TAG:");
            puts(itox(tag, buffer));
            break;
        }
        newline();
        atag_base =
            (struct atag_header *)((uint32_t *) atag_base + (atag_base->size));
    };

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

