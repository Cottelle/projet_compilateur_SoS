.data
 .space 8   #place pour les symboles
 #place pour les lables de chaine de charactere
la1 : .asciiz "Hello"
la2 : .asciiz " "
la3 : .asciiz "World"
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
la $s0,la1
sw $s0,0x10010004
a1:
move $s0,$31
move $22,$s0
a2:
jal a3
a3:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010000
a4:
move $s0,$22
move $31,$s0
a5:
j a19
a6:
la $s0,la2
sw $s0,0x10010004
a7:
move $s0,$31
move $22,$s0
a8:
jal a9
a9:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010000
a10:
move $s0,$22
move $31,$s0
a11:
j a19
a12:
la $s0,la3
sw $s0,0x10010004
a13:
move $s0,$31
move $22,$s0
a14:
jal a15
a15:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010000
a16:
move $s0,$22
move $31,$s0
a17:
j a19
a18:
j a22
a19:
lw $s0,0x10010004
move $4,$s0
a20:
li $v0,4
syscall
a21:
lw $s0,0x10010000
jr $s0
a22:
li $v0,10
syscall

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
jal strlen
jal strlen2
add $t0,$t0,$t3
li $v0,9
syscall

strconcatboucle:
lb $t1,0($a0)
beq $t1,$zero,boucledeuxiemechaine
sb $t1,0($v0)
addi $a0,$a0,1
addi $v0,$v0,1
j strconcatboucle

boucledeuxiemechaine:
lb $t1,0($a1)
beq $t1,$zero,strconcatfin
sb $t1,0($v0)
addi $a1,$a1,1
addi $v0,$v0,1
j boucledeuxiemechaine

strconcatfin:
li $t1,0
sb $t1,0($v0)
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

strlen2:
li $t3,0

strlen2boucle:
lb $t1,0($a1)
beq $t1,$zero,strlen2fin
addi $a1,$a1,1
addi $t3,$t3,1
j strlen2boucle

strlen2fin:
jr $ra
