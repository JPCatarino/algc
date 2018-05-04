#include<stdio.h>

int isPower(unsigned int a, unsigned int b);

int div = 0;

int main(){
    unsigned int a;
    unsigned int b;
    for(a = 1; a < 100; a++) {
        div = 0;
        if (isPower(a, 3)) {
            printf("a = b^n\n");
            printf("%d e igual a 3^n\n",a);
        }
        else {
            printf("a != b^n\n");
            printf("%d e diferente de 3^n\n",a);
        }
       printf("ao final de %d divs\n", div);
    }
}

int isPower(unsigned int a, unsigned int b){
    if(a == 1){
        return 1;
    }
    if(a == b){
        return 1;
    }
    if(a % b != 0){
        return  0;
    }
    div++;
    return isPower(a/b, b);


}
