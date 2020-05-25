.data
str: .asciiz "Hello World"

.text
la $a0, str
addi $v0, $zero, 4
syscall
