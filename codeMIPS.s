.data
 .space 4   #place pour les symboles
 #place pour les lables de chaine de charactere
la0 : .asciiz "blabla"
la1 : .asciiz "i"
la2 : .asciiz "a"
la-1: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
la $s0,la0
sw $s0,0x10010000
a1:
li $s0,0
move $31,$s0
a2:
lw $s0,8($sp)
jr $s0
a3:
la $s0,la2
sw $s0,0($sp)
a4:
la $s0,la1
sw $s0,4($sp)
a5:
li $s0,7
sw $s0,0($sp)
a6:
j a0
a7:
li $s0,0
move $31,$s0
a8:
li $v0,10
syscall
