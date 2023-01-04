.data
 .space 12   #place pour les symboles
 #place pour les lables de chaine de charactere
la0 : .asciiz "aaaaaaaaaaaa"
la1 : .asciiz "bbbbbbbbbbbbb"
la2 : .asciiz "aze"
la3 : .asciiz "qsd"
la4 : .asciiz "wx"
la-1: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
la $s0,la0
sw $s0,0x10010000
a1:
j a2
a2:
la $s0,la1
sw $s0,0x10010004
a3:
j a4
a4:
li $s0,0
sw $s0,0x10010008
a5:
move $s0,$31
jr $s0
a6:
la $s0,la4
sw $s0,0($sp)
a7:
la $s0,la3
sw $s0,4($sp)
a8:
la $s0,la2
sw $s0,8($sp)
a9:
j a0
a10:
li $v0,10
syscall
