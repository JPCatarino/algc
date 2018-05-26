#include <stdio.h>
#include <stdlib.h>

#include "pqueue.h" 

void heapSort (int array[], int size);
int main(void){
    int array[20], i;
    for(i = 0; i < 20; i++)
        array[i] = (rand() % 100)+1;
    heapSort(array,20);

    for(int i=0;i<20;i++)
        printf("%d\n",array[i]);

    return 0;
}

void heapSort(int array[], int size){
    PtPQueue heap = PQueueCreate(size);
    for (int i = 0;i < 20; i++)
        PQueueInsert(heap,array[i]);

    for(int i = size-1; i>=0;i--)
        PQueueDeleteMax(heap,&array[i]);

    PQueueDestroy(&heap);
}

void ksmallest(int array[], int size){
    PtPQueue heap = PQueueCreate(size);
    int min = 9999;
    for(int i = 0;i < 20;i++) {
        PQueueInsert(heap, array[i]);
        if(array[i] < min)
            min = array[i];
    }
    while(!PQueueIsEmpty){

    }
}