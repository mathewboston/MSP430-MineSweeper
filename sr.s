	.arch msp430g2553
	.p2align 1,0
	.text

	;;  routines to access sr

	.global set_sr
set_sr:	mov r15, r2		
	ret

	.global get_sr
get_sr:	mov r2, r15
	ret

	.global or_sr
or_sr:	bis r15, r2
	ret
	
	.global and_sr
and_sr:	and r15, r2
	ret
