
.globl _start
_start:
    mov sp,0x100000
    bl notmain
    .quad 0 // 0x80008: image load offset
    .quad 0 // 0x80010: effective image size
    .quad 0 // 0x80018: kernel flags
    .quad 0 // 0x80020: reserved
    .int 0 // 0x80028: reserved
    .int (_binary_huawei_angler_vn2_dtb_start - _start)// 0x8002c
    .quad 0 // 0x80030: reserved
    .int 0x644d5241 // 0x80038
    .int 0 // 0x8003c
