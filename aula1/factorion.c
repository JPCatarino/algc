#include <stdio.h>

int main(){
    int i, j, k, resto, fact, soma,multic;
    for(i = 1;i < 1000000;i++){
        soma = 0;
        for(j = i;j>0;j = j/10){
            resto = j%10;
            fact = 1;
            for(k = 1;k <= resto;k++){
                fact = fact * k;
                multic++;
            }
            soma += fact;
        }
        if (soma == i) {
            printf("%d\n", soma);
        }
    }
    printf("o numero de multiplicacoes foi %d", multic);
}

