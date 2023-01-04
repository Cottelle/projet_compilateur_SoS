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

_read:
li $v0,8
li $a1,31
la $a0, l0
syscall
li $t0,0
la $9,l0

loop: 			#taille du buffer lu 
lb $t2 , ($9)
beq $t2, $0 , exit
addi $t0, $t0, 1
addi $9 , $t1, 1
j loop

exit : 
li $v0, 9
move $a0 , $t0			#alloue
syscall
la $9,l0
move $11, $v0

loop2 :
beq $t0,$0 , exit2
lb $t2, ($9)
sb $t2, ($v0)
addi $9,$9,1
addi $v0,$v0,1
addi $t0,$t0,-1
j loop2

exit2 :
jr $31					#resulat ds $11
#the value allocated is in $11

strconcat:

strconcatboucle:
lb $t1,0($a0)
beq $t1,$zero,boucledeuxiemechaine
sb $t1,0($a2)
addi $a0,$a0,1
addi $a2,$a2,1
j strconcatboucle

boucledeuxiemechaine:
lb $t1,0($a1)
beq $t1,$zero,strconcatfin
sb $t1,0($a2)
addi $a1,$a1,1
addi $a2,$a2,1
j boucledeuxiemechaine

strconcatfin:
li $t1,0
sb $t1,0($a2)
jr $ra

strlen:
li $t0,0

strlenboucle:
lb $t1,0($a0)
beq $t1,$zero,strlenfin
addi $a0,$a0,1
addi $t0,$t0,1
j strlenboucle

strlenfin:
jr $ra
