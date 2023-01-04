#include "SoS2MIPS.h"

void MIPSstrlen(FILE *f)
{
    fprintf(f,"strlen:\n");

    fprintf(f,"li $t0,0\n");// compteur de caractere

    fprintf(f,"strlenboucle:\n");
    fprintf(f,"lb $t1,0($a0)\n");//on charge le caractere dans $t1
    fprintf(f,"beq $t1,$zero,strlenfin\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"addi $a0,$a0,1\n");//on incremente l'adresse de la chaine de caractere
    fprintf(f,"addi $t0,$t0,1\n");//on incremente le compteur de caractere
    fprintf(f,"j strlenboucle\n");//on recommence

    fprintf(f,"strlenfin:\n");//on a fini de compter
    fprintf(f,"jr $ra\n");//on retourne
}

void MIPSstrcompare(FILE *f)
{
    fprintf(f,"strcompare:\n");

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
    fprintf(f,"strconcat:\n");

    fprintf(f,"\nstrconcatboucle:\n");
    fprintf(f,"lb $t1,0($a0)\n");//on charge le caractere dans $t1
    fprintf(f,"beq $t1,$zero,boucledeuxiemechaine\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"sb $t1,0($a2)\n");//on ecrit le caractere dans la chaine de caractere concatenee
    fprintf(f,"addi $a0,$a0,1\n");//on incremente l'adresse de la 1ere chaine de caractere
    fprintf(f,"addi $a2,$a2,1\n");//on incremente l'adresse de la chaine de caractere concatene
    fprintf(f,"j strconcatboucle\n");//on recommence

    fprintf(f,"\nboucledeuxiemechaine:\n");
    fprintf(f,"lb $t1,0($a1)\n");//on charge le caractere dans $t1
    fprintf(f,"beq $t1,$zero,strconcatfin\n");//si le caractere est nul on sort de la boucle
    fprintf(f,"sb $t1,0($a2)\n");//on ecrit le caractere dans la chaine de caractere concatenee
    fprintf(f,"addi $a1,$a1,1\n");//on incremente l'adresse de la 2eme chaine de caractere
    fprintf(f,"addi $a2,$a2,1\n");//on incremente l'adresse de la chaine de caractere concatene
    fprintf(f,"j boucledeuxiemechaine\n");//on recommence


    fprintf(f,"\nstrconcatfin:\n");
    fprintf(f,"li $t1,0\n");//on met 0 dans $t1 pour dire que le caractere est nul
    fprintf(f,"sb $t1,0($a2)\n");//on ecrit le caractere nul dans la chaine de caractere concatenee
    fprintf(f,"jr $ra\n");//on retourne
}

//reserver la memoire pour les symboles et pour les labels 
void labelprint(struct labels l, int size_symb,FILE *f)
{
    fprintf(f, ".data\n .space %i   #place pour les symboles\n #place pour les lables de chaine de charactere\n", size_symb*4);
    for (int i = 0; i < l.cur_place; i++)
        fprintf(f, "la%i : .asciiz \"%s\"\n", i, l.tab[i]);

    fprintf(f, "la-1: .space 32         #the buffer for the read buffer of siez 32\n  \n\n .text\n");
}


void il2MIPS(struct quad quad, struct tabsymbole tabsymbole, struct labels labels)
{

    int isstring1 = 0;
    int isstring2 = 0;
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

                        //jr $s0
                        fprintf(f,"jr $s0\n");
                    }
                }
                break;
            case AFF:
                if(quad.quadrup[i].zero.s==NULL)
                {
                    printf("Error: variable not found");
                    exit(1);
                }
                switch(quad.quadrup[i].type)
                {
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
                                    fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].two.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].two.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s0,$%i\n",quad.quadrup[i].two.s->isint);
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
                                    fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].two.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].two.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s0,$%i\n",quad.quadrup[i].two.s->isint);
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
                                    fprintf(f,"lw $s0,0x%x\n",quad.quadrup[i].two.s->memory_place+DATA_SEGMENT);
                                    break;
                                case 1:
                                    fprintf(f,"lw $s0,%i($sp)\n",quad.quadrup[i].two.s->memory_place);
                                    break;
                                case 2:
                                    fprintf(f,"move $s0,$%i\n",quad.quadrup[i].two.s->isint);
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
                            isstring1=1;
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
                            isstring2=1;
                            break;
                        default:
                            printf("Error: variable not found");
                            exit(1);
                    }
                    fprintf(f,"lw $s1,%i\n",quad.quadrup[i].two.s->memory_place);
                }
                else
                {
                    fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                }
                
                if((isstring1 && !isstring2) || (!isstring1 && isstring2))
                {
                    printf("Error: cannot compare string with int");
                    exit(1);
                }

                if(isstring1 && isstring2)
                {
                    if(quad.quadrup[i].type == 0)//=
                    {
                        MIPSstrcompare(f);// à adapter pour que ca colle avec le reste
                        fprintf(f,"\n bne $t0,$zeros,a%i\n",quad.quadrup[i].zero.value);
                    }
                    else if(quad.quadrup[i].type == 1)//!=
                    {
                        MIPSstrcompare(f);// à adapter pour que ca colle avec le reste
                        fprintf(f,"\n beq $t0,$zeros,a%i\n",quad.quadrup[i].zero.value);
                    }
                    else
                    {
                        printf("Error: cannot compare string with < or >");
                        exit(1);
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
                }//fin switch type
                break;
            case SYS:
                fprintf(f,"li $v0,%i\n",quad.quadrup[i].zero.value);
                fprintf(f,"syscall\n");
                break;
        }//fin switch instruction
    }//fin for quad
}//fin fonction