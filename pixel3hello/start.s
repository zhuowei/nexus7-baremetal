
.globl _start
_start:
    b asm_start
    .int 0
    .quad 0x80000 // 0x80008: image load offset
    .quad (_end - _start) // 0x80010: effective image size
    .quad 0xa // 0x80018: kernel flags; 4K pages, no 2MB req, little endian
    .quad 0 // 0x80020: reserved
    .quad 0 // 0x80028: reserved
    .quad 0 // 0x80030: reserved
    .int 0x644d5241 // 0x80038
    .int 0 // 0x8003c
asm_start:
    mov x1,0x81000000
    mov sp, x1
    bl notmain
