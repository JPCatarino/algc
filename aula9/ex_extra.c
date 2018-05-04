#include <stdio.h>
#include "stack.h"

int main(){
    char word[20];
    PtStack stacky = StackCreate(30);
    fgets(word, 20, stdin);

    char* p = word;
    while(*p != '\0'){
        StackPush(stacky,p);
        p++;
    }
    while(!StackIsEmpty(stacky)){
        char c;
        StackPop(stacky, &c);
        if(c != '\0')
            printf("%c",c);
    }
    return -1;
}