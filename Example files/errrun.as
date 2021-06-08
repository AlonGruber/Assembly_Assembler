;file ps.as
;sample source code

random text
////
.entry	Next
.extern wNumber

STR:	.asciz	"aBcd"
	.asciz
	.asciz 123
MAIN:	add $3,44,$9
LOOP:	ori 4,-88888,$2
	la val1
	jmp Next
Next:	move	$20,$4,$20
LIST:	.db	300,-9
	bgt $4,$2,END
	la	K
	.db
LIST:	sw $0,4,$10,$5
	bne $31,$9,LOOP
	call val1
add:	jmp $4
	jump $4
	la wNumber label
.extern val1
.entry val1
	.dh 27056, 77777
K:	.dw 31,-12
END:	stop stop
