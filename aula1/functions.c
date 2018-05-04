#include <stdio.h>

int counter1,counter2,counter3;

int f1 (int n){
    int i, j, r = 0;

    for(i = 1; i<=n; i++){
        for(j = 1; j<=n;j++){
            r += 1;
            counter1++;
        }
    }
    return r;
}

int f2 (int n){
    int i, j, r= 0;

    for(i = 1; i<=n; i++){
        for(j = 1; j<=i; j++){
            r += 1;
            counter2++;
        }
    }
    return r;
}

int f3 (int n){
    int i, j, r = 0;

    for(i = 1; i<=n; i++){
        for(j = i; j<=n; j++){
            r += j;
            counter3++;
        }
    }
    return r;
}

int main(){
    int i;
    printf("*******Function 1********\n");
    for(i = 1; i<=10;i++) {
        counter1 = 0;
        int result1 = f1(i);
        printf("%5d , N.Inst: %5d\n", result1,counter1);
    }
    printf("*******Function 2********\n");
    for(i = 1; i<=10; i++){
        counter2 = 0;
        int result2 = f2(i);
        printf("%5d , N.Inst: %5d\n", result2,counter2);
    }
    printf("*******Function 3********\n");
    for(i = 1; i<=10; i++){
        counter3 = 0;
        int result3 = f3(i);
        printf("%5d , N.Inst: %5d\n", result3,counter3);
    }
    return 0;
}


