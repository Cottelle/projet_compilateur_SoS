#include "SoS2MIPS.h"

void MIPSstrtoint(FILE *f)
{
    //write a string to int converter in MIPS
    fprintf(f,"\nstrtoint:\n");

    //on se place au dernier caractere
    fprintf(f,"\ninitboucle:\n");
    fprintf(f,"lb $t1,0($a0)\n");//on charge le caractere dans $t1
    fprintf(f,"beq $t1,$zero,initfin\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"addi $a0,$a0,1\n");//on incremente l'adresse de la chaine de caractere
    fprintf(f,"j initboucle\n");//on recommence

    fprintf(f,"\ninitfin:\n");//on a fini de se placer au dernier caractere
    fprintf(f,"addi $a0,$a0,-1\n");//on decremente l'adresse de la chaine de caractere
    fprintf(f,"move $t4,$a0\n");//on sauvegarde l'adresse du dernier caractere dans $t2

    //initialisation des variables
    fprintf(f,"\nli $t0,1\n");//on initialise le compteur de puissance a 1
    fprintf(f,"li $t1,0\n");//on initialise le resultat a 0
    fprintf(f,"li $t2,1\n");//on initialise le signe a 1

    fprintf(f,"\nstrtointboucle:\n");
    fprintf(f,"lb $t3,0($t4)\n");//on charge le caractere dans $t3

    //test du caractere
    fprintf(f,"beq $t3,$zero,strtointfin\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"beq $t3,45,strtointnegatif\n");//si le caractere est - on met le signe a -1
    fprintf(f,"beq $t3,43,strtointpositif\n");//si le caractere est + on met le signe a 1
    fprintf(f,"blt $t3,48,error\n");//si le caractere est inferieur a 0 on affiche une erreur
    fprintf(f,"bgt $t3,57,error\n");//si le caractere est superieur a 9 on affiche une erreur

    //calcul du resultat
    fprintf(f,"addi $t3,$t3,-48\n");//on soustrait 48 au caractere pour avoir la valeur numerique
    fprintf(f,"mult $t3,$t0\n");//on multiplie le caractere par la puissance
    fprintf(f,"mflo $t3\n");//on met le resultat dans $t3
    fprintf(f,"add $t1,$t1,$t3\n");//on ajoute le resultat a la valeur
    fprintf(f,"addi $s0,$0,10\n");//on met 10 dans $s0
    fprintf(f,"mult $t0,$s0\n");//on multiplie la puissance par 10
    fprintf(f,"mflo $t0\n");//on met le resultat dans $t0
    fprintf(f,"addi $t4,$t4,-1\n");//on decremente l'adresse de la chaine de caractere
    fprintf(f,"j strtointboucle\n");//on recommence

    fprintf(f,"\nstrtointnegatif:\n");
    fprintf(f,"addi $t2,$t2,-1\n");//on met le signe a -1
    fprintf(f,"j strtointfin\n");//on va à la fin

    fprintf(f,"\nstrtointpositif:\n");
    fprintf(f,"addi $t2,$t2,1\n");//on met le signe a 1
    fprintf(f,"j strtointfin\n");//on va à la fin

    fprintf(f,"\nerror:\n");
    fprintf(f,"li $t1,0\n");//si erreur on met retourne 0
    fprintf(f,"la $a0,errorstrtoint\n");
    fprintf(f,"li $v0,4\n");
    fprintf(f,"li $v0,10\n");
    fprintf(f,"syscall          #la fonction échoue, on veut convertir des strings non compatibles\n");

    fprintf(f,"\nstrtointfin:\n");//on a fini de compter
    fprintf(f,"mult $t2,$t1\n");//on multiplie le signe par le compteur de puissance
    fprintf(f,"mflo $t1\n");//on met le resultat dans $t1
    fprintf(f,"li $t0,0\n");//on initialise le compteur a 0
    fprintf(f,"li $t3,0\n");//on initialise le caractere a 0
    fprintf(f,"li $t4,0\n");//on initialise le nombre a 0
    //fprintf(f,"move $v0,$t1\n");//on met le resultat dans $v0
    fprintf(f,"jr $ra       #la fonction a bien terminé\n");//on retourne au programme
}

void MIPSstrlen(FILE *f)
{
    fprintf(f,"\nstrlen:\n");

    fprintf(f,"li $t0,0\n");// compteur de caractere

    fprintf(f,"\nstrlenboucle:\n");
    fprintf(f,"lb $t1,0($a1)\n");//on charge le caractere dans $t1
    fprintf(f,"beq $t1,$zero,strlenfin\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"addi $a1,$a1,1\n");//on incremente l'adresse de la chaine de caractere
    fprintf(f,"addi $t0,$t0,1\n");//on incremente le compteur de caractere
    fprintf(f,"j strlenboucle\n");//on recommence

    fprintf(f,"\nstrlenfin:\n");//on a fini de compter
    fprintf(f,"jr $ra\n");//on retourne
}

void MIPSstrlen2(FILE *f)
{
    fprintf(f,"\nstrlen2:\n");

    fprintf(f,"li $t3,0\n");// compteur de caractere

    fprintf(f,"\nstrlen2boucle:\n");
    fprintf(f,"lb $t1,0($a2)\n");//on charge le caractere dans $t1
    fprintf(f,"beq $t1,$zero,strlen2fin\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"addi $a2,$a2,1\n");//on incremente l'adresse de la chaine de caractere
    fprintf(f,"addi $t3,$t3,1\n");//on incremente le compteur de caractere
    fprintf(f,"j strlen2boucle\n");//on recommence

    fprintf(f,"\nstrlen2fin:\n");//on a fini de compter
    fprintf(f,"jr $ra\n");//on retourne
}

void MIPSstrcompare(FILE *f)
{
    fprintf(f,"\nstrcompare:\n");

    fprintf(f,"li $t0,0\n");//renvoie 0 si les 2 chaines sont egales

    fprintf(f,"\nstrcompareboucle:\n");
    fprintf(f,"lb $t1,0($a0)\n");//on charge le 1er caractere dans $t1
    fprintf(f,"lb $t2,0($a1)\n");//on charge le 2eme caractere dans $t2
    fprintf(f,"bne $t1,$t2,notequal\n");//si les 2 caracteres sont differents on sort de la boucle
    fprintf(f,"beq $t1,$zero,equal\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"addi $a0,$a0,1\n");//on incremente l'adresse de la 1ere chaine de caractere
    fprintf(f,"addi $a1,$a1,1\n");//on incremente l'adresse de la 2eme chaine de caractere
    fprintf(f,"j strcompareboucle\n");//on recommence

    fprintf(f,"\nnotequal:\n");
    fprintf(f,"addi $t0,$t0,1\n");//on met 1 dans $t0 pour dire que les 2 chaines sont differentes
    fprintf(f,"j strcomparefin\n");//on sort de la boucle

    fprintf(f,"\nequal:\n");
    fprintf(f,"addi $t0,$t0,0\n");//on met 0 dans $t0 pour dire que les 2 chaines sont egales
    fprintf(f,"j strcomparefin\n");//on sort de la boucle


    fprintf(f,"\nstrcomparefin:\n");//on a fini de comparer
    fprintf(f,"jr $ra\n");//on retourne
}

void MIPSstrconcat(FILE *f)
{
    fprintf(f,"\nstrconcat:\n");
    fprintf(f,"jal strlen\n");//on calcule la taille de la 1ere chaine de caractere dans $t0
    fprintf(f,"jal strlen2\n");//on calcule la taille de la 2eme chaine de caractere dans $t3
    fprintf(f,"add $t0,$t0,$t3\n");//on additionne les 2 tailles
    
    fprintf(f,"move $a0,$t0\n");//on met la taille dans $a0
    fprintf(f,"li $v0,9\n");//on met 9 dans $v0 pour allouer de la memoire
    fprintf(f,"syscall\n");//on alloue de la memoire pour la chaine de caractere concatenee
    fprintf(f,"move $t8,$v0\n");//on met l'adresse de la chaine de caractere concatenee dans $t8

    fprintf(f,"\nstrconcatboucle:\n");
    fprintf(f,"lb $t1,0($a1)\n");//on charge le caractere dans $t1
    fprintf(f,"beq $t1,$zero,boucledeuxiemechaine\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"sb $t1,0($v0)\n");//on ecrit le caractere dans la chaine de caractere concatenee
    fprintf(f,"addi $a1,$a1,1\n");//on incremente l'adresse de la 1ere chaine de caractere
    fprintf(f,"addi $v0,$v0,1\n");//on incremente l'adresse de la chaine de caractere concatene
    fprintf(f,"j strconcatboucle\n");//on recommence

    fprintf(f,"\nboucledeuxiemechaine:\n");
    fprintf(f,"lb $t1,0($a2)\n");//on charge le caractere dans $t1
    fprintf(f,"beq $t1,$zero,strconcatfin\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"sb $t1,0($v0)\n");//on ecrit le caractere dans la chaine de caractere concatenee
    fprintf(f,"addi $a2,$a2,1\n");//on incremente l'adresse de la 2eme chaine de caractere
    fprintf(f,"addi $v0,$v0,1\n");//on incremente l'adresse de la chaine de caractere concatene
    fprintf(f,"j boucledeuxiemechaine\n");//on recommence


    fprintf(f,"\nstrconcatfin:\n");
    fprintf(f,"li $t1,0\n");//on met 0 dans $t1 pour dire que le caractere est nul
    fprintf(f,"sb $t1,0($v0)\n");//on ecrit le caractere nul dans la chaine de caractere concatenee
    fprintf(f,"jr $ra\n");//on retourne
}

void MIPSintostr(FILE *f)
{
    fprintf(f,"\nintostr:\n");
    fprintf(f,"li $a0,11\n");//on met la taille dans $a0
    fprintf(f,"li $v0,9\n");//on met 9 dans $v0 pour allouer de la memoire
    fprintf(f,"syscall\n");//on alloue de la memoire pour la chaine de caractere concatenee
    fprintf(f,"move $t8,$v0\n");//on met l'adresse de la chaine de caractere concatenee dans $t8

    fprintf(f,"bnez $a1,intostrloop     #cas spécifique du zero\n");//si la valeur est nulle on sort de la boucle
    fprintf(f,"li $t1,48\n");//on met le caractere '0' dans $t1
    fprintf(f,"sb $t1,0($v0)\n");//on ecrit le caractere '0' dans la chaine de caractere concatenee
    fprintf(f,"sb $zero,1($v0)\n");//on ecrit le caractere nul dans la chaine de caractere concatenee
    fprintf(f,"jr $ra\n");//on retourne

    //cas spécifiques
    fprintf(f,"\nintostrloop:\n");
    fprintf(f,"move $t1,$a1\n");//on charge la valeur dans $t1
    fprintf(f,"blt $t1,$zero,intostrnegatif\n");//si la valeur est negative on va dans la boucle negative

    fprintf(f,"\nloopnonzero:\n");
    fprintf(f,"beq $t1,$zero,intostrfin\n");//si la valeur est nulle on sort de la boucle

    //calcul de l'entier à écrire
    fprintf(f,"li $t2,10\n");//on met 10 dans $t2
    fprintf(f,"div $t1,$t2\n");//on divise la valeur par 10
    fprintf(f,"mfhi $t3\n");//on met le reste dans $t3
    fprintf(f,"mflo $t1\n");//on met le quotient dans $t1
    
    //écriture dans le buffer
    fprintf(f,"addi $t3,$t3,48\n");//on ajoute 48 au reste pour avoir le caractere correspondant
    fprintf(f,"sb $t3,0($v0)\n");//on ecrit le caractere dans la chaine de caractere concatenee
    fprintf(f,"addi $v0,$v0,1\n");//on incremente l'adresse de la chaine de caractere concatene
    fprintf(f,"j loopnonzero\n");//on recommence

    //cas négatif
    fprintf(f,"\nintostrnegatif:        #if the number is <0\n");
    fprintf(f,"li $t2,45\n");//on met le caractere '-' dans $t2
    fprintf(f,"sb $t2,0($v0)\n");//on ecrit le caractere '-' dans la chaine de caractere concatenee
    fprintf(f,"addi $v0,$v0,1\n");//on incremente l'adresse de la chaine de caractere concatene
    fprintf(f,"j loopnonzero\n");//on recommence

    //fin
    fprintf(f,"\nintostrfin:\n");
    fprintf(f,"li $t1,0\n");//on met 0 dans $t1 pour dire que le caractere est nul
    fprintf(f,"sb $t1,0($v0)\n");//on ecrit le caractere nul dans la chaine de caractere concatenee
    fprintf(f,"jr $ra\n");//on retourne
}

void MIPSread(FILE *f)
{
    fprintf(f,"\n_read:\n");
    fprintf(f,"li $v0,8\n");
    fprintf(f,"li $a1,31\n");
    fprintf(f,"la $a0, la0\n");
    fprintf(f,"syscall\n"); 


    fprintf(f,"li $t0,0\n");
    fprintf(f,"la $9,la0\n");

    fprintf(f,"\nloop: 			#taille du buffer lu \n");
    fprintf(f,"lb $t2 , ($9)\n");
    fprintf(f,"beq $t2, $0 , exit\n");
    fprintf(f,"addi $t0, $t0, 1\n");
    fprintf(f,"addi $9 , $t1, 1\n");
    fprintf(f,"j loop\n");
    
    fprintf(f,"\nexit : \n");
    fprintf(f,"li $v0, 9\n");
    fprintf(f,"move $a0 , $t0			#alloue\n");
    fprintf(f,"syscall\n");

    fprintf(f,"la $9,la0\n");
    fprintf(f,"move $11, $v0\n");

    fprintf(f,"\nloop2 :\n");
    fprintf(f,"beq $t0,$0 , exit2\n");
    fprintf(f,"lb $t2, ($9)\n");
    fprintf(f,"sb $t2, ($v0)\n");
    fprintf(f,"addi $9,$9,1\n");
    fprintf(f,"addi $v0,$v0,1\n");
    fprintf(f,"addi $t0,$t0,-1\n");
    fprintf(f,"j loop2\n");

    fprintf(f,"\nexit2 :\n");

    fprintf(f,"jr $31					#resulat ds $11\n");
    fprintf(f,"#the value allocated is in $11\n");
}


//reserver la memoire pour les symboles et pour les labels 
void labelprint(struct labels l, int size_symb,FILE *f)
{
    fprintf(f, ".data\n .space %i   #place pour les symboles\n #place pour les lables de chaine de charactere\n", size_symb*4);
    fprintf(f,"errorstrtoint : .asiicz \"Ce n'est pas un nombre desolé\" \n");
    for (int i = 1; i < l.cur_place; i++)
        fprintf(f, "la%i : .asciiz \"%s\"\n", i, l.tab[i]);

    fprintf(f, "la0: .space 32         #the buffer for the read buffer of siez 32\n  \n\n .text\n");
}


void il2MIPS(struct quad quad, struct tabsymbole tabsymbole, struct labels labels)
{
    FILE *f=fopen("codeMIPS.s","w");
    if(f==NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    //reservation of memory (.data)
    int size_symb = 0;

    for (int i = 0; i < tabsymbole.size; i++)

        if (tabsymbole.tab[i])

            size_symb += tabsymbole.tab[i]->nb;

    labelprint(labels, size_symb,f);


    int i=0;
    for(i=0;i<quad.next;i++)
    {
        fprintf(f,"a%i:\n",i);

        switch(quad.quadrup[i].instruction)
        {
            case GOTO:
                if(quad.quadrup[i].type==1)
                {
                    if(quad.quadrup[i].zero.s==NULL)
                    {
                        fprintf(f,"jal a%i\n",quad.quadrup[i].zero.value);
                    }
                    else
                    {
                        switch(quad.quadrup[i].zero.s->onstack_reg_label)
                        {
                            case 0:
                                fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+TEXT_SEGMENT);
                                break;
                            case 1:
                                fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                break;
                            case 2:
                                fprintf(f,"move $s0,$%i\n",quad.quadrup[i].zero.s->isint);
                                break;
                            case 3:
                                fprintf(f,"la $s0,la%i\n",quad.quadrup[i].zero.s->memory_place);
                            default:
                                printf("Error: variable not found");
                                exit(1);
                        }

                        //jalr $s0
                        fprintf(f,"jalr $s0\n");
                    }
                }
                else
                {
                    if(quad.quadrup[i].zero.s==NULL)
                    {
                        fprintf(f,"j a%i\n",quad.quadrup[i].zero.value);
                    }
                    else
                    {
                        switch(quad.quadrup[i].zero.s->onstack_reg_label)
                        {
                            case 0:

                                fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                break;
                            case 1:
                                fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                break;
                            case 2:
                                fprintf(f,"move $s0,$%i\n",quad.quadrup[i].zero.s->isint);
                                break;
                            case 3:
                                fprintf(f,"la $s0,la%i\n",quad.quadrup[i].zero.s->memory_place);
                            default:
                                printf("Error: variable not found");
                                exit(1);
                        }

                        //jr $s0
                        fprintf(f,"jr $s0\n");
                    }
                }
                break;
            case AFF:
                if(quad.quadrup[i].zero.s==NULL)
                {
                    printf("Error: variable not found \n");
                    exit(1);
                }
                switch(quad.quadrup[i].type)
                {
                    case -2://affectation indirecte de type lw a,$i
                        fprintf(f,"move $s0,$%i\n",quad.quadrup[i].zero.s->isint);          //zero forcement un registre
                        if(!quad.quadrup[i].one.s)
                                fprintf(f,"lw $s1,0x%x\n",quad.quadrup[i].one.value+DATA_SEGMENT);

                        else
                        {
                            switch(quad.quadrup[i].one.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s1,0x%x\n",quad.quadrup[i].one.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s1,%i($sp)\n",quad.quadrup[i].one.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s1,$%i\n",quad.quadrup[i].one.s->isint);
                                    break;
                                case 3:
                                    fprintf(f,"la $s1,la%i\n",quad.quadrup[i].one.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found \n");
                                    exit(1);
                            }
                        }
                        fprintf(f,"sw $s1,($s0)\n");
                        break;
                    case -1://affectation indirecte de type sw $i,a
                        fprintf(f,"lw,$s0,($%i)\n",quad.quadrup[i].one.s->isint);
                        switch(quad.quadrup[i].zero.s->onstack_reg_label)
                        {
                            case 0:
                                fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                break;
                            case 1:
                                fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                break;
                            case 2:
                                fprintf(f,"move $%i,$0\n",quad.quadrup[i].zero.s->isint);
                                break;
                            default:
                                printf("Error: variable not found");
                                exit(1);
                        }
                        break;
                    case 0://affectation simple
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                            switch(quad.quadrup[i].zero.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }
                        else
                        {
                            switch(quad.quadrup[i].one.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].one.s->memory_place+DATA_SEGMENT);
                                    switch(quad.quadrup[i].zero.s->onstack_reg_label)
                                    {
                                        case 0:
                                            fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                            break;
                                        case 1:
                                            fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                            break;
                                        case 2:
                                            fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                            break;

                                        default:
                                            printf("Error: variable not found");
                                            exit(1);
                                    }
                                    break;
                                case 1:
                                    fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].one.s->memory_place);
                                    switch(quad.quadrup[i].zero.s->onstack_reg_label)
                                    {
                                        case 0:
                                            fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                            break;
                                        case 1:
                                            fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                            break;
                                        case 2:
                                            fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                            break;

                                        default:
                                            printf("Error: variable not found");
                                            exit(1);
                                    }
                                    break;
                                case 2:
                                    fprintf(f,"move $s0,$%i\n",quad.quadrup[i].one.s->isint);
                                    switch(quad.quadrup[i].zero.s->onstack_reg_label)
                                    {
                                        case 0:
                                            fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                            break;
                                        case 1:
                                            fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                            break;
                                        case 2:
                                            fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                            break;
                                        default:
                                            printf("Error: variable not found");
                                            exit(1);
                                    }
                                    break;
                                case 3:
                                    fprintf(f,"la $s0,la%i\n",quad.quadrup[i].one.s->memory_place);
                                    switch(quad.quadrup[i].zero.s->onstack_reg_label)
                                    {
                                        case 0:
                                            fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                            break;
                                        case 1:
                                            fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                            break;
                                        case 2:
                                            fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                            break;
                                        default:
                                            printf("Error: variable not found");
                                            exit(1);
                                    }
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }
                        break;


                    case 1://addition
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                        }
                        else
                        {
                            switch(quad.quadrup[i].one.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].one.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].one.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s0,$%i\n",quad.quadrup[i].one.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }
                        if(quad.quadrup[i].two.s==NULL)
                        {
                            fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                        }
                        else
                        {
                            switch(quad.quadrup[i].two.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s1,0x%x\n",quad.quadrup[i].two.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s1,%i($sp)\n",quad.quadrup[i].two.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s1,$%i\n",quad.quadrup[i].two.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }
                        fprintf(f,"add $s0,$s0,$s1\n");
                        switch(quad.quadrup[i].zero.s->onstack_reg_label)
                        {
                            case 0:
                                fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                break;
                            case 1:
                                fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                break;
                            case 2:
                                fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                break;
                            default:
                                printf("Error: variable not found");
                                exit(1);
                        }
                        break;


                    case 2://soustraction
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                        }
                        else
                        {
                            switch(quad.quadrup[i].one.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].one.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].one.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s0,$%i\n",quad.quadrup[i].one.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }
                        if(quad.quadrup[i].two.s==NULL)
                        {
                            fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                        }
                        else
                        {
                            switch(quad.quadrup[i].two.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s1,0x%x\n",quad.quadrup[i].two.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s1,%i($sp)\n",quad.quadrup[i].two.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s1,$%i\n",quad.quadrup[i].two.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }

                        fprintf(f,"sub $s0,$s0,$s1\n");
                        switch(quad.quadrup[i].zero.s->onstack_reg_label)
                        {
                            case 0:
                                fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                break;
                            case 1:
                                fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                break;
                            case 2:
                                fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                break;
                            default:
                                printf("Error: variable not found");
                                exit(1);
                        }
                        break;
                    case 3://multiplication
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                        }
                        else
                        {
                            switch(quad.quadrup[i].one.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].one.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].one.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s0,$%i\n",quad.quadrup[i].one.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }
                        if(quad.quadrup[i].two.s==NULL)
                        {
                            fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                        }
                        else
                        {
                            switch(quad.quadrup[i].two.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s1,0x%x\n",quad.quadrup[i].two.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s1,%i($sp)\n",quad.quadrup[i].two.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s1,$%i\n",quad.quadrup[i].two.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }

                        fprintf(f,"mult $s0,$s1\n");
                        fprintf(f,"mflo $s0\n");

                        switch(quad.quadrup[i].zero.s->onstack_reg_label)
                        {
                            case 0:
                                fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                break;
                            case 1:
                                fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                break;
                            case 2:
                                fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                break;
                            default:
                                printf("Error: variable not found");
                                exit(1);
                        }
                        break;
                    case 4://division
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                        }
                        else
                        {
                            switch(quad.quadrup[i].one.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].one.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].one.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s0,$%i\n",quad.quadrup[i].one.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }
                        if(quad.quadrup[i].two.s==NULL)
                        {
                            fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                        }
                        else
                        {
                            switch(quad.quadrup[i].two.s->onstack_reg_label)
                            {
                                case 0:
                                    fprintf(f,"lw $s1,0x%x\n",quad.quadrup[i].two.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s1,%i($sp)\n",quad.quadrup[i].two.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s1,$%i\n",quad.quadrup[i].two.s->isint);
                                    break;
                                default:
                                    printf("Error: variable not found");
                                    exit(1);
                            }
                        }

                        fprintf(f,"div $s0,$s1\n");
                        fprintf(f,"mflo $s0\n");
                        
                        switch(quad.quadrup[i].zero.s->onstack_reg_label)
                        {
                            case 0:
                                fprintf(f,"sw $s0,0x%x\n",quad.quadrup[i].zero.s->memory_place+DATA_SEGMENT);
                                break;
                            case 1:
                                fprintf(f,"sw $s0,%i($sp)\n",quad.quadrup[i].zero.s->memory_place);
                                break;
                            case 2:
                                fprintf(f,"move $%i,$s0\n",quad.quadrup[i].zero.s->isint);
                                break;
                            default:
                                printf("Error: variable not found");
                                exit(1);
                        }
                        break;
                }//fin switch type
                break;
            case IF:
                if(quad.quadrup[i].one.s != NULL )
                {
                    switch(quad.quadrup[i].one.s->onstack_reg_label)
                    {
                        case 0:
                            fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].one.s->memory_place+DATA_SEGMENT);
                            break;
                        case 1:
                            fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].one.s->memory_place);
                            break;
                        case 2:
                            fprintf(f,"move $s0,$%i\n",quad.quadrup[i].one.s->isint);
                            break;
                        case 3:
                            fprintf(f,"la $s0,la%i\n",quad.quadrup[i].one.s->memory_place);
                            break;
                        default:
                            printf("Error: variable not found");
                            exit(1);
                    }
                }
                else
                {
                    fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                }
                if(quad.quadrup[i].two.s != NULL )
                {
                    switch(quad.quadrup[i].two.s->onstack_reg_label)
                    {
                        case 0:
                            fprintf(f,"lw $s1,0x%x\n",quad.quadrup[i].two.s->memory_place+DATA_SEGMENT);
                            break;
                        case 1:
                            fprintf(f,"lw $s1,%i($sp)\n",quad.quadrup[i].two.s->memory_place);
                            break;
                        case 2:
                            fprintf(f,"move $s1,$%i\n",quad.quadrup[i].two.s->isint);
                            break;
                        case 3:
                            fprintf(f,"la $s1,la%i\n",quad.quadrup[i].two.s->memory_place);
                            break;
                        default:
                            printf("Error: variable not found");
                            exit(1);
                    }
                }
                else
                {
                    fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                }
                if(quad.quadrup[i].type>=0)
                {
                    if(quad.quadrup[i].one.s && quad.quadrup[i].one.s->onstack_reg_label!=2 && quad.quadrup[i].one.s->isint==0 )
                    {
                        fprintf(f,"move $a0,$s0\n");
                        fprintf(f,"move $t9,$ra\n");
                        fprintf(f,"jal strtoint\n");
                        fprintf(f,"move $ra,$t9\n");
                        fprintf(f,"move $s0,$t1\n");
                    }
                    if(quad.quadrup[i].two.s && quad.quadrup[i].two.s->onstack_reg_label!=2 && quad.quadrup[i].two.s->isint==0 )
                    {
                        fprintf(f,"move $a0,$s1\n");
                        fprintf(f,"move $t9,$ra\n");
                        fprintf(f,"jal strtoint\n");
                        fprintf(f,"move $ra,$t9\n");
                        fprintf(f,"move $s1,$t1\n");
                    }
                }
                switch(quad.quadrup[i].type)
                {
                    case 0://=
                        fprintf(f,"beq $s0,$s1,a%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 1://!=
                        fprintf(f,"bne $s0,$s1,a%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 2://<
                        fprintf(f,"blt $s0,$s1,a%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 3://>
                        fprintf(f,"bgt $s0,$s1,a%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 4://<=
                        fprintf(f,"ble $s0,$s1,a%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 5://>=
                        fprintf(f,"bge $s0,$s1,a%i\n",quad.quadrup[i].zero.value);
                        break;
                    case -2://=
                        fprintf(f,"move $a0,$s0\n");
                        fprintf(f,"move $a1,$s1\n");
                        fprintf(f,"move $t9,$ra\n");
                        fprintf(f,"jal strcompare\n");
                        fprintf(f,"move $ra,$t9\n");
                        fprintf(f,"beq $t0,$0,a%i\n",quad.quadrup[i].zero.value);
                        break;
                    case -1://!=
                        fprintf(f,"move $a0,$s0\n");
                        fprintf(f,"move $a1,$s1\n");
                        fprintf(f,"move $t9,$ra\n");
                        fprintf(f,"jal strcompare\n");
                        fprintf(f,"move $ra,$t9\n");
                        fprintf(f,"bne $t0,$0,a%i\n",quad.quadrup[i].zero.value);
                        break;
                }//fin switch type
                break;
            case SYS:
                fprintf(f,"li $v0,%i\n",quad.quadrup[i].zero.value);
                fprintf(f,"syscall\n");
                break;
            case CALL:
                fprintf(f,"jal %s\n",(char *)quad.quadrup[i].zero.s);
                break;
        }//fin switch instruction
    }//fin for quad

    //écriture des fonctions auxiliaires
    MIPSread(f);
    MIPSstrcompare(f);
    MIPSstrconcat(f);
    MIPSstrlen(f);
    MIPSstrlen2(f);
    MIPSstrtoint(f);
    MIPSintostr(f);

}//fin fonction