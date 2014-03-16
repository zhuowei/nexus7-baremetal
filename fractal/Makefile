
ARMGNU ?= arm-linux-gnueabi

COPS = -Wall -O3 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a9 -std=gnu99 -marm -mthumb-interwork
OBJS = start.o bootloader05.o bzero.o
LIBGCC = /usr/lib/gcc-cross/arm-linux-gnueabi/4.7/libgcc.a

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

kernel.img : loader $(OBJS)
	$(ARMGNU)-ld $(OBJS) $(LIBGCC) -T loader -o bootloader05.elf
	arm-linux-androideabi-objdump -D bootloader05.elf > bootloader05.list
	$(ARMGNU)-objcopy bootloader05.elf -O ihex bootloader05.hex
	$(ARMGNU)-objcopy bootloader05.elf -O binary kernel.img

