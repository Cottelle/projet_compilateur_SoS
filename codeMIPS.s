.data
 .space 4   #place pour les symboles
 #place pour les lables de chaine de charactere
errorstrtoint : .asciiz "Ce n'est pas un nombre desolé" 
la1 : .asciiz "0"
la2 : .asciiz "0"
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
j a35
a1:
lw $s0,0($sp)
la $s1,la1
move $a0,$s0
move $t9,$ra
jal strtoint
move $ra,$t9
move $s0,$t1
move $a0,$s1
move $t9,$ra
move $s4,$s0
jal strtoint
move $s0,$s4
move $ra,$t9
move $s1,$t1
beq $s0,$s1,a3
a2:
j a8
a3:
la $s0,la2
move $4,$s0
a4:
li $v0,4
syscall
a5:
li $s0,0
move $2,$s0
a6:
move $s0,$31
jr $s0
a7:
j a33
a8:
move $s0,$2
move $24,$s0
a9:
move $s0,$31
move $25,$s0
a10:
lw $s0,0($sp)
move $4,$s0
a11:
jal strtoint
a12:
move $s0,$25
move $31,$s0
a13:
move $s0,$24
move $2,$s0
a14:
move $s0,$9
move $23,$s0
a15:
move $s0,$23
sw $s0,4($sp)
a16:
li $s0,1
move $23,$s0
a17:
lw $s0,4($sp)
move $s1,$23
sub $s0,$s0,$s1
move $23,$s0
a18:
move $s0,$31
move $25,$s0
a19:
move $s0,$2
move $24,$s0
a20:
move $s0,$23
move $5,$s0
a21:
jal intostr
a22:
move $s0,$25
move $31,$s0
a23:
move $s0,$2
sw $s0,0x10010000
a24:
move $s0,$29
sw $s0,4($sp)
a25:
move $s0,$31
sw $s0,8($sp)
a26:
move $s0,$29
li $s1,12
add $s0,$s0,$s1
move $29,$s0
a27:
lw $s0,0x10010000
sw $s0,0($sp)
a28:
jal a1
a29:
lw $s0,-4($sp)
move $31,$s0
a30:
lw $s0,-8($sp)
move $29,$s0
a31:
lw $s0,0($sp)
move $4,$s0
a32:
li $v0,4
syscall
a33:
li $s0,0
move $2,$s0
a34:
move $s0,$31
jr $s0
a35:
move $s0,$31
sw $s0,0($sp)
a36:
jal _read
a37:
move $s0,$11
sw $s0,0x10010000
a38:
lw $s0,0($sp)
move $31,$s0
a39:
move $s0,$29
sw $s0,4($sp)
a40:
move $s0,$31
sw $s0,8($sp)
a41:
move $s0,$29
li $s1,12
add $s0,$s0,$s1
move $29,$s0
a42:
lw $s0,0x10010000
sw $s0,0($sp)
a43:
jal a1
a44:
lw $s0,-4($sp)
move $31,$s0
a45:
lw $s0,-8($sp)
move $29,$s0
a46:
li $s0,0
move $2,$s0
a47:
li $v0,10
syscall

_read:
li $v0,8
li $a1,31
la $a0, la0
syscall
li $t0,0
la $9,la0
li $t3,10

_readloop: 			#taille du buffer lu 
lb $t2 , ($9)
beq $t2, $0 , _readexit
beq $t2, $t3 , _readNL
addi $t0, $t0, 1
addi $9 , $t1, 1
j _readloop
_readNL:
sb $0,($9)
_readexit : 
li $v0, 9
move $a0 , $t0			#alloue
syscall
la $9,la0
move $11, $v0

_readloop2 :
beq $t0,$0 , _readexit2
lb $t2, ($9)
sb $t2, ($v0)
addi $9,$9,1
addi $v0,$v0,1
addi $t0,$t0,-1
j _readloop2

 _readexit2 :
jr $31					#resulat ds $11
#the value allocated is in $11

strcompare:
li $t0,0
li $t3,10

strcompareboucle:
lb $t1,0($a0)
lb $t2,0($a1)
bne $t1,$t2,notequal
beq $t1,$zero,equal
beq $t1,$t3,equal
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
move $t7,$ra
jal strlen
jal strlen2
move $ra,$t7
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
move $t4,$a1

strlenboucle:
lb $t1,0($a1)
beq $t1,$zero,strlenfin
addi $a1,$a1,1
addi $t0,$t0,1
j strlenboucle

strlenfin:
move $a1,$t4
jr $ra

strlen2:
li $t3,0
move $t4,$a2

strlen2boucle:
lb $t1,0($a2)
beq $t1,$zero,strlen2fin
addi $a2,$a2,1
addi $t3,$t3,1
j strlen2boucle

strlen2fin:
move $a2,$t4
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
