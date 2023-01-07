.data
 .space 0   #place pour les symboles
 #place pour les lables de chaine de charactere
errorstrtoint : .asciiz "Ce n'est pas un nombre desolé" 
la1 : .asciiz "a"
la2 : .asciiz "c"
la3 : .asciiz "c"
la4 : .asciiz "b"
la5 : .asciiz "b"
la6 : .asciiz "a"
la7 : .asciiz "a"
la8 : .asciiz "Bidon"
la9 : .asciiz "rien"
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
la $s0,la1
la $s1,la2
bne $s0,$s1,a4
a1:
la $s0,la3
move $4,$s0
a2:
li $v0,4
syscall
a3:
j a17
a4:
la $s0,la1
la $s1,la4
bne $s0,$s1,a8
a5:
la $s0,la5
move $4,$s0
a6:
li $v0,4
syscall
a7:
j a17
a8:
la $s0,la1
la $s1,la6
bne $s0,$s1,a12
a9:
la $s0,la7
move $4,$s0
a10:
li $v0,4
syscall
a11:
j a17
a12:
j a14
a13:
la $s0,la1
la $s1,la8
bne $s0,$s1,a17
a14:
la $s0,la9
move $4,$s0
a15:
li $v0,4
syscall
a16:
j a17
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
addi $t0,$t0,1
move $a0,$t0
li $v0,9
syscall
move $v1,$v0

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
lb $t1,0($a1)
beq $t1,$zero,strlenfin
addi $a1,$a1,1
addi $t0,$t0,1
j strlenboucle

strlenfin:
jr $ra

strlen2:
li $t3,0

strlen2boucle:
lb $t1,0($a2)
beq $t1,$zero,strlen2fin
addi $a2,$a2,1
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
li $t5,10
beq $t3,$t5,strtointfin
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
syscall
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
li $a0,11
li $v0,9
syscall
bnez $a1,intostrloop     #cas spécifique du zero
li $t1,48
sb $t1,0($v0)
sb $zero,1($v0)
jr $ra

intostrloop:
move $t1,$a1
blt $t1,$zero,intostrnegatif
li $t2,10

loopendadd:
beq $t2,$zero,finloopendadd
addi $v0,$v0,1
addi $t2,$t2,-1
j loopendadd

finloopendadd:
move $v1,$v0
addi $v1,$v1,1
sb $zero,0($v1)

loopnonzero:
beq $t1,$zero,intostrfin
li $t2,10
div $t1,$t2
mfhi $t3
mflo $t1
addi $t3,$t3,48
sb $t3,0($v0)
subi $v0,$v0,1
j loopnonzero

intostrnegatif:        #if the number is <0
li $t2,45
j loopnonzero

negfin:
sb $t2,0($v0)
jr $ra

intostrfin:
bne $t2,$zero,negfin
addi $v0,$v0,1
jr $ra
