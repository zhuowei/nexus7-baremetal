Some experiments with running code directly from the bootloader of an Asus Nexus 7 (grouper).

For those without a Nexus 7, a sample bare metal program that runs on the Android emulator is also included.

To run an image:

Install Android NDK

`make`

`fastboot boot kernel.img`

Contains code from https://github.com/dwelch67/raspberrypi/tree/master/bootloader05 .
