# Bare metal example for the Android Emulator (goldfish-armv7)

Writes out "Full yolo motion!" to the serial console. Based on the serial writing routine from https://android.googlesource.com/kernel/goldfish/+/android-goldfish-3.4/arch/arm/mach-goldfish/include/mach/uncompress.h .

To run it:

`emulator -verbose -avd IceCreamEmu -shell -show-kernel -qemu -kernel kernel.img`

replace IceCreamEmu with your own AVD name.
