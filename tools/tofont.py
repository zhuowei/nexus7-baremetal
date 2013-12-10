#!/usr/bin/python
from __future__ import print_function, division
import Image
import sys
CHAR_WIDTH = 8
def main():
	widths = []
	im = Image.open(sys.argv[1])
	data = list(im.getdata())
	imageWidth = CHAR_WIDTH * 16
	# character grid: 16 x 16, 8 pix per char
	print("const char console_font[256*8] = {")
	for i in xrange(0x100):
		beginX = (i % 16) * CHAR_WIDTH
		beginY = (i // 16) * CHAR_WIDTH
		maxc = 0
		charlastcol = 0
		for r in xrange(CHAR_WIDTH):
			charbin = 0
			for c in xrange(CHAR_WIDTH):
				myx = beginX + c
				myy = beginY + r
				mypix = data[myy * imageWidth + myx]
				char = 0 if mypix[3] == 0 else 1
				charbin = (charbin << 1) | char
				if char == 1 and c > charlastcol:
					charlastcol = c
			#print("{0:8b}".format(charbin).replace("0"," "))
			ender = "" if i == 0xff and r == CHAR_WIDTH - 1 else ","
			print(hex(charbin) + ender)
		if i == 32:
			charlastcol = 3 # from the Minecraft source code
		widths.append(str(charlastcol + 1))
	print("};")
	print("const char console_font_widths[256] = {")
	print(",".join(widths));
	print("};");

if __name__ == "__main__":
	main()
