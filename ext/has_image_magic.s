.section __TEXT,__text,regular,pure_instructions
.globl _has_image_magic
.p2align 2

_has_image_magic:
	stp	x29, x30, [sp, #-32]!
	mov	x29, sp

	// Open file
	mov	x1, #0			// O_RDONLY
	mov	x16, #5			// sys_open
	svc	#0x80

	b.cs	.L_error
	cmp	x0, #0
	b.lt	.L_error

	mov	w12, w0

	// Read file
	// fd already in w0
	add	x1, sp, #16		// buffer
	mov	x2, #8			// bytes count
	mov	x16, #3			// sys_read
	svc	#0x80

	mov	x13, x0

	// Close file
	mov	w0, w12			// grab the fd
	mov	x16, #6			// sys_close
	svc	#0x80

	// Check if 8 bytes
	cmp	x13, #8
	b.ne	.L_error

	// Load data
	add	x1, sp, #16
	ldr	x0, [x1]
	ldr	x1, =0x0A1A0A0D474E5089	// PNG magic bytes

	// Compare
	cmp	x0, x1
	cset	w0, eq
	b	.L_done

.L_error:
	mov	w0, #0

.L_done:
	ldp	x29, x30, [sp], #32
	ret
