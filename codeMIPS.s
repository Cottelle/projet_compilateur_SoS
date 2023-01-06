.data
 .space 24   #place pour les symboles
 #place pour les lables de chaine de charactere
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
j a7
a1:
move $s0,$23
li $s1,4
mult $s0,$s1
mflo $s0
move $23,$s0
a2:
j a5
a3:
move $s0,$31
sw $s0,0($sp)
a4:
jal _read
a5:
li $s0,0
move $2,$s0
a6:
move $s0,$31
jr $s0
a7:
move $s0,$29
sw $s0,0($sp)
a8:
move $s0,$31
sw $s0,4($sp)
a9:
move $s0,$29
li $s1,8
add $s0,$s0,$s1
move $29,$s0
a10:
la $s0,la3
sw $s0,0($sp)
a11:
la $s0,la4
sw $s0,4($sp)
a12:
jal a1
a13:
lw $s0,-4($sp)
move $31,$s0
a14:
lw $s0,-8($sp)
move $29,$s0
a15:
lw $s0,0x10010004
sw $s0,0x10010014
a35:
move $s0,$31
move $22,$s0
a36:
jal a37
a37:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010010
a38:
move $s0,$22
move $31,$s0
a39:
j a53
a40:
lw $s0,0x10010008
sw $s0,0x10010014
a41:
move $s0,$31
move $22,$s0
a42:
jal a43
a43:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010010
a44:
move $s0,$22
move $31,$s0
a45:
j a53
a46:
lw $s0,0x1001000c
sw $s0,0x10010014
a47:
move $s0,$31
move $22,$s0
a48:
jal a49
a49:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010010
a50:
move $s0,$22
move $31,$s0
a51:
j a53
a52:
j a56
a53:
lw $s0,0x10010014
move $4,$s0
a16:
li $v0,4
syscall
a17:
li $s0,0
move $2,$s0
a18:
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
li $a0,9
syscall

strconcatboucle:
lb $t1,0($a1)
beq $t1,$zero,boucledeuxiemechaine
sb $t1,0($v0)
addi $a1,$a1,1
addi $v0,$v0,1
j strconcatboucle

boucledeuxiemechaine:
lb $t1,0($a2)
beq $t1,$zero,strconcatfin
sb $t1,0($v0)
addi $a2,$a2,1
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

strtoint:

initboucle:
lb $t1,0($a0)
beq $t1,$zero,initfin
addi $a0,$a0,1
j initboucle

initfin:
addi $a0,$a0,-1
move $t4,$a0

li $t0,1
li $t1,0
li $t2,1

strtointboucle:
lb $t3,0($t4)
beq $t3,$zero,strtointfin
beq $t3,45,strtointnegatif
beq $t3,43,strtointpositif
blt $t3,48,error
bgt $t3,57,error
addi $t3,$t3,-48
mult $t3,$t0
mflo $t3
add $t1,$t1,$t3
addi $s0,$0,10
mult $t0,$s0
mflo $t0
addi $t4,$t4,-1
j strtointboucle

strtointnegatif:
addi $t2,$t2,-1
j strtointfin

strtointpositif:
addi $t2,$t2,1
j strtointfin

error:
li $t1,0
li $v0,10
syscall          #la fonction échoue, on veut convertir des strings non compatibles

strtointfin:
mult $t2,$t1
mflo $t1
li $t0,0
li $t3,0
li $t4,0
jr $ra       #la fonction a bien terminé
