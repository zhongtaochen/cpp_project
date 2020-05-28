.data
add_: .asciiz "Testing add ..."
addu_: .asciiz "Testing addu ..."
addi_: .asciiz "Testing addi ..."
addiu_: .asciiz "Testing addiu ..."
and_: .asciiz "Testing and ..."
andi_: .asciiz "Testing andi ..."
div_: .asciiz "Testing div ..."
divu_: .asciiz "Testing divu ..."
mult_: .asciiz "Testing mult ..."
multu_: .asciiz "Testing multu ..."
nor_: .asciiz "Testing nor ..."
or_: .asciiz "Testing or ..."
ori_: .asciiz "Testing ori ..."
sll_: .asciiz "Testing sll ..."
sllv_: .asciiz "Testing sllv ..."
sra_: .asciiz "Testing sra ..."
srav_: .asciiz "Testing srav ..."
srl_: .asciiz "Testing srl ..."
srlv_: .asciiz "Testing srlv ..."
sub_: .asciiz "Testing sub ..."
subu_: .asciiz "Testing subu ..."
xor_: .asciiz "Testing xor ..."
xori_: .asciiz "Testing xori ..."
pass_: .asciiz "Tests all passed."
fail_: .asciiz "Test fails."

.text
test_add:
la $a0, add_
li $v0, 4
syscall

li $s1, 1
li $s2, -1
add $s3, $s1, $s2
bne $s3, 0, fail


test_addu:
la $a0, addu_
li $v0, 4
syscall

li $s1, 1
li $s2, -1
addu $s3, $s1, $s2
bne $s3, 0, fail


test_addi:
la $a0, addu_
li $v0, 4
syscall

li $s1, 1
addi $s2, $s1, -1
bne $s3, 0, fail


test_addiu:
la $a0, addiu_
li $v0, 4
syscall

li $s1, 1
addiu $s2, $s1, -1
bne $s3, 0, fail


test_and:
la $a0, and_
li $v0, 4
syscall

li $s1, 10 # 0b1010
li $s2, 12 # 0b1100
and $s3, $s1, $s2
bne $s3, 8, fail

sdf

test_andi:
la $a0, andi_
li $v0, 4
syscall

li $s1, 10 # 0b1010
andi $s2, $s1, 12
bne $s2, 8, fail


test_div:
la $a0, div_
li $v0, 4
syscall

li $s1, 20
li $s2, -6
div $s1, $s2
mfhi $s3
bne $s3, 2, fail
mflo $s3
bne $s3, -3, fail


test_divu:
la $a0, divu_
li $v0, 4
syscall

li $s1, 20
li $s2, 6
divu $s1, $s2
mfhi $s3
bne $s3, 2, fail
mflo $s3
bne $s3, 3, fail


test_mult:
la $a0, mult_
li $v0, 4
syscall

li $s1, 1
li $s2, -1
mult $s1, $s2
mfhi $s3
bne $s3, -1, fail
mflo $s3
bne $s3, -1, fail


test_multu:
la $a0, multu_
li $v0, 4
syscall

li $s1, 1
li $s2, 3
mult $s1, $s2
mfhi $s3
bne $s3, 0, fail
mflo $s3
bne $s3, 3, fail


test_nor:
la $a0, nor_
li $v0, 4
syscall

li $s1, -1
li $s2, -1
nor $s3, $s1, $s2
bne $s3, 0, fail


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
