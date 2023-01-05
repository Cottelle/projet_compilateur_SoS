.data
 .space 24   #place pour les symboles
 #place pour les lables de chaine de charactere
la0: .space 32         #the buffer for the read buffer of siez 32
  

 .text
a0:
li $s0,0
move $23,$s0
a1:
li $s0,268500992
move $s1,$23
add $s0,$s0,$s1
move $22,$s0
a2:
move $s0,$31
sw $s0,0($sp)
a3:
jal _read
a4:
move $s0,$22
move $s1,$s11
sw $s1,($s0)
a5:
lw $s0,0($sp)
move $31,$s0
a6:
li $s0,1
move $23,$s0
a7:
li $s0,268500992
move $s1,$23
add $s0,$s0,$s1
move $22,$s0
a8:
move $s0,$31
sw $s0,0($sp)
a9:
jal _read
a10:
move $s0,$22
move $s1,$s11
sw $s1,($s0)
a11:
lw $s0,0($sp)
move $31,$s0
a12:
li $s0,2
move $23,$s0
a13:
li $s0,268500992
move $s1,$23
add $s0,$s0,$s1
move $22,$s0
a14:
move $s0,$31
sw $s0,0($sp)
a15:
jal _read
a16:
move $s0,$22
move $s1,$s11
sw $s1,($s0)
a17:
lw $s0,0($sp)
move $31,$s0
a18:
li $s0,3
move $23,$s0
a19:
li $s0,268500992
move $s1,$23
add $s0,$s0,$s1
move $22,$s0
a20:
move $s0,$31
sw $s0,0($sp)
a21:
jal _read
a22:
move $s0,$22
move $s1,$s11
sw $s1,($s0)
a23:
lw $s0,0($sp)
move $31,$s0
a24:
lw $s0,0x10010000
sw $s0,0x10010014
a25:
move $s0,$31
move $22,$s0
a26:
jal a27
a27:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010010
a28:
move $s0,$22
move $31,$s0
a29:
j a49
a30:
lw $s0,0x10010004
sw $s0,0x10010014
a31:
move $s0,$31
move $22,$s0
a32:
jal a33
a33:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010010
a34:
move $s0,$22
move $31,$s0
a35:
j a49
a36:
lw $s0,0x10010008
sw $s0,0x10010014
a37:
move $s0,$31
move $22,$s0
a38:
jal a39
a39:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010010
a40:
move $s0,$22
move $31,$s0
a41:
j a49
a42:
lw $s0,0x1001000c
sw $s0,0x10010014
a43:
move $s0,$31
move $22,$s0
a44:
jal a45
a45:
move $s0,$31
li $s1,32
add $s0,$s0,$s1
sw $s0,0x10010010
a46:
move $s0,$22
move $31,$s0
a47:
j a49
a48:
j a52
a49:
lw $s0,0x10010014
move $4,$s0
a50:
li $v0,4
syscall
a51:
lw $s0,0x10010010
jr $s0
a52:
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
mult $t0,10
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
li $v0,4
la $a0,erreur
syscall
li $v0,10
syscall

strtointfin:
mult $t2,$t1
mflo $t1
li $t0,0
li $t3,0
li $t4,0
jr $ra
