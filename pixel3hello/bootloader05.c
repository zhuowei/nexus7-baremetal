#define MPM2_MPM_PS_HOLD                     0x0C264000

static void* findframebuffer() {
	// trying to find the framebuffer by brute force.
	// zeroes all the ram.
	// all memory regions from /proc/iomem
	// except the kernel region

	// this gets the screen to blank out before rebooting.
	// implying that scanout is still turned on after booting kernel
	// unlike Nexus 6P.
	for (unsigned int* p = (unsigned int*)0x9d500000ull; p <= (unsigned int*)0x9e400000ull; p++) {
		*p = 0xff00ff00u;
	}
	return 0;
}
static void not_memset(void* a, int v, unsigned long long size) {
	char* p = a;
	for (unsigned long long i = 0; i < size; i++) {
		p[i] = v;
	}
}
int notmain (void *dtb) {
	void* fb = findframebuffer();
	for (int i = 0; i < 0x40000000; i++) {
		asm volatile("");
	}
	// simplest test code: just reboots the processo
	//unsigned int* hold = (unsigned int*)MPM2_MPM_PS_HOLD;
	//*hold = 0;
	while(1) {
	}
	return 0;
}
