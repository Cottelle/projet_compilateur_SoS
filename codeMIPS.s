.data
 .space 4   #place pour les symboles
 #place pour les lables de chaine de charactere
la0 : .asciiz "aaaaaaaaaaaaaaa"
la-1: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
la $s0,la0
sw $s0,0x10010000
a1:
lw $s0,0x10010000
move $23,$s0
a2:
lw $s0,23
li $s1,3
add $s0,$s0,$s1
sw $s0,23
a3:
lw $s0,23
li $s1,1
mult $s0,$s1
mflo $s0
sw $s0,23
a4:
move $s0,$23
a5:
li $v0,10
syscall
a6:
li $s0,0
move $31,$s0
a7:
li $v0,10
syscall
