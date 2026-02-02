#include<stdio.h>

//prototypes
void whileloop(int);
void whileflag(int);
void DoWhile(int);
int total;

int main(void){


//whileloop(5);
whileflag(5);
//DoWhile(5);

}



//While w/counter Loop
void whileloop(int n){

int ct = 0;
total = 0;

while(ct<=n){

total+=ct;
ct++;

}
printf("total = %d\n\n", total);
}

//While w/flag
void whileflag(int n){

int flag = 1;
total = 0;

while(flag){

if(n>0)
total+=n;

else
flag = 0;

n--;

}
printf("total = %d\n\n", total);
}

//DoWhile

void DoWhile(int n){

total = 0;

do{

total+=n;
n--;

}while(n>0);
printf("total = %d\n\n", total);
}







