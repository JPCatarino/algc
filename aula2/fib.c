#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "elapsed_time.h"
typedef unsigned long long int u64;
u64 somasrec = 0;
u64 f1(int num){
    assert (num>=0);
    if(num == 0){
        return 0;
    }
    else if(num == 1){
        return 1;
    }
    else{
        somasrec++;
        return f1(num - 1) + f1(num - 2);
    }

}

u64 f2(int num){
    assert (num >= 0);
    u64 res;
    u64 bef2 = 0;
    u64 bef1 = 1;
    u64 somas = 0;
    for(int i = 2; i < num; i++){
        res = bef2 + bef1;
        if(i > 1){somas++;}
        bef2 = bef1;
        bef1 = res;
    }
    printf("Numero de adicoes = %llu\n ", somas);
    return res;
}

int main() {
    u64 resultrec,resultint;
    int num = 45;
    (void)elapsed_time();
    for (int i = 0;i != num+1; i++) {
        clock_t beginrec = clock();
        resultrec = f1(i);
        clock_t endrec = clock();
        double time_spentrec = (double) endrec - beginrec / CLOCKS_PER_SEC;
        printf("Recursivo - Indice: %d, F(i): %llu, Tempo: %lf, Numero de Somas: %llu\n ",i,resultrec,time_spentrec,somasrec);
        somasrec = 0;
    }
    double dtrec = elapsed_time();
    printf("tempo decorrido: %lf\n",dtrec);

    (void)elapsed_time();
    for (int i = 0;i != num+1; i++){
        clock_t beginit = clock();
        resultint = f2(i);
        clock_t endit = clock();
        double time_spentit = (double) endit - beginit / CLOCKS_PER_SEC;
        printf("Iterativo - Indice: %d, F(i): %llu, Tempo: %lf\n",i,resultint,time_spentit);
    }
    double dtit = elapsed_time();
    printf("tempo decorrido: %lf\n",dtit);

    return 0;
}

