.data
fileio_: .asciiz "Testing file IO ..."
filename: .asciiz "C:\Users\40455\tmp.txt" # You should change accordingly
pass_io_: .asciiz "File IO tests passed."
int_: .asciiz "Testing read_int, print_int ..."
read_int_: .asciiz "Enter an integer: "
print_int_: .asciiz "Entered integer is: "
char_: .asciiz "Testing read_char, print_char ..."
read_char_: .asciiz "Enter a char: "
print_char_: .asciiz "Entered char is: "
str_: .asciiz "Testing read_str_, print_str_, sbrk ... "
read_str_: .asciiz "Enter a 4-char string: "
print_str_: .asciiz "Entered string is: "
pass: .asciiz "Tests passed."

.text
test_fileio:
la $a0, fileio_
li $v0, 4
syscall

la $a0, filename
li $v0, 13
syscall
move $t0, $a0

la $a1, pass_io_
li $a2, 21
li $v0, 15
syscall

li $a0, 21
li $v0, 9
syscall

move $a1, $v0
move $a0, $t0
li $a2, 21
li $v0, 14
syscall

move $a0, $a1
li $v0, 4
syscall

test_int:
la $a0, int_
li $v0, 4
syscall

la $a0, read_int_
li $v0, 4
syscall

li $v0, 5
syscall
move $s0, $v0

la $a0, print_int_
li $v0, 4
syscall

move $a0, $s0
li $v0, 1
syscall


test_char:
la $a0, char_
li $v0, 4
syscall

la $a0, read_char_
li $v0, 4
syscall

li $v0, 12
syscall
move $s0, $v0

la $a0, print_char_
li $v0, 4
syscall

move $a0, $s0
li $v0, 11
syscall

addi $sp, $sp, 21 # restore


test_str:
la $a0, str_
li $v0, 4
syscall

la $a0, read_str_
li $v0, 4
syscall

li $a0, 4
li $v0, 9
syscall
move $t0, $v0

move $a0, $t0
li $a1, 4
li $v0, 8
syscall

la $a0, print_str_
li $v0, 4
syscall

move $a0, $t0
li $v0, 4
syscall


exit:
la $a0, pass
li $v0, 4
syscall

li $v0, 10
syscall
