.text
loop:	beq $t0, $t3, end
	addi $t2,$t2, 4
	addi $t3, $t3, 1			#increment $t3
	j loop
end:	sw $t1, 0($t2)				#put grade in place
	add $v1, $t2, $zero			#return the address of the changed grade
	lw $v0, 0($sp)				#restore original $v0
	addi $sp, $sp, 4
	jr $ra
