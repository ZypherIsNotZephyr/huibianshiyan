/*
G: 	T-> BC
	B->int|float
	C->[num]C1|^
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR -1
typedef struct TypeAndWidth{
    char type[100];
    int width;
}taw;
char sym,a[50];
int ip=0;
int w;
char t[20];
taw T();
taw B();

void getNextSym()
{
    sym=a[++ip];
}
int StrToInt(char a[])
{
    int num=0;
    ip=ip+1;
    while(a[ip]!=']')
    {
        num=10*num+(int)(a[ip]-'0');
        ip+=1;
    }
    ip--;
    if (num==0)
        return ERROR;
    return num;
}
void main()                      /*递归分析*/
{
	taw ret;
	while(1){
        printf("\nPlease Input Length < 50,Ending with'#'; '^#' to Return!\n");
        ip=0;
        do{
            scanf("%c",&sym);
            a[ip++]=sym;
        }while(sym!='#');

        if(a[0]=='^' && a[1]=='#')
            return;

        printf("........BEGIN........\n");
        printf("......Analyzing......\n");
        ip=-1;
        getNextSym();
        ret=T();
        if (ret.width==ERROR)
            printf("Error Input\n");
        printf(".........END.........\n");
        if (ret.width != ERROR && sym=='#'){
            printf("\n....THE ANSWER....\n");
            printf("Type:%s\nWidth:%d\n",ret.type,ret.width);
            printf(".......END.......\n");
        }
        else{
            printf("\n....THE ANSWER....\n");
            printf(".......ERROR........\n");
        }
        getchar();
	}
}
taw T()
{
    taw tawB;
    if(strncmp(a,"int",3)==0){
        ip=ip+2;
        printf("T->B1\n");
        strcpy(tawB.type,"integer");
        tawB.width=4;
        getNextSym();
        strcpy(t,tawB.type);
        w = tawB.width;
        tawB = B();
        if(tawB.width==-1)
            return tawB;
    }
    else if(strncmp(a,"float",5)==0){
        ip=ip+4;
        printf("T->B2\n");
        strcpy(tawB.type,"float");
        tawB.width=8;
        getNextSym();
        strcpy(t,tawB.type);
        w = tawB.width;
        tawB = B();
        if(tawB.width==-1)
            return tawB;
    }
    else{
        tawB.width=-1;
        return tawB;
    }
    return tawB;
}
taw B()
{
    taw tawC;
    int num;
    char z[10];
    taw temp;
    char * str;
    if(sym == '['){
        printf("C->[num]C1\n");
        num=StrToInt(a);
        //printf("%d",num);
        if(num==ERROR){
            tawC.width=-1;
            return tawC;
        }
        getNextSym();
        if(sym==']'){
            getNextSym();
            temp = B();
            if(temp.width==-1){
                tawC.width=-1;
                return tawC;
            }
        }
        char z1[10]="array(";
        char z2[10]=",";
        char z3[50];
        char z4[10]=")";
        strcpy(z3,temp.type);
        strcpy(tawC.type,strcat(strcat(strcat(strcat(z1,itoa(num,z,10)),z2),z3),z4));
        tawC.width=num*temp.width;
        printf("type:%s\twidth:%d\n",tawC.type,tawC.width);
    }
    else if(sym == '#'){
        printf("C->^\n");
        strcpy(tawC.type,t);
        tawC.width=w;
        printf("type:%s\twidth:%d\n",tawC.type,tawC.width);
    }
    else{
        tawC.width=-1;
        return tawC;
    }
    return tawC;
}
