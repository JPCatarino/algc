//
// Created by JPCatarino on 03/05/2018.
//

#include <stdio.h>
int multCounter = 0;


int schroder(int n);
int dynSchroder(int n);

int main() {
    for(int i = 0; i <=12; i++){
        printf("O numero de Schroder para %d: %d\n",i,schroder(i));
        printf("Nr de mults quando %d: %d\n",i,multCounter);
        multCounter = 0;
    }
    for(int i = 0; i <=12; i++){
        printf("O numero de Schroder para %d: %d\n",i,dynSchroder(i));
        printf("Nr de mults quando %d: %d\n",i,multCounter);
        multCounter = 0;
    }
}

// função não eficiente recursiva
int schroder (int n){
    int resCy = 0;
    if(n == 0)
        return 1;
    else{
        for(int i = 0; i <= n-1; i++){
            multCounter += 1;
            resCy += schroder(i) * schroder(n-i-1);
        }
        return schroder(n-1) + resCy;
    }
}

// dynamic programming
int dynSchroder(int n){
    int s[n];
    int i;
    int resCy = 0;
    s[0] = 1;

    for(i = 1;i<=n;i++){
        resCy = 0;
        for(int j = 0; j <= i-1; j++){
            multCounter += 1;
            resCy += s[j] * s[i-j-1];
        }
        s[i] = s[i-1] + resCy;
    }
    return s[n];

}