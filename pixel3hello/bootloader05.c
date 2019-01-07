#define MPM2_MPM_PS_HOLD                     0x0C264000

static void clearram() {
	// trying to find the framebuffer by brute force.
	// zeroes all the ram.
	// all memory regions from /proc/iomem
	// except the kernel region

	// this gets the screen to blank out before rebooting.
	// implying that scanout is still turned on after booting kernel
	// unlike Nexus 6P.
for (int* p = (int*)0x81000000ull; p <= (int*)0x856fffffull; p++){ *p=0; }
for (int* p = (int*)0x85d00000ull; p <= (int*)0x85dfffffull; p++){ *p=0; }
for (int* p = (int*)0x85f00000ull; p <= (int*)0x85fbffffull; p++){ *p=0; }
for (int* p = (int*)0x88f00000ull; p <= (int*)0x8aafffffull; p++){ *p=0; }
for (int* p = (int*)0x8c417000ull; p <= (int*)0x8c4fffffull; p++){ *p=0; }
for (int* p = (int*)0x99c00000ull; p <= (int*)0xa17fffffull; p++){ *p=0; }
//for (int* p = (int*)0xa1c11000ull; p <= (int*)0x17e09ffffull; p++){ *p=0; }
}
int notmain (void *dtb) {
	clearram();
	// simplest test code: just reboots the processo
	unsigned int* hold = (unsigned int*)MPM2_MPM_PS_HOLD;
	*hold = 0;
	while(1) {
	}
	return 0;
}
