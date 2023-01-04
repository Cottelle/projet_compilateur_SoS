<<<<<<< HEAD
li $s0,0
sw $s0,2
=======
.data
 .space 2   #place pour les symboles
 #place pour les lables de chaine de charactere
la0 : .asciiz "aaaaaaaaaaaaaaaa"
la1 : .asciiz "bbbbbbbbbbbbbb"
la-1: .space 32         #the buffer for the read buffer of siez 32
  

 .text
lw $s0,0
sw $s0,0
lw $s0,1
sw $s0,4
li $s0,0
sw $s0,31
li $v0,10
syscall
>>>>>>> 76d0f634a8ee0f5ad479fa31463c2301acd34e71
