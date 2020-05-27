.data
beq_: .asciiz "Testing beq ..."
bgez_: .asciiz "Testing bgez ..."
bgezal_: .asciiz "Testing bgezal ..."
bgtz_: .asciiz "Testing bgtz ..."
blez_: .asciiz "Testing blez ..."
bltzal_: .asciiz "Testing bltzal ..."
bltz_: .asciiz "Testing bltz ..."
bne_: .asciiz "Testing bne ..."
j_: .asciiz "Testing j ..."
jal_: .asciiz "Testing jal ..."
jalr_: .asciiz "Testing jalr ..."
jr_: .asciiz "Testing jr ..."
pass_: .asciiz "Tests all passed."
fail_: .asciiz "Test fails."

.text
test_beq: 
la $a0, beq_
li $v0, 4
syscall

beq $zero, $zero, l1
j fail
l1: nop

test_bgez:
la $a0, bgez_
li $v0, 4
syscall

li $s1, 1
bgez $s1, l2
j fail
l2: nop


test_bgezal:
la $a0, bgezal_
li $v0, 4
syscall

li $s1, 1
bgezal $s1, l3
j fail
l3:
la $s2, l3
addi $s2, $s2, -4
bne $ra, $s2, fail


test_bgtz:
la $a0, bgtz_
li $v0, 4
syscall

li $s1, 1
bgtz $s1, l4
j fail
l4: nop


test_blez:
la $a0, bgtz_
li $v0, 4
syscall

li $s1, -1
blez $s1, l5
j fail
l5: nop


test_bltzal:
la $a0, bltzal_
li $v0, 4
syscall

li $s1, -1
bltzal $s1, l6
j fail
l6:
la $s2, l6
addi $s2, $s2, -4
bne $ra, $s2, fail


test_bltz:
la $a0, bltz_
li $v0, 4
syscall

li $s1, -1
bltz $s1, l7
j fail
l7: nop


test_bne:
la $a0, bne_
li $v0, 4
syscall

li $s1, 1
bne $s1, $zero, l8
j fail
l8: nop


test_j:
la $a0, j_
li $v0, 4
syscall

j l9
j fail
l9: nop


test_jal:
la $a0, jal_
li $v0, 4
syscall

jal l10
j fail
l10:
la $s1, l10
addi $s1, $s1, -4
bne $ra, $s1, fail


test_jalr:
la $a0, jalr_
li $v0, 4
syscall

la $s1, l11
jalr $s1, $s2
j fail
l11:
la $s3, l11
addi $s3, $s3, -4
bne $s2, $s3, fail


test_jr:
la $a0, jr_
li $v0, 4
syscall

la $s1, l12
jr $s1
j fail
l12: nop


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
