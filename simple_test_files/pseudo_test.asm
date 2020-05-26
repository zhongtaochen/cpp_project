.data
str: .asciiz "Hello World"
str1: .asciiz "Expected:100, Actual:"
str2: .asciiz "If you see this, branching is not working."

.text
la $a0, str
li $v0, 4
syscall # print_string str

test_mul:
la $a0, str1
li $v0, 4
syscall # print_string str1

li $t1, -10
li $t2, -10
mul $a0, $t1, $t2
li $v0, 1
syscall # print_int 100

test_abs:
la $a0, str1
li $v0, 4
syscall # print_string str1

addi $a0, $v0, -100
abs $a0, $a0
li $v0, 1
syscall # print_int 100

test_move_clear_branch:
move $s1, $v0
clear $s1
beqz $s1, exit

skipped:
la $a0, str2
li $v0, 4
syscall # print_string str2

exit:
li $v0, 10
syscall
