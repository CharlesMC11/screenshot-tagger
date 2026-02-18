/*!
 * Read the first 12-16 bytes of a file to determine if it belongs to a
 * supported photographic format
 * @environment AArch64 (Apple Silicon), macOS ABI
 * @param x0 (int fd): File descriptor to read from
 * @return w0 (bool): 1 if file matches PNG, HEIC, JPEG, or TIFF; 0 otherwise
 */

.section __TEXT,__text,regular,pure_instructions
.globl _is_image
.p2align 2

.extern _read

_is_image:
    pacia   x30, sp
    stp     x29, x30, [sp, #-32]!       // reserve a 16-byte buffer
    mov     x29, sp

    // Read file
    add     x1, sp, #16                 // load the 16-byte buffer
    mov     x2, #16                     // read 16 bytes from the file
    bl      _read

    cmp     x0, #12                     // Check if at least 12 bytes were read
    b.lt   .L_false

    ldr     q0, [sp, #16]               // Load the file header into SIMD lane

    // PNG: 89 50 4E 47 0D 0A 1A 0A
    movz    x1, #0x5089
    movk    x1, #0x474E, lsl #16
    movk    x1, #0x0A0D, lsl #32
    movk    x1, #0x0A1A, lsl #48
    fmov    d1, x1                      // Move 64-bit pattern to SIMD lane
    cmeq    v1.2d, v0.2d, v1.2d         // If bits match, lane becomes all 1s

    // HEIF: 'ftypheic' or 'ftypmif1' at offset 4
    ext     v2.16b, v0.16b, v0.16b, #4
    movz    x2, #0x7466                 // 'ft'
    movk    x2, #0x7079, lsl #16        // 'yp'
    movk    x2, #0x6568, lsl #32        // 'he'
    movk    x2, #0x6369, lsl #48        // 'ic'
    fmov    d2, x2
    cmeq    v2.2d, v1.2d, v2.2d

    orr     v1.16b, v1.16b, v2.16b

    fmov    x1, d1
    cbnz    x1, .L_true

    // JPEG: FF D8 FF
    fmov    w1, s0
    and     w1, w1, #0xFFFFFF
    mov     w2, #0xD8FF
    movk    w2, #0x00FF, lsl #16
    cmp     w1, w2
    b.eq    .L_true

    // TIFF: 'II' (49 49 2A 00) or 'MM'(4D 4D 00 2A)
    fmov    w1, s0
    mov     w2, #0x4949                 // 'II'
    movk    w2, #0x002A, lsl #16
    cmp     w1, w2
    b.eq    .L_true

    mov     w2, #0x4D4D                 // 'MM'
    movk    w2, #0x2A00, lsl #16
    cmp     w1, w2
    b.eq    .L_true

.L_false:
    mov     w0, #0
    b       .L_done

.L_true:
    mov     w0, #1

.L_done:
    ldp     x29, x30, [sp], #32
    retaa
