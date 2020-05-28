.data
la_li_abs_: .asciiz "Testing la, li, abs ..."
b_nop_: .asciiz "Testing b, nop ..."
bal_: .asciiz "Testing bal ..."
beq_: .asciiz "Testing beq ..."
beqz_: .asciiz "Testing beqz ..."
bge_: .asciiz "Testing bge ..."
bgt_: .asciiz "Testing bgt ..."
bgtu_: .asciiz "Testing bgtu ..."
ble_: .asciiz "Testing ble ..."
blt_: .asciiz "Testing blt ..."
bne_: .asciiz "Testing bne ..."
clear_: .asciiz "Testing clear ..."
div_: .asciiz "Testing div ..."
move_: .asciiz "Testing move ..."
mul_: .asciiz "Testing mul ..."
mulou_: .asciiz "Testing mulou ..."
not_: .asciiz "Testing not ..."
rem_: .asciiz "Testing rem ..."
remu_: .asciiz "Testing remu ..."
pass_: .asciiz "Tests all passed."
fail_: .asciiz "Test fails."


.text
test_la_li_abs:
la $a0, la_li_abs_
li $v0, 4
syscall

li, $s1, -10
abs $s1, $s1
bne $s1, 10, fail


test_b_nop:
la $a0, b_nop_
li $v0, 4
syscall

b l1
j fail
l1: nop


test_bal:
la $a0, bal_
li $v0, 4
syscall

bal l2
j fail
l2:
la $s1, l2
addi $s1, $s1, -4
bne $s1, $ra, fail


test_beq:
la $a0, beq_
li $v0, 4
syscall

li $s1, -1
beq $s1, -1, l3
j fail
l3: nop


test_beqz:
la $a0, beqz_
li $v0, 4
syscall

li $s1, 0
beqz $s1, l4
j fail
l4: nop


test_bge:
la $a0, bge_
li $v0, 4
syscall

li $s1, -1
li $s2, -2
bge $s1, $s2, l5
j fail
l5: nop


test_bgt:
la $a0, bgt_
li $v0, 4
syscall

li $s1, -1
li $s2, -2
bgt $s1, $s2, l6
j fail
l6: nop


test_bgtu:
la $a0, bgtu_
li $v0, 4
syscall

li $s1, -1
bgtu $s1, $zero, l7
j fail
l7: nop


test_ble:
la $a0, ble_
li $v0, 4
syscall

li $s1, -1
ble $s1, $zero, l8
j fail
l8: nop


test_blt:
la $a0, blt_
li $v0, 4
syscall

li $s1, -1
blt $s1, $zero, l9
j fail
l9: nop


test_bne:
la $a0, bne_
li $v0, 4
syscall

li $s1, -1
bne $s1, 0, l10
j fail
l10: nop


test_clear:
la $a0, clear_
li $v0, 4
syscall

li $s1, -1
clear $s1
bne $s1, 0, fail


test_div:
la $a0, div_
li $v0, 4
syscall

li $s1, 20
li $s2, 6
div $s3, $s1, $s2
bne $s3, 3, fail


test_move:
la $a0, move_
li $v0, 4
syscall

li $s1, 10
li $s2, 6
move $s2, $s1
bne $s2, 10, fail


test_mul:
la $a0, mul_
li $v0, 4
syscall

li $s1, -10
li $s2, -10
mul $s3, $s1, $s2
bne $s3, 100, fail


test_mulou:
la $a0, mulou_
li $v0, 4
syscall

li $s1, 10
li $s2, 10
mulou $s3, $s1, $s2
bne $s3, 100, fail


test_not:
la $a0, not_
li $v0, 4
syscall

li $s1, -1
not $s1, $s1
bne $s1, 0, fail


test_rem:
la $a0, rem_
li $v0, 4
syscall

li $s1, 20
li $s2, -6
rem $s3, $s1, $s2
bne $s3, 2, fail


test_remu:
la $a0, remu_
li $v0, 4
syscall

li $s1, 20
li $s2, 6
remu $s3, $s1, $s2
bne $s3, 2, fail


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
