.text

.global return_0_warmup
.global return_0_aligned_8
.global return_0_aligned_16
.global return_0_aligned_32
.global return_0_aligned_64
.global return_0_aligned_128
.global return_0_aligned_256
.global return_0_aligned_512
.global return_0_aligned_1024
.global return_0_aligned_2048
.global return_0_aligned_4096
.global return_0_cross_8
.global return_0_cross_16
.global return_0_cross_32
.global return_0_cross_64
.global return_0_cross_128
.global return_0_cross_256
.global return_0_cross_512
.global return_0_cross_1024
.global return_0_cross_2048
.global return_0_cross_4096

.type return_0_warmup, @function
.type return_0_aligned_8, @function
.type return_0_aligned_16, @function
.type return_0_aligned_32, @function
.type return_0_aligned_64, @function
.type return_0_aligned_128, @function
.type return_0_aligned_256, @function
.type return_0_aligned_512, @function
.type return_0_aligned_1024, @function
.type return_0_aligned_2048, @function
.type return_0_aligned_4096, @function
.type return_0_cross_8, @function
.type return_0_cross_16, @function
.type return_0_cross_32, @function
.type return_0_cross_64, @function
.type return_0_cross_128, @function
.type return_0_cross_256, @function
.type return_0_cross_512, @function
.type return_0_cross_1024, @function
.type return_0_cross_2048, @function
.type return_0_cross_4096, @function

return_0_warmup:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 8, 0
return_0_aligned_8:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 16, 0
return_0_aligned_16:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 32, 0
return_0_aligned_32:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 64, 0
return_0_aligned_64:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 128, 0
return_0_aligned_128:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 256, 0
return_0_aligned_256:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 512, 0
return_0_aligned_512:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 1024, 0
return_0_aligned_1024:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 2048, 0
return_0_aligned_2048:
	xorq %rax, %rax
	ret

.align 4096, 0
return_0_aligned_4096:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 7, 0
return_0_cross_8:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 15, 0
return_0_cross_16:
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
.skip 255, 0
return_0_cross_256:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 511, 0
return_0_cross_512:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 1023, 0
return_0_cross_1024:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 2047, 0
return_0_cross_2048:
	xorq %rax, %rax
	ret

.align 4096, 0
.skip 4095, 0
return_0_cross_4096:
	xorq %rax, %rax
	ret
