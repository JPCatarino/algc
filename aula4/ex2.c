#include <stdio.h>

int numComp = 0;
int numDesc = 0;

void DeleteRepElems (int [], int*);

int main(){
//    int array[10] = {1,2,2,2,3,3,4,5,8,8}; // NumC = 28 NumD = 21
//    int array[10] = {1,2,2,2,3,3,3,3,8,8}; // NumC = 23 NumD = 28
//    int array[10] = {1,2,5,4,7,0,3,9,6,8}; // NumC = 45 NumD = 0;
//    int array[10] = {1,1,3,4,5,6,7,8,8,9};
//    int array[10] = {1,1,1,1,1,1,1,1,1,1};
//    int array[10] = {1,2,2,3,2,2,1,1,4,4};

    int size = 10;
    DeleteRepElems(array,&size);
    for(int i=0; i<size;i++){
        printf("%d ", array[i]);
    }
    printf("\nNum de Comp: %d Num de Desc: %d\n",numComp,numDesc);
    return 0;
}

void DeleteRepElems (int array[], int * size){
    int nrElems = *size;
    for(int i = 0; i < nrElems; i++){
        for(int j = i + 1; j < nrElems;){
            numComp++;
            if(array[j] == array[i]){
                for(int k = j; k < nrElems-1; k++){
                    numDesc++;
                    array[k] = array[k+1];
                }
                nrElems--;
            }
            else j++;
        }
    }
    *size = nrElems;
}
