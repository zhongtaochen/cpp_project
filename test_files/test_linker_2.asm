test_or:
la $a0, or_
li $v0, 4
syscall

li $s1, 10 # 0b1010
li $s2, 12 # 0b1100
or $s3, $s1, $s2
bne $s3, 14, fail


test_ori:
la $a0, ori_
li $v0, 4
syscall

li $s1, 10 # 0b1010
ori $s2, $s1, 12
bne $s2, 14, fail


test_sll:
la $a0, sll_
li $v0, 4
syscall

li $s1, 10
sll $s1, $s1, 2
bne $s1, 40, fail


test_sllv:
la $a0, sllv_
li $v0, 4
syscall

li $s1, 10
li $s2, 2
sllv $s1, $s1, $s2
bne $s1, 40, fail


test_sra:
la $a0, sra_
li $v0, 4
syscall

li $s1, -1
sra $s1, $s1, 10
bne $s1, -1, fail


test_srav:
la $a0, srav_
li $v0, 4
syscall

li $s1, -1
li $s2, 10
srav $s1, $s1, $s2
bne $s1, -1, fail


test_srl:
la $a0, srl_
li $v0, 4
syscall

li $s1, 21 # 0b10101
srl $s1, $s1, 2
bne $s1, 5, fail


test_srlv:
la $a0, srlv_
li $v0, 4
syscall

li $s1, 21
li $s2, 2
srav $s1, $s1, $s2
bne $s1, 5, fail


test_sub:
la $a0, sub_
li $v0, 4
syscall

li $s1, 1
li $s2, -1
sub $s3, $s1, $s2
bne $s3, 2, fail
