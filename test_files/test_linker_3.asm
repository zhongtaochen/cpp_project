test_subu:
la $a0, subu_
li $v0, 4
syscall

li $s1, 1
li $s2, 1
subu $s3, $s1, $s2
bne $s3, 0, fail


test_xor:
la $a0, xor_
li $v0, 4
syscall

li $s1, 10 # 0b1010
li $s2, 12 # 0b1100
xor $s3, $s1, $s2
bne $s3, 6, fail


test_xori:
la $a0, xori_
li $v0, 4
syscall

li $s1, 10 # 0b1010
xori $s2, $s1, 12
bne $s2, 6, fail


exit:
la $a0, pass_
li $v0, 4
syscall

li $v0, 10
syscall

fail:
la $a0, fail_
li $v0, 4
syscall

li $v0, 10
syscall
