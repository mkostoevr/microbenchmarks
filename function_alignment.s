.text

.global return_0_aligned_4096
.global return_0_cross_32
.global return_0_cross_64
.global return_0_cross_128
.global return_0_cross_4096

.type return_0_aligned_4096, @function
.type return_0_cross_32, @function
.type return_0_cross_64, @function
.type return_0_cross_128, @function
.type return_0_cross_4096, @function

.align 4096, 0
return_0_aligned_4096:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 31, 0
return_0_cross_32:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 63, 0
return_0_cross_64:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 127, 0
return_0_cross_128:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 4095, 0
return_0_cross_4096:
	xorq %rax, %rax
	ret
