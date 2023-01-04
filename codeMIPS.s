.data
 .space 8   #place pour les symboles
 #place pour les lables de chaine de charactere
la1 : .asciiz "aaaaaaaaaaaaaaaaaaa"
la2 : .asciiz "3"
la3 : .asciiz "a"
la4 : .asciiz "a"
la5 : .asciiz "a"
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
la $s0,la1
sw $s0,0x10010000
a1:
la $s0,la2
sw $s0,16($sp)
a2:
move $s0,$31
a3:
j a0
a4:
lw $s0,20($sp)
move $31,$s0
a5:
li $s0,0
sw $s0,0x10010004
a6:
move $s0,$31
jr $s0
a7:
la $s0,la5
sw $s0,0($sp)
a8:
la $s0,la4
sw $s0,4($sp)
a9:
la $s0,la3
sw $s0,8($sp)
a10:
move $s0,$31
a11:
j a0
a12:
lw $s0,12($sp)
move $31,$s0
a13:
li $v0,10
syscall
