/*
Lists 
- Homogeneous elements (of the same type in each list)
- Finite Length
- The elements are sequentially arranged in the list.

Used in 3 ways
- Static array
- Dynamic array

Written by Alex Ludwig
Feb 2026

*/

#include <stdio.h>
#include <stdlib.h>

//member is an alias of RECORD
typedef struct member{
    int number;
    struct member *next;
} RECORD;

//Prototypes
RECORD* insert(RECORD *it,  int value);
void traverse_and_print(RECORD *head);

int main (void){

    int result;
    RECORD *head, *p;

    head = NULL;
    result = 1;

    for(int i=1; i<6; i++)
        head = insert(head, i);

    traverse_and_print(head);
}

RECORD* insert(RECORD *it, int value){
    RECORD *cur, *q;
    printf("Entering insert, value is %d\n", value);
    cur = (RECORD *)malloc(sizeof(RECORD));
    cur->number = value;
    cur->next = NULL;
    if(it == NULL)
        it = cur;
    else{
        q = it;
        while(q->next!=NULL)
            q = q->next;
        q->next = cur;
    }
    return it;
}

void traverse_and_print(RECORD *head){

    RECORD *p;
    int result;
    result=1;
    p=head;
    while (p!=NULL){

        result=result*p->number;
        p=p->next;
    }
    printf("result is %d\n", result);
    return;

}