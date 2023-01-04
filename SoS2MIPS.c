#include "SoS2MIPS.h"

void MIPSstrlen(FILE *f)
{
    fprintf(f,"strlen:\n");

    fprintf(f,"li $t0,0\n");

    fprintf(f,"strlenboucle:\n");
    fprintf(f,"lb $t1,0($a0)\n");
    fprintf(f,"beq $t1,$zero,strlenfin\n");
    fprintf(f,"addi $a0,$a0,1\n");
    fprintf(f,"addi $t0,$t0,1\n");
    fprintf(f,"j strlenboucle\n");

    fprintf(f,"strlenfin:\n");
    fprintf(f,"jr $ra\n");
}

//je sais pas ce que c'est  ---> reserver la memoire pour les symboles et pour les labels 
void labelprint(struct labels l, int size_symb,FILE *f)
{
    fprintf(f, ".data\n .space %i   #place pour les symboles\n #place pour les lables de chaine de charactere\n", size_symb);
    for (int i = 0; i < l.cur_place; i++)
        fprintf(f, "la%i : .asciiz \"%s\"\n", i, l.tab[i]);

    fprintf(f, "la-1: .space 32         #the buffer for the read buffer of siez 32\n  \n\n .text\n");
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
        switch(quad.quadrup[i].instruction)
        {
            case GOTO:
                if(quad.quadrup[i].zero.s==NULL)
                {
                    fprintf(f,"j %i\n",quad.quadrup[i].zero.value);
                }
                else
                {
                    //sw $s0,addr0
                    fprintf(f,"sw $s0,%i\n",quad.quadrup[i].zero.s->memory_place);

                    //jr $s0
                    fprintf(f,"jr $s0\n");
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
                        }
                        else
                        {
                            fprintf(f,"lw $s0,%i\n",quad.quadrup[i].one.s->memory_place);
                        }
                        fprintf(f,"sw $s0,%i\n",quad.quadrup[i].zero.s->memory_place);
                        break;


                    case 1://addition
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                        }
                        else
                        {
                            fprintf(f,"lw $s0,%i\n",quad.quadrup[i].one.s->memory_place);
                        }
                        if(quad.quadrup[i].two.s==NULL)
                        {
                            fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                        }
                        else
                        {
                            fprintf(f,"lw $s1,%i\n",quad.quadrup[i].two.s->memory_place);
                        }


                        fprintf(f,"add $s0,$s0,$s1\n");
                        fprintf(f,"sw $s0,%i\n",quad.quadrup[i].zero.s->memory_place);

                        break;


                    case 2://soustraction
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                        }
                        else
                        {
                            fprintf(f,"lw $s0,%i\n",quad.quadrup[i].one.s->memory_place);
                        }
                        if(quad.quadrup[i].two.s==NULL)
                        {
                            fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                        }
                        else
                        {
                            fprintf(f,"lw $s1,%i\n",quad.quadrup[i].two.s->memory_place);
                        }

                        fprintf(f,"sub $s0,$s0,$s1\n");
                        fprintf(f,"sw $s0,%i\n",quad.quadrup[i].zero.s->memory_place);

                        break;
                    case 3://multiplication
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                        }
                        else
                        {
                            fprintf(f,"lw $s0,%i\n",quad.quadrup[i].one.s->memory_place);
                        }
                        if(quad.quadrup[i].two.s==NULL)
                        {
                            fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                        }
                        else
                        {
                            fprintf(f,"lw $s1,%i\n",quad.quadrup[i].two.s->memory_place);
                        }

                        fprintf(f,"mult $s0,$s1\n");
                        fprintf(f,"mflo $s0\n");
                        fprintf(f,"sw $s0,%i\n",quad.quadrup[i].zero.s->memory_place);

                        break;
                    case 4://division
                        if(quad.quadrup[i].one.s==NULL)
                        {
                            fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                        }
                        else
                        {
                            fprintf(f,"lw $s0,%i\n",quad.quadrup[i].one.s->memory_place);
                        }
                        if(quad.quadrup[i].two.s==NULL)
                        {
                            fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                        }
                        else
                        {
                            fprintf(f,"lw $s1,%i\n",quad.quadrup[i].two.s->memory_place);
                        }

                        fprintf(f,"div $s0,$s1\n");
                        fprintf(f,"mflo $s0\n");
                        fprintf(f,"sw $s0,%i\n",quad.quadrup[i].zero.s->memory_place);

                        break;
                }//fin switch type
                break;
            case IF:
                if(quad.quadrup[i].one.s != NULL )
                {
                    fprintf(f,"lw $s0,%i\n",quad.quadrup[i].one.s->memory_place);
                }
                else
                {
                    fprintf(f,"li $s0,%i\n",quad.quadrup[i].one.value);
                }
                if(quad.quadrup[i].two.s != NULL )
                {
                    fprintf(f,"lw $s1,%i\n",quad.quadrup[i].two.s->memory_place);
                }
                else
                {
                    fprintf(f,"li $s1,%i\n",quad.quadrup[i].two.value);
                }
                switch(quad.quadrup[i].type)
                {
                    case 0://=
                        fprintf(f,"beq $s0,$s1,%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 1://!=
                        fprintf(f,"bne $s0,$s1,%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 2://<
                        fprintf(f,"blt $s0,$s1,%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 3://>
                        fprintf(f,"bgt $s0,$s1,%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 4://<=
                        fprintf(f,"ble $s0,$s1,%i\n",quad.quadrup[i].zero.value);
                        break;
                    case 5://>=
                        fprintf(f,"bge $s0,$s1,%i\n",quad.quadrup[i].zero.value);
                        break;
                }//fin switch type
                break;
            case SYS:
                switch(quad.quadrup[i].zero.value)
                {
                    case 1://print
                        if(quad.quadrup[i].one.s != NULL )
                        {
                            fprintf(f,"lw $a0,%i\n",quad.quadrup[i].one.s->memory_place);
                        }
                        else
                        {
                            fprintf(f,"li $a0,%i\n",quad.quadrup[i].one.value);
                        }
                        fprintf(f,"li $v0,1\n");
                        fprintf(f,"syscall\n");
                        break;
                    case 2://print float
                        if(quad.quadrup[i].one.s != NULL )
                        {
                            fprintf(f,"lw $f12,%i\n",quad.quadrup[i].one.s->memory_place);
                        }
                        else
                        {
                            fprintf(f,"li $f12,%i\n",quad.quadrup[i].one.value);
                        }
                        fprintf(f,"li $v0,2\n");
                        fprintf(f,"syscall\n");
                        break;
                    case 3://print double
                        if(quad.quadrup[i].one.s != NULL )
                        {
                            fprintf(f,"lw $f12,%i\n",quad.quadrup[i].one.s->memory_place);
                        }
                        else
                        {
                            fprintf(f,"li $f12,%i\n",quad.quadrup[i].one.value);
                        }
                        if(quad.quadrup[i].two.s != NULL )
                        {
                            fprintf(f,"lw $f13,%i\n",quad.quadrup[i].two.s->memory_place);
                        }
                        else
                        {
                            fprintf(f,"li $f13,%i\n",quad.quadrup[i].two.value);
                        }
                        fprintf(f,"li $v0,3\n");
                        fprintf(f,"syscall\n");
                        break;
                    case 4://print string
                        fprintf(f,"la $a0,%i\n",quad.quadrup[i].one.s->memory_place);
                        fprintf(f,"li $v0,4\n");
                        fprintf(f,"syscall\n");
                        break;
                    case 5://read int
                        fprintf(f,"li $v0,5\n");
                        fprintf(f,"syscall\n");
                        fprintf(f,"sw $v0,%i\n",quad.quadrup[i].one.s->memory_place);
                        break;
                    case 6://read float
                        fprintf(f,"li $v0,6\n");
                        fprintf(f,"syscall\n");
                        fprintf(f,"sw $f0,%i\n",quad.quadrup[i].one.s->memory_place);
                        break;
                    case 7://read double
                        fprintf(f,"li $v0,7\n");
                        fprintf(f,"syscall\n");
                        fprintf(f,"sw $f0,%i\n",quad.quadrup[i].one.s->memory_place);
                        break;
                    case 8://read string à modifier
                        fprintf(f,"li $v0,8\n");
                        fprintf(f,"syscall\n");
                        fprintf(f,"sw $v0,%i\n",quad.quadrup[i].one.s->memory_place);
                        break;
                    case 9://sbrk
                        fprintf(f,"li $v0,9\n");
                        fprintf(f,"li $a0,%i\n",quad.quadrup[i].one.value);
                        fprintf(f,"syscall\n");
                        fprintf(f,"sw $v0,%i\n",quad.quadrup[i].two.s->memory_place);
                        break;
                    case 10://exit
                        fprintf(f,"li $v0,10\n");
                        fprintf(f,"syscall\n");
                        break;
                    
                    
                }
        }//fin switch instruction
    }//fin for quad
}//fin fonction