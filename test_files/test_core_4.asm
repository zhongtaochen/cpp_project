.data
teq_: .asciiz "Testing teq, expecting an exception ..."
teqi_: .asciiz "Testing teqi, expecting an exception ..."
tne_: .asciiz "Testing tne, expecting an exception ..."
tnei_: .asciiz "Testing tnei, expecting an exception ..."
tge_: .asciiz "Testing tge, expecting an exception ..."
tgeu_: .asciiz "Testing tgeu, expecting an exception ..."
tgei_: .asciiz "Testing tgei, expecting an exception ..."
tgeiu_: .asciiz "Testing tgeiu, expecting an exception ..."
tlt_: .asciiz "Testing tlt, expecting an exception ..."
tltu_: .asciiz "Testing tltu, expecting an exception ..."
tlti_: .asciiz "Testing tlti, expecting an exception ..."
tltiu_: .asciiz "Testing tltiu, expecting an exception ..."
pass_: .asciiz "Tests all passed."


.text
test_teq:
la $a0, teq_
li $v0, 4
syscall

li $s0, -1
li $s1, -1
teq $s0, $s1


test_teqi:
la $a0, teqi_
li $v0, 4
syscall

li $s0, -1
teqi $s0, -1


test_tne:
la $a0, tne_
li $v0, 4
syscall

li $s0, -1
li $s1, -2
tne $s0, $s1


test_tnei:
la $a0, tnei_
li $v0, 4
syscall

li $s0, -1
tnei $s0, -2


test_tge:
la $a0, tge_
li $v0, 4
syscall

li $s0, -1
li $s1, -2
tge $s0, $s1


test_tgeu:
la $a0, tgeu_
li $v0, 4
syscall

li $s0, -1
li $s1, -2
tgeu $s0, $s1


test_tgei:
la $a0, tgei_
li $v0, 4
syscall

li $s0, -1
tgei $s0, -2


test_tgeiu:
la $a0, tgeiu_
li $v0, 4
syscall

li $s0, -1
tgeiu $s0, -2


test_tlt:
la $a0, tlt_
li $v0, 4
syscall

li $s0, -1
li $s1, -2
tlt $s1, $s0


test_tltu:
la $a0, tltu_
li $v0, 4
syscall

li $s0, -1
li $s1, -2
tltu $s1, $s0


test_tlti:
la $a0, tlti_
li $v0, 4
syscall

li $s0, -2
tlti $s0, -1


test_tltiu:
la $a0, tltiu_
li $v0, 4
syscall

li $s0, -2
tltiu $s0, -1


exit:
la $a0, pass_
li $v0, 4
syscall

li $v0, 10
syscall
