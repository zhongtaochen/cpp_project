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
