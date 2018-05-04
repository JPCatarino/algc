#include <stdio.h>

int main(){
    int i, j, resto;
    printf("Numeros de Armstrong com 3 digitos: \n");
    for(i = 100;i < 999;i++){
        int soma = 0;
        for(j = i;j>0;j = j/10){
            resto = j%10;
            soma = soma +(resto*resto*resto);

        }
        if(soma == i){
            printf("%d\n",soma);
        }
    }

    return 0;
}