#include <stdio.h>
#include "gencode.h"
#include "tabsymbole.h"


/*
Declaration of fonctions used to 
Fill different type of instructions
@param instructions: int to fill
@param place: where to fill the number (if present)
@param number: number to add to the instruction
*/

//function to fill opcode of instructions

void fillopcode(int instructions, int number)
{
    int i;
    int k;
    for (i = 5; i>=0; i--)
    {
        k=number>>i;
        if (k & 1)
            instructions |= (1<<(26+i));
        else
            instructions &= ~(1<<(26+i));
    }
}

//function to fill R instructions

void fillRinst(int instructions, int place,int number)
{
    int i=0;
    int k=0;
    int begin = 0;

    switch(place)
    {
        case 1:
            //rs
            begin = 21 ;
            break;
        case 2:
            //rt
            begin = 16 ;
            break;
        case 3:
            //rd
            begin = 11 ;
            break;
        case 4:
            //shamt
            begin = 6 ;
            break;
        case 5:
            //funct
            begin = 0 ;
            break;
    }

    if(place!=5)
    {
        for (i = 4; i>=0; i--)
        {
            k=number>>i;

            if (k & 1)
                instructions |= (1<<(begin+i));
            else
                instructions &= ~ (1<<(begin+i));
        }
    }
    else
    {
        for (i = 5; i>=0; i--)
        {
            k=number>>i;

            if (k & 1)
                instructions |= (1<<(begin+i));
            else
                instructions &= ~(1<<(begin+i));
        }
    }
}

//function to fill I instructions

void fillIinst(int instructions, int place,int number)
{
    int i=0;
    int k=0;
    int begin = 0;

    switch(place)
    {
        case 1:
            //rs
            begin = 21 ;
            break;
        case 2:
            //rt
            begin = 16 ;
            break;
        case 3:
            //immediate
            begin = 0 ;
            break;
    }

    if(place!=3)
    {
        for (i = 4; i>=0; i--)
        {
            k=number>>i;

            if (k & 1)
                instructions |= (1<<(begin+i));
            else
                instructions &= ~(1<<(begin+i));
        }
    }
    else
    {
        for (i = 15; i>=0; i--)
        {
            k=number>>i;

            if (k & 1)
                instructions |= (1<<(begin+i));
            else
                instructions &= ~(1<<(begin+i));
        }
    }
}

//function to fill J instructions

void fillJinst(int instructions,int number)
{
    int i=0;
    int k=0;
    int begin = 0;

    for (i = 25; i>=0; i--)
    {
        k=number>>i;

        if (k & 1)
            instructions |= (1<<(begin+i));
        else
            instructions &= ~(1<<(begin+i));
    }
}

//function to fill FR instructions

void fillFRinst(int instructions, int place,int number)
{
    int i=0;
    int k=0;
    int begin = 0;

    switch(place)
    {
        case 1:
            //fmt
            begin = 21 ;
            break;
        case 2:
            //ft
            begin = 16 ;
            break;
        case 3:
            //fs
            begin = 11 ;
            break;
        case 4:
            //fd
            begin = 6 ;
            break;
        case 5:
            //funct
            begin = 0 ;
            break;
    }

    if(place!=5)
    {
        for (i = 4; i>=0; i--)
        {
            k=number>>i;

            if (k & 1)
                instructions |= (1<<(begin+i));
            else
                instructions &= ~(1<<(begin+i));
        }
    }
    else
    {
        for (i = 5; i>=0; i--)
        {
            k=number>>i;

            if (k & 1)
                instructions |= (1<<(begin+i));
            else
                instructions &= ~(1<<(begin+i));
        }
    }
}

//function to fill FI instructions

void fillFIinst(int instructions, int place,int number)
{
    int i=0;
    int k=0;
    int begin = 0;

    switch(place)
    {
        case 1:
            //fmt
            begin = 21 ;
            break;
        case 2:
            //rt
            begin = 16 ;
            break;
        case 3:
            //immediate
            begin = 0 ;
            break;
    }

    if(place!=3)
    {
        for (i = 4; i>=0; i--)
        {
            k=number>>i;

            if (k & 1)
                instructions |= (1<<(begin+i));
            else
                instructions &= ~(1<<(begin+i));
        }
    }
    else
    {
        for (i = 15; i>=0; i--)
        {
            k=number>>i;

            if (k & 1)
                instructions |= (1<<(begin+i));
            else
                instructions &= ~(1<<(begin+i));
        }
    }
}


//function to write the binary code in the file
void iltoMIPS(struct quad quad)
{
    //creation of the int for the different instructions
    int instructions=0;

    //creation of the file that will contain the binary code
    FILE *f = fopen("codeMIPS.s", "wb");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int i;
    for (i = 0; i < quad.next; i++)
    {
        //set (or reset) the int to 0 (to avoid problems)
        instructions = 0;

        switch (quad.quadrup[i].instruction)
        {
            case GOTO:
                //if it is a direct jump
                if(quad.quadrup[i].zero.s == NULL)
                {
                    fillJinst(instructions, quad.quadrup[i].zero.value);
                }
                //if it is an indirect jump
                else
                {
                    //we are gonna do lui $1 and the word without the 4 last bits
                    fillopcode(instructions, 0x0F);

                    fillIinst(instructions, 1, 0);

                    fillIinst(instructions, 2, 1);

                    fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place>>16);

                    fwrite(&instructions, sizeof(int), 1, f);

                    //lw $s0 add1($1)
                    fillopcode(instructions, 0x23);

                    fillIinst(instructions, 1, 1);

                    fillIinst(instructions, 2, 16);

                    fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place);

                    fwrite(&instructions, sizeof(int), 1, f);

                    //make the jump j
                    fillopcode(instructions, 0);

                    fillRinst(instructions, 1, 16);

                    fillRinst(instructions, 2, 0);

                    fillRinst(instructions, 3, 0);

                    fillRinst(instructions, 4, 0);

                    fillRinst(instructions, 5, 8);

                    fwrite(&instructions, sizeof(int), 1, f);
                }
                break;
            case AFF:
                if(quad.quadrup[i].zero.s == NULL)
                {
                    printf("Erreur: la variable n'existe pas\n");
                    exit(1);
                }


                switch (quad.quadrup[i].type)
                {
                    case 0: //affectation simple
                        if(quad.quadrup[i].one.s != NULL)
                        {
                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //lw $s1 addr2($1)
                            fillopcode(instructions, 0x23);

                            fillIinst(instructions, 1, 1);

                            fillIinst(instructions, 2, 17);

                            fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);




                            //add $s0 $zero $s1
                            fillopcode(instructions, 0);
                            
                            fillRinst(instructions,1,0);

                            fillRinst(instructions,2,17);

                            fillRinst(instructions,3,16);

                            fillRinst(instructions,4,0);

                            fillRinst(instructions,5,0x20);
                            fwrite(&instructions, sizeof(int), 1, f);



                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //sw $s0 add1($1)
                            fillopcode(instructions, 0x2b);

                            //rs
                            fillIinst(instructions, 1, 1);

                            //rt
                            fillIinst(instructions, 2, 16);

                            //immediate
                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //fprintf(f,"move $%i, $%i\n", quad.quadrup[i].zero.s->memory_place, quad.quadrup[i].one.s->memory_place);
                        }
                        else
                        {
                            //addi $s0 $zero value
                            fillopcode(instructions, 8);

                            fillIinst(instructions,1,0);

                            fillIinst(instructions,2,17);

                            fillIinst(instructions,3,quad.quadrup[i].one.value);

                            fwrite(&instructions, sizeof(int), 1, f);



                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //sw $s0 add1

                            fillopcode(instructions, 0x2b);

                            //rs
                            fillIinst(instructions, 1, 1);

                            //rt
                            fillIinst(instructions, 2, 16);

                            //immediate
                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //fprintf(f,"li $%i, %i\n", quad.quadrup[i].zero.s->memory_place, quad.quadrup[i].one.value);
                        }
                    break;

                    case 1: //addition
                        if(quad.quadrup[i].two.s != NULL)
                            {
                                //we are gonna do lui $1 and the word without the 4 last bits
                                fillopcode(instructions, 0x0F);

                                fillIinst(instructions, 1, 0);

                                fillIinst(instructions, 2, 1);

                                fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place>>16);

                                fwrite(&instructions, sizeof(int), 1, f);

                                //lw $s1 add2
                                fillopcode(instructions, 0x23);

                                fillIinst(instructions, 1, 1);

                                fillIinst(instructions, 2, 17);

                                fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place);

                                fwrite(&instructions, sizeof(int), 1, f);

                                
                                
                                //we are gonna do lui $1 and the word without the 4 last bits
                                fillopcode(instructions, 0x0F);

                                fillIinst(instructions, 1, 0);

                                fillIinst(instructions, 2, 1);

                                fillIinst(instructions, 3, quad.quadrup[i].two.s->memory_place>>16);

                                fwrite(&instructions, sizeof(int), 1, f);

                                //lw $s2 add3
                                fillopcode(instructions, 0x23);

                                fillIinst(instructions, 1, 1);

                                fillIinst(instructions, 2, 18);

                                fillIinst(instructions, 3, quad.quadrup[i].two.s->memory_place);

                                fwrite(&instructions, sizeof(int), 1, f);



                                //add $s0 $s1 $s2
                                fillopcode(instructions, 0);
                                
                                fillRinst(instructions,1,17);

                                fillRinst(instructions,2,18);

                                fillRinst(instructions,3,16);

                                fillRinst(instructions,4,0);

                                fillRinst(instructions,5,0x20);

                                fwrite(&instructions, sizeof(int), 1, f);



                                //we are gonna do lui $1 and the word without the 4 last bits
                                fillopcode(instructions, 0x0F);

                                fillIinst(instructions, 1, 0);

                                fillIinst(instructions, 2, 1);

                                fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place>>16);

                                fwrite(&instructions, sizeof(int), 1, f);

                                //sw $t0 add1

                                fillopcode(instructions, 0x2b);

                                //rs
                                fillIinst(instructions, 1, 1);

                                //rt
                                fillIinst(instructions, 2, 16);

                                //immediate
                                fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place);

                                fwrite(&instructions, sizeof(int), 1, f);

                                //fprintf(f,"add $%i, $%i, $%i\n", quad.quadrup[i].zero.s->memory_place, quad.quadrup[i].one.s->memory_place, quad.quadrup[i].two.s->memory_place);
                            }
                        else
                        {
                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //lw $s1 add2
                            fillopcode(instructions, 0x23);

                            fillIinst(instructions, 1, 1);

                            fillIinst(instructions, 2, 17);

                            fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);


                            
                            //addi $t0 $t1 value
                            fillopcode(instructions, 8);

                            fillIinst(instructions,1,17);

                            fillIinst(instructions,2,16);

                            fillIinst(instructions,3,quad.quadrup[i].two.value);



                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //sw $t0 add1

                            fillopcode(instructions, 0x2b);

                            //rs
                            fillIinst(instructions, 1, 1);

                            //rt
                            fillIinst(instructions, 2, 16);

                            //immediate
                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //fprintf(f,"addi $%i, $%i, %i\n", quad.quadrup[i].zero.s->memory_place, quad.quadrup[i].one.s->memory_place, quad.quadrup[i].two.value);
                        }
                    break;

                    case 2: //soustraction
                        if(quad.quadrup[i].two.s != NULL)
                        {
                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //lw $s1 add2
                            fillopcode(instructions, 0x23);

                            fillIinst(instructions, 1, 1);

                            fillIinst(instructions, 2, 17);

                            fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);

                            
                            
                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].two.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //lw $s2 add3
                            fillopcode(instructions, 0x23);

                            fillIinst(instructions, 1, 1);

                            fillIinst(instructions, 2, 18);

                            fillIinst(instructions, 3, quad.quadrup[i].two.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);



                            //sub $s0 $s1 $s2
                            fillopcode(instructions, 0);

                            fillRinst(instructions,1,17);

                            fillRinst(instructions,2,18);

                            fillRinst(instructions,3,16);

                            fillRinst(instructions,4,0);

                            fillRinst(instructions,5,0x22);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //sw $t0 add1
                            fillopcode(instructions, 0x2b);

                            //rs
                            fillIinst(instructions, 1, 1);

                            //rt
                            fillIinst(instructions, 2, 16);

                            //immediate
                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);


                            //fprintf(f,"sub $%i, $%i, $%i\n", quad.quadrup[i].zero.s->memory_place, quad.quadrup[i].one.s->memory_place, quad.quadrup[i].two.s->memory_place);
                        }
                        else
                        {
                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //lw $s1 add2
                            fillopcode(instructions, 0x23);

                            fillIinst(instructions, 1, 1);

                            fillIinst(instructions, 2, 17);

                            fillIinst(instructions, 3, quad.quadrup[i].one.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);



                            //addi $s2 $zero value

                            fillopcode(instructions, 0x08);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 18);

                            fillIinst(instructions, 3, quad.quadrup[i].two.value);

                            fwrite(&instructions, sizeof(int), 1, f);



                            //sub $s0 $s1 $s2
                            fillopcode(instructions, 0);

                            fillRinst(instructions,1,quad.quadrup[i].one.s->memory_place);

                            fillRinst(instructions,2,quad.quadrup[i].zero.s->memory_place);

                            fillRinst(instructions,3,quad.quadrup[i].two.value);

                            fillRinst(instructions,4,0);

                            fillRinst(instructions,5,0x22);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //we are gonna do lui $1 and the word without the 4 last bits
                            fillopcode(instructions, 0x0F);

                            fillIinst(instructions, 1, 0);

                            fillIinst(instructions, 2, 1);

                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place>>16);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //sw $t0 add1
                            fillopcode(instructions, 0x2b);

                            //rs
                            fillIinst(instructions, 1, 1);

                            //rt
                            fillIinst(instructions, 2, 16);

                            //immediate
                            fillIinst(instructions, 3, quad.quadrup[i].zero.s->memory_place);

                            fwrite(&instructions, sizeof(int), 1, f);

                            //fprintf(f,"subi $%i, $%i, %i\n", quad.quadrup[i].zero.s->memory_place, quad.quadrup[i].one.s->memory_place, quad.quadrup[i].two.value);
                        }
                    break;

                    case 3:
                    break;
                }
                break;
        } //end switch
    
    fwrite(&instructions, sizeof(int), 1, f);
    } //end for
} //end function