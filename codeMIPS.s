.data
 .space 16   #place pour les symboles
 #place pour les lables de chaine de charactere
la1 : .asciiz "fffffffff"
la2 : .asciiz "aaaaaaaaaaaaaaaaaaa"
la3 : .asciiz "bbbbbbbbbbbbbbbbbbbb"
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
j a4
a1:
la $s0,la1
sw $s0,0x10010000
a2:
li $s0,0
sw $s0,0x10010004
a3:
move $s0,$31
jr $s0
a4:
j a7
a5:
la $s0,la2
sw $s0,0x10010008
a6:
j a9
a7:
la $s0,la3
sw $s0,0x10010008
a8:
j a9
a9:
move $s0,$31
a10:
jal _read
a11:
move $s0,$11
a12:
lw $s0,0($sp)
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

_read:
li $v0,8
li $a1,31
la $a0, la0
syscall
li $t0,0
la $9,la0

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
la $9,la0
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
