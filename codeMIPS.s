.data
 .space 8   #place pour les symboles
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
sw $s0,0x10010004
a2:
move $s0,$31
jr $s0
a3:
la $s0,la2
sw $s0,0($sp)
a4:
la $s0,la1
sw $s0,4($sp)
a5:
j a0
a6:
li $v0,10
syscall
