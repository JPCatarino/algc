#include <stdio.h>

int gtl (int intarray[],int size){
    int counter = 0;
    int comparar = 0;
    for(int i = 0; i < size; i++){
        if(i > 0){                         /* n comparações */
            comparar++;                     
            if(intarray[i] != intarray[i-1]){   /* n-1 comparações */
                counter++;
            }
        }
    }
    printf("Numero de comparacoes: %d%\n", comparar);
    return counter;

}

int main() {
    int intarray [10] = {4,5,1,2,6,8,7,9,3,0};
    int result = gtl(intarray,10);
    printf("Existem %d elemento diferentes",result);
    return 0;
}

