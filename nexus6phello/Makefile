
ARMGNU ?= aarch64-linux-android

COPS = -Wall -O3 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a53 -std=gnu99
OBJS = start.o bootloader05.o dtb.o

gcc : kernel.img

all : gcc

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.s

%.o : %.c
	$(ARMGNU)-gcc $(COPS) -c $^ -o $@

%.o : %.s
	$(ARMGNU)-gcc $(COPS) -c $^ -o $@

%.o : %.S
	$(ARMGNU)-gcc $(COPS) -c $^ -o $@
dtb.o: huawei_angler_vn2.dtb
	$(ARMGNU)-objcopy -B aarch64 -O elf64-littleaarch64 -I binary $^ $@

kernel.img : loader $(OBJS)
	$(ARMGNU)-ld $(OBJS) $(LIBGCC) -T loader -o bootloader05.elf
	$(ARMGNU)-objdump -D bootloader05.elf > bootloader05.list
	$(ARMGNU)-objcopy bootloader05.elf -O ihex bootloader05.hex
	$(ARMGNU)-objcopy bootloader05.elf -O binary kernel.img

