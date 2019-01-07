#define MPM2_MPM_PS_HOLD                     0x0C264000
int notmain (void *dtb) {
	// simplest test code: just reboots the processo
	unsigned int* hold = (unsigned int*)MPM2_MPM_PS_HOLD;
	*hold = 0;
	while(1) {
	}
	return 0;
}
