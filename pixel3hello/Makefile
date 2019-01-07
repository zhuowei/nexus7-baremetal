
ARMGNU ?= aarch64-linux-gnu

COPS = -Wall -Os -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a53 -std=gnu99
OBJS = start.o bootloader05.o

gcc : kernel.img bootable.img

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

kernel.img : loader $(OBJS)
	$(ARMGNU)-ld $(OBJS) $(LIBGCC) -T loader -o bootloader05.elf
	$(ARMGNU)-objdump -D bootloader05.elf > bootloader05.list
	$(ARMGNU)-objcopy bootloader05.elf -O ihex bootloader05.hex
	$(ARMGNU)-objcopy bootloader05.elf -O binary kernel.img

bootable.img: kernel.img devicetree.dtb
	gzip -c kernel.img >bootable.img
	cat devicetree.dtb >>bootable.img

