main:addi $a0, $zero, 4
addi $v0, $zero, 9
syscall
sub $t0, $v0, $zero
addi $a0, $zero, 4
addi $v0, $zero, 9
syscall
sub $a0, $v0, $zero
addi $a1, $zero, 4
addi $v0, $zero, 8
syscall
lw $t1, 0($a0)
sw $t1, 0($t0)
sub $a0, $t0, $zero
addi $v0, $zero, 4
syscall
addi $v0, $zero, 10
syscall

