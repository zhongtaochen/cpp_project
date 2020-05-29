.data
slt_: .asciiz "Testing slt ..."
sltu_: .asciiz "Testing sltu ..."
slti_: .asciiz "Testing slti ..."
sltiu_: .asciiz "Testing sltiu ..."
pass_: .asciiz "Tests all passed."
fail_: .asciiz "Test fails."


.text
test_slt:
la $a0, slt_
li $v0, 4
syscall

li $s1, -1
slt $s2, $s1, $zero
bne $s2, 1, fail


test_sltu:
la $a0, sltu_
li $v0, 4
syscall

li $s1, -1
sltu $s2, $s1, $zero
bne $s2, 0, fail

li $s1, 1
slt $s2, $zero, $s1
bne $s2, 1, fail


test_slti:
la $a0, slti_
li $v0, 4
syscall

li $s1, -1
slti $s2, $s1, 0
bne $s2, 1, fail


test_sltiu:
la $a0, sltiu_
li $v0, 4
syscall

li $s1, 1
sltiu $s2, $s1, -1
bne $s2, 1, fail


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
