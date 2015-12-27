#define MDP_BASE                    (0xfd900000)
#define REG_MDP(off)                (MDP_BASE + (off))
#define MDP_VP_0_VIG_0_BASE                     REG_MDP(0x5000)
#define MDP_VP_0_RGB_0_BASE                     REG_MDP(0x15000)
#define MDP_VP_0_DMA_0_BASE                     REG_MDP(0x25000)
#define PIPE_SSPP_SRC0_ADDR                     0x14
#define MPM2_MPM_PS_HOLD                     0xFC4AB000
static void* getbase() {
	unsigned long pipe_base = MDP_VP_0_VIG_0_BASE;
	unsigned int* src0_addr = (unsigned int*) (pipe_base + PIPE_SSPP_SRC0_ADDR);
	return (void*)*src0_addr;
}
int notmain (void *dtb) {
/*
	unsigned int* video = (unsigned int*) 0xf9000000;
	unsigned int* endram = video + 100000; //0x60000000;
	for (unsigned int* a = video; a < endram; a++) *a = 0xdeadbeef;
*/
	// simplest test code: just reboots the processo
	unsigned int* hold = (unsigned int*)MPM2_MPM_PS_HOLD;
	*hold = 0;
	while(1) {
	}
	return 0;
}
