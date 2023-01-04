.data
 .space 4   #place pour les symboles
 #place pour les lables de chaine de charactere
la1 : .asciiz "qdqsd sqdqsd"
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
la $s0,la1
sw $s0,0x10010000
a1:
li $v0,10
syscall
