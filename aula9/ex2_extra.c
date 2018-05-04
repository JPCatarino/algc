#include <stdio.h>
#include "stack.h"
#include "queue.h"

int checkPalindrome(PtStack s,PtQueue q);

int main(){
    char cap[20];
    PtStack stacky = StackCreate(30);
    PtQueue queuey = QueueCreate(30);
    fgets(cap,20,stdin);
    char *p = cap;

    while(*p != '\0'){
        StackPush(stacky,p);
        QueueEnqueue(queuey,p);
        p++;
    }
    if(checkPalindrome(stacky,queuey))
        printf("nice");
}

int checkPalindrome(PtStack s,PtQueue q){
    char c1;
    char c2;
    int res = 0;
    while(!StackIsEmpty(s) && !QueueIsEmpty(q)){
        StackPop(s, &c1);
        QueueDequeue(q,&c2);
        printf("a\n");
            if(c1 == c2){
                res = 1;
            }
            else{
                return 0;
            } 
        }    
    return res;
}