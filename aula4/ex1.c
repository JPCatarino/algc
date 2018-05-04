#include <stdio.h>
int counterOp = 0;

int sequence(int array[], int size){
    for(int i = 0; i < size; i++){
        if(i > 0) {
            counterOp++;
            if (array[i] != array[i - 1] + 1) {
                return 0;
            }
        }
    }
    return 1;
}


int main() {
//    int array[10] = {1,3,4,5,5,6,7,7,8,9};
//    int array[10] = {1,2,4,5,5,6,7,8,8,9};
//    int array[10] = {1,2,3,6,8,8,8,9,9,9};
//    int array[10] = {1,2,3,4,6,7,7,8,8,9};
//    int array[10] = {1,2,3,4,5,7,7,8,8,9};
//    int array[10] = {1,2,3,4,5,6,8,8,9,9};
//    int array[10] = {1,2,3,4,5,6,7,9,9,9};
//    int array[10] = {1,2,3,4,5,6,7,8,8,9};
//    int array[10] = {1,2,3,4,5,6,7,8,9,9};
    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    int result = sequence(array,10);
    if(result == 1){
        printf("O array contem uma sequencia de numeros\n");
    }
    else{
        printf("O array nao contem uma sequencia de numeros\n");
    }
    printf("Numero de add: %d", counterOp);
    return result;
}