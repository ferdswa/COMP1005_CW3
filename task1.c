#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char ruleset(char,char,char,int);
int inputChecker(char*);
int main(int argc, char **argv)
{
    int numCells,numGens,rule,i,j,ccell,t1,t2,t3;
    char *ptr1, *current, left,right;
    if(argc!=4)
    {
        printf("You have entered the wrong number of arguments!\n");
        return -1;
    }
    t1=inputChecker(argv[1]);
    t2=inputChecker(argv[2]);
    t3=inputChecker(argv[3]);
    if(t1==0)
    {
        printf("You have entered a non-integer value!\n");
        return -1;
    }
    else if(t2==0)
    {
        printf("You have entered a non-integer value!\n");
        return -1;
    }
    else if(t3==0)
    {
        printf("You have entered a non-integer value!\n");
        return -1;
    }
    numCells=strtol(argv[1],&ptr1,10);
    numGens=strtol(argv[2],&ptr1,10);
    rule=strtol(argv[3],&ptr1,10);
    if(numCells==0){
        printf("Cells value not in accepted range. Must be >0.\n");
        return -1;}
    else if(numGens==0){
        printf("Generation value not in accepted range. Must be >0\n");
        return -1;}
    else if((rule<=0) | (rule>=255))
    {
        printf("Rule value not in accepted range. Must be 0<=rule<=255\n");
        return -1;
    }
    current = calloc(numCells*2,sizeof(char));
    ccell = numCells/2;
    for(i=0;i<numCells;i++)
    {
        current[i]=32;
    }
    current[ccell]=42;
    for(i=0;i<numGens;i++)
    {
        for(j=0;j<numCells;j++)
        {
            printf("%c",current[j]);
        }
        printf("\n");
        for(j=0;j<numCells;j++)
        {
            if(j==0)
            {
                left=current[numCells-1];
                right=current[j+1];
            }
            else if(j==(numCells-1))
            {
                left=current[j-1];
                right=current[0];
            }
            else
            {
                left=current[j-1];
                right=current[j+1];
            }
            current[numCells+j]=ruleset(left,current[j],right,rule);
        }
        for(j=0;j<numCells;j++)
        {
            current[j]=current[numCells+j];
        }
    }
    free(current);
    return 0;
}
char ruleset(char c1,char c2,char c3,int rule)
{
    int sum=0;
    if(c1==42)
        sum+=4;
    if(c2==42)
        sum+=2;
    if(c3==42)
        sum+=1;
    rule=rule>>sum;
    if(rule&1)
        return 42;
    else
        return 32;
}
int inputChecker(char *input)
{
    while(*input)
    {
        if(isdigit(*input++)==0)
        {
            return 0;
        }
    }
    return 1;
}