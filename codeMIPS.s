.data
 .space 8   #place pour les symboles
 #place pour les lables de chaine de charactere
la1 : .asciiz "8"
la2 : .asciiz "3"
la3 : .asciiz "dqsf"
la4 : .asciiz "6"
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
j a25
a1:
la $s0,la1
la $s1,la2
move $a0,$s0
move $a1,$s1
move $t9,$ra
jal strcompare
move $ra,$t9
bne $t0,$0,a3
a1:
la $s0,la3
sw $s0,0x10010000
a2:
li $s0,3
move $23,$s0
a3:
move $s0,$23
sw $s0,20($sp)
a4:
li $s0,1
move $23,$s0
a5:
move $s0,$23
sw $s0,24($sp)
a6:
li $s0,5
move $23,$s0
a7:
lw $s0,24($sp)
move $s1,$23
mult $s0,$s1
mflo $s0
move $23,$s0
a8:
move $s0,$23
sw $s0,24($sp)
a9:
li $s0,6
move $23,$s0
a10:
move $s0,$23
sw $s0,28($sp)
a11:
li $s0,7
move $23,$s0
a12:
lw $s0,28($sp)
move $s1,$23
div $s0,$s1
mflo $s0
move $23,$s0
a13:
move $s0,$23
sw $s0,28($sp)
a14:
move $s0,$31
move $25,$s0
a15:
lw $s0,0x10010000
move $4,$s0
a16:
jal strtoint
a17:
move $s0,$25
move $31,$s0
a18:
move $s0,$9
move $23,$s0
a19:
lw $s0,28($sp)
move $s1,$23
add $s0,$s0,$s1
move $23,$s0
a20:
lw $s0,24($sp)
move $s1,$23
add $s0,$s0,$s1
move $23,$s0
a21:
lw $s0,20($sp)
move $s1,$23
add $s0,$s0,$s1
move $23,$s0
a22:
lw $s0,0x10010000
sw $s0,0x10010004
a23:
li $s0,0
move $2,$s0
a24:
move $s0,$31
jr $s0
a25:
move $s0,$2
sw $s0,0x10010004
a26:
move $s0,$29
sw $s0,0($sp)
a27:
move $s0,$31
sw $s0,4($sp)
a28:
move $s0,$29
li $s1,8
add $s0,$s0,$s1
move $29,$s0
a29:
la $s0,la2
sw $s0,0($sp)
a30:
la $s0,la3
sw $s0,4($sp)
a31:
la $s0,la4
sw $s0,8($sp)
a32:
li $s0,0
sw $s0,12($sp)
a33:
li $s0,0
sw $s0,16($sp)
a34:
jal a1
a35:
lw $s0,-4($sp)
move $31,$s0
a36:
lw $s0,-8($sp)
move $29,$s0
a37:
move $s0,$2
sw $s0,0x10010004
a38:
li $s0,0
move $2,$s0
a39:
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

strcompare:
li $t0,0

strcompareboucle:
lb $t1,0($a0)
lb $t2,0($a1)
bne $t1,$t2,notequal
beq $t1,$zero,equal
addi $a0,$a0,1
addi $a1,$a1,1
j strcompareboucle

notequal:
addi $t0,$t0,1
j strcomparefin

equal:
addi $t0,$t0,0
j strcomparefin

strcomparefin:
jr $ra

strconcat:
jal strlen
jal strlen2
add $t0,$t0,$t3
move $a0,$t0
li $v0,9
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
la $a0,errorstrtoint
li $v0,4
li $v0,10
syscall          #la fonction échoue, on veut convertir des strings non compatibles

strtointfin:
mult $t2,$t1
mflo $t1
li $t0,0
li $t3,0
li $t4,0
jr $ra       #la fonction a bien terminé

intostr:
jal strlen
move $a0,$t0
li $v0,9
syscall
bnez $a1,loopnonzero     #cas spécifique du zero
li $t1,48
sb $t1,0($v0)
sb $zero,1($v0)
jr $ra

loopnonzero:
move $t1,$a1
beq $t1,$zero,intostrfin
blt $t1,$zero,intostrnegatif
li $t2,10
div $t1,$t2
mfhi $t3
mflo $t1
addi $t3,$t3,48
sb $t3,0($v0)
addi $v0,$v0,1
j loopnonzero

intostrnegatif:        #if the number is <0
li $t2,45
sb $t2,0($v0)
addi $v0,$v0,1
j loopnonzero

intostrfin:
li $t1,0
sb $t1,0($v0)
jr $ra
