.data
 .space 4   #place pour les symboles
 #place pour les lables de chaine de charactere
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
move $s0,$31
a1:
a2:
move $s0,$11
a3:
lw $s0,0($sp)
move $31,$s0
a4:
li $v0,10
syscall
