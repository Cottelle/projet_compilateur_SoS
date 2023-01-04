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

void il2MIPS(struct quad quad)
{
    FILE *f=fopen("codeMIPS.s","w");
    if(f==NULL)
    {
        printf("Error opening file");
        exit(1);
    }

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
                    case 0://print
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
                }
        }//fin switch instruction
    }//fin for quad
}//fin fonction