// FracRotate.cpp : main project file.
#define VIDEOBASE 0xabe01000
#include "sintable.h"

#define WIDTH 1280
#define HEIGHT 800

#define TEGRA_DC_DISP_A_BASE 0x54200000
#define TEGRA_DC_WINBUF_A_START 0x800
#define HWREG(x)    *((unsigned int*)(x)) 

void *memset(void *ptr, int c, unsigned int len);

static unsigned int* framebuffer = (unsigned int*) VIDEOBASE;
static unsigned int* secondFramebuffer = (unsigned int*) (VIDEOBASE + (WIDTH * HEIGHT * 4));

static float sindeg(int val) {
	val = val % 360;
	if (val < 0) val = 360 + val;
	//Console::Write(val + L":");
	return sin_table[val];
}

#define cosdeg(val) sindeg(val + 90)
#define MAX(x1, x2) (x1 > x2? x1: x2)
#define MIN(x1, x2) (x1 < x2? x1: x2)
#define ABS(x) ((x) < 0? -1 * (x): (x))
#define PIXELADDR(x, y) (x * HEIGHT + y)

void renderLine(int x0, int y0, int x1, int y1) {
	/* pulled from Wikipedia page on Bresenham's line algorithm */
	int deltaX = ABS(x1 - x0);
	int deltaY = ABS(y1 - y0);
	int sx = x0 < x1 ? 1 : -1; /* directions */
	int sy = y0 < y1 ? 1 : -1;
	int err = deltaX - deltaY;
	for(;;) {
		int addr = PIXELADDR(x0, y0);
		if (addr >= 0 && addr < WIDTH*HEIGHT && x0 >= 0 && y0 >= 0 && x0 < WIDTH && y0 < HEIGHT) framebuffer[addr] = 0x00000000;
		if (x0 == x1 && y0 == y1) break;
		int e2 = err*2;
		if (e2 > -deltaY) {
			err -= deltaY;
			x0 += sx;
		}
		if (e2 < deltaX) {
			err += deltaX;
			y0 += sy;
		}
	}
}

void render(int beginX, int beginY, int length, int curDegree, int deltaDegree) {
	int endX = beginX + (int)(length * sindeg(curDegree));
	int endY = beginY - (int)(length * cosdeg(curDegree));
	renderLine(beginX, beginY, endX, endY);
	int nextLength = length * 7 / 10;
	if (nextLength > 0) {
		render(endX, endY, nextLength, curDegree - deltaDegree, deltaDegree);
		render(endX, endY, nextLength, curDegree + deltaDegree, deltaDegree);
	}
}

void renderFrame(int degrees) {
	render(WIDTH / 2, HEIGHT, HEIGHT / 2, 0, degrees);
}

void flipBuffer() {
	/* does not work yet */
	unsigned int* renderedBuffer = framebuffer;
	framebuffer = secondFramebuffer;
	secondFramebuffer = renderedBuffer;
	HWREG(TEGRA_DC_DISP_A_BASE + TEGRA_DC_WINBUF_A_START) = (unsigned int) renderedBuffer;
}

int notmain (int alwaysZero, int armMachineType, void *atags) {
	int degrees = 0;
	while(1) {
		memset(framebuffer, 0xff, WIDTH * HEIGHT * 4);
		renderFrame(degrees);
		degrees++;
		if (degrees >= 180) degrees = 0;
		//flipBuffer();
	}
	return 0;
}

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

