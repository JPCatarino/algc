#include <stdio.h>
#include <time.h>
#include "elapsed_time.h"

int compa = 0;

int lesserElem(int array[],int size){
    int NumberOfElems = 0;
    int index = -1;
    for(int i = 0; i < size; i++){
        int temp = 0;
        for(int j = 0; j < i;j++){
            compa++;
            if(array[i] > array[j]){
                temp++;
            }
        }
        if (temp > NumberOfElems){
            index = i;
            NumberOfElems = temp;
        }
    }
    return index;
}




int main(){
//    int array[10] = {1,9,2,8,3,4,5,3,7,2};
    int result;
//    int array[10] = {1,7,4,6,5,3,2,1,0};
    int array[10] = {2,2,2,2,2,2,2,2,2,2};
    clock_t begin = clock();
    (void)elapsed_time();
    result = lesserElem(array, 10);
    double tempo = elapsed_time();
    clock_t end = clock();
    double ciclos = (double) end - begin / CLOCKS_PER_SEC;
    if(result > -1) {
        printf("o numero com mais elementos menores e %d, encontrado apos: %f, ao final de %f ciclos\n", array[result], tempo, ciclos);
    }
    printf("Comparacoes = %d", compa);
    return 0;
}
