#include <stdio.h>

int mults = 0;

int fib(int n);
int dynFib(int n);

void main(){
    for(int n = 0; n <=12;n++){
        printf("Resultado: %d\n",dynFib(n));
        printf("Nr Mults: %d\n",mults);
        mults = 0;
    }
}

int fib(int n){
    if(n<=1){
        return n;
    }
    else {
        mults = mults + 2;
        return (3 * fib(n - 1)) + (2 * fib(n - 2));
    }
}

int dynFib(int n){
    int f[n+2];
    int i;

    f[0] = 0;
    f[1] = 1;

    for(i = 2; i <= n; i++){
        mults = mults + 2;
        f[i] = (3 * f[i-1]) + (2 * f[i-2]);
    }

    return f[n];
}