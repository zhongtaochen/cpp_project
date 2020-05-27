.data
sb_lb_lbu_: .asciiz "Testing sb, lb, lbu ..."
sh_lh_lhu: .asciiz "Testing sh, lh, lhu ..."
sw_lw_: .asciiz "Testing sw, lw ..."
pass_: .asciiz "Tests all passed."
fail_: .asciiz "Test fails."


.text
li $v0, 9
li $a0, 4
syscall
move $t0, $v0

test_sb_lb_lbu:
la $a0, sb_lb_lbu_
li $v0, 4
syscall

li $s0, -1
sb $s0, 0($t0)

lb $s0, 0($t0)
bne $s0, -1, fail

lbu $s0, 0($t0)
bne $s0, 255, fail


test_sh_lh_lhu:
la $a0, sh_lh_lhu
li $v0, 4
syscall

li $s0, -1
sh $s0, 0($t0)

lh $s0, 0($t0)
bne $s0, -1, fail

lhu $s0, 0($t0)
bne $s0, 65535, fail


test_sw_lw:
la $a0, sw_lw_
li $v0, 4
syscall

li $s0, -1
sw $s0, 0($t0)

lw $s0, 0($t0)
bne $s0, -1, fail


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
