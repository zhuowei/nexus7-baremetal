
ARMGNU ?= arm-linux-gnueabihf
#ARMGNU ?= arm-linux-androideabi

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -mcpu=cortex-a9 -std=gnu99 -marm -mthumb-interwork

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


start.o : start.s
	$(ARMGNU)-gcc $(COPS) -c start.s -o start.o

bootloader05.o : bootloader05.c
	$(ARMGNU)-gcc $(COPS) -c bootloader05.c -o bootloader05.o

kernel.img : loader start.o bootloader05.o 
	$(ARMGNU)-ld start.o bootloader05.o -T loader -o bootloader05.elf
	arm-linux-androideabi-objdump -D bootloader05.elf > bootloader05.list
	$(ARMGNU)-objcopy bootloader05.elf -O ihex bootloader05.hex
	$(ARMGNU)-objcopy bootloader05.elf -O binary kernel.img

