.data
 .space 44   #place pour les symboles
 #place pour les lables de chaine de charactere
errorstrtoint : .asciiz "Ce n'est pas un nombre desolé" 
la1 : .asciiz "0"
la2 : .asciiz "0"
la3 : .asciiz "0"
la4 : .asciiz "0"
la5 : .asciiz "10"
la6 : .asciiz "0"
la7 : .asciiz "10"
la8 : .asciiz "0"
la9 : .asciiz "1"
la10 : .asciiz "1"
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
j a16
a1:
la $s0,la1
sw $s0,0($sp)
a2:
lw $s0,0($sp)
la $s1,la2
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
bne $s0,$s1,a4
a3:
j a14
a4:
move $s0,$2
move $24,$s0
a5:
move $s0,$31
move $25,$s0
a6:
lw $s0,0($sp)
move $4,$s0
a7:
jal strtoint
a8:
move $s0,$25
move $31,$s0
a9:
move $s0,$24
move $2,$s0
a10:
move $s0,$9
li $s1,4
mult $s0,$s1
mflo $s0
move $23,$s0
a11:
li $s0,268500992
move $s1,$23
add $s0,$s0,$s1
move $20,$s0
a12:
move $s0,$20
la $s1,la3
sw $s1,($s0)
a13:
j a2
a14:
li $s0,0
move $2,$s0
a15:
move $s0,$31
jr $s0
a16:
j a55
a17:
la $s0,la4
sw $s0,4($sp)
a18:
lw $s0,4($sp)
la $s1,la5
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
bne $s0,$s1,a20
a19:
j a53
a20:
move $s0,$2
move $24,$s0
a21:
move $s0,$31
move $25,$s0
a22:
lw $s0,4($sp)
move $4,$s0
a23:
jal strtoint
a24:
move $s0,$25
move $31,$s0
a25:
move $s0,$24
move $2,$s0
a26:
move $s0,$9
li $s1,4
mult $s0,$s1
mflo $s0
move $23,$s0
a27:
li $s0,268500992
move $s1,$23
add $s0,$s0,$s1
move $20,$s0
a28:
lw,$s0,($20)
sw $s0,0x10010028
a29:
lw $s0,0x10010028
lw $s1,0($sp)
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
beq $s0,$s1,a31
a30:
j a34
a31:
li $s0,1
move $2,$s0
a32:
move $s0,$31
jr $s0
a33:
j a18
a34:
move $s0,$2
move $24,$s0
a35:
move $s0,$31
move $25,$s0
a36:
lw $s0,4($sp)
move $4,$s0
a37:
jal strtoint
a38:
move $s0,$25
move $31,$s0
a39:
move $s0,$24
move $2,$s0
a40:
move $s0,$9
move $23,$s0
a41:
move $s0,$23
sw $s0,8($sp)
a42:
li $s0,1
move $23,$s0
a43:
lw $s0,8($sp)
move $s1,$23
add $s0,$s0,$s1
move $23,$s0
a44:
move $s0,$31
move $25,$s0
a45:
move $s0,$2
move $24,$s0
a46:
move $s0,$23
move $5,$s0
a47:
jal intostr
a48:
move $s0,$25
move $31,$s0
a49:
move $s0,$2
sw $s0,4($sp)
a50:
j a18
a51:
li $s0,0
move $2,$s0
a52:
move $s0,$31
jr $s0
a53:
li $s0,0
move $2,$s0
a54:
move $s0,$31
jr $s0
a55:
j a101
a56:
la $s0,la6
sw $s0,4($sp)
a57:
lw $s0,4($sp)
la $s1,la7
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
bne $s0,$s1,a59
a58:
j a99
a59:
move $s0,$2
move $24,$s0
a60:
move $s0,$31
move $25,$s0
a61:
lw $s0,4($sp)
move $4,$s0
a62:
jal strtoint
a63:
move $s0,$25
move $31,$s0
a64:
move $s0,$24
move $2,$s0
a65:
move $s0,$9
li $s1,4
mult $s0,$s1
mflo $s0
move $23,$s0
a66:
li $s0,268500992
move $s1,$23
add $s0,$s0,$s1
move $20,$s0
a67:
lw,$s0,($20)
sw $s0,0x10010028
a68:
lw $s0,0x10010028
la $s1,la8
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
beq $s0,$s1,a70
a69:
j a82
a70:
move $s0,$2
move $24,$s0
a71:
move $s0,$31
move $25,$s0
a72:
lw $s0,4($sp)
move $4,$s0
a73:
jal strtoint
a74:
move $s0,$25
move $31,$s0
a75:
move $s0,$24
move $2,$s0
a76:
move $s0,$9
li $s1,4
mult $s0,$s1
mflo $s0
move $23,$s0
a77:
li $s0,268500992
move $s1,$23
add $s0,$s0,$s1
move $20,$s0
a78:
move $s0,$20
lw $s1,0($sp)
sw $s1,($s0)
a79:
li $s0,0
move $2,$s0
a80:
move $s0,$31
jr $s0
a81:
j a57
a82:
move $s0,$2
move $24,$s0
a83:
move $s0,$31
move $25,$s0
a84:
lw $s0,4($sp)
move $4,$s0
a85:
jal strtoint
a86:
move $s0,$25
move $31,$s0
a87:
move $s0,$24
move $2,$s0
a88:
move $s0,$9
move $23,$s0
a89:
move $s0,$23
sw $s0,8($sp)
a90:
li $s0,1
move $23,$s0
a91:
lw $s0,8($sp)
move $s1,$23
add $s0,$s0,$s1
move $23,$s0
a92:
move $s0,$31
move $25,$s0
a93:
move $s0,$2
move $24,$s0
a94:
move $s0,$23
move $5,$s0
a95:
jal intostr
a96:
move $s0,$25
move $31,$s0
a97:
move $s0,$2
sw $s0,4($sp)
a98:
j a57
a99:
li $s0,0
move $2,$s0
a100:
move $s0,$31
jr $s0
a101:
move $s0,$29
sw $s0,0($sp)
a102:
move $s0,$31
sw $s0,4($sp)
a103:
move $s0,$29
li $s1,8
add $s0,$s0,$s1
move $29,$s0
a104:
la $s0,la9
sw $s0,0($sp)
a105:
jal a17
a106:
lw $s0,-4($sp)
move $31,$s0
a107:
lw $s0,-8($sp)
move $29,$s0
a108:
move $s0,$2
move $24,$s0
a109:
move $s0,$31
move $25,$s0
a110:
move $s0,$2
move $5,$s0
a111:
jal intostr
a112:
move $s0,$25
move $31,$s0
a113:
move $s0,$2
move $4,$s0
a114:
li $v0,4
syscall
a115:
move $s0,$29
sw $s0,0($sp)
a116:
move $s0,$31
sw $s0,4($sp)
a117:
move $s0,$29
li $s1,8
add $s0,$s0,$s1
move $29,$s0
a118:
la $s0,la10
sw $s0,0($sp)
a119:
jal a56
a120:
lw $s0,-4($sp)
move $31,$s0
a121:
lw $s0,-8($sp)
move $29,$s0
a122:
move $s0,$2
move $24,$s0
a123:
move $s0,$31
move $25,$s0
a124:
move $s0,$2
move $5,$s0
a125:
jal intostr
a126:
move $s0,$25
move $31,$s0
a127:
move $s0,$2
move $4,$s0
a128:
li $v0,4
syscall
a129:
li $s0,0
move $2,$s0
a130:
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
beq $t1,$t3,retour1
beq $t2,$t3,retour2
bne $t1,$t2,notequal
beq $t1,$zero,equal
beq $t1,$t3,equal
addi $a0,$a0,1
addi $a1,$a1,1
j strcompareboucle

retour1:
addi $a0,$a0,1
j strcompareboucle

retour2:
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
