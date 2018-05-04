#include <stdio.h>

float powerCalc (float value, int p);
float powerCalc2 (float value, int p);
int multCounter = 0;

int main() {
    float v = 0.5;
    int p;

//    for(p = 1; p <= 16; p++) {
//        printf("%f ^ %d = %f \n", v, p, res);
//        printf("Ao fim de %d multi\n",multCounter);
//        multCounter = 0;
//    }

    for(p = 1; p<=16;p++){
        float res = powerCalc2(v,p);
        printf("%f ^ %d = %f \n", v, p, res);
        printf("Ao fim de %d multi\n",multCounter);
        multCounter = 0;
    }
}


float powerCalc (float value, int p){
    if(p == 0) {
        return 1;
    }
    multCounter++;
    return value * powerCalc(value,p-1);
}

float powerCalc2 (float value, int p){
    if(p == 0){
        return 1;
    }
    else if(p % 2 == 0){
        float temp = powerCalc2(value, p/2);
        multCounter++;
        return temp * temp;
    }
    else{
        float temp = powerCalc2(value,p/2);
        multCounter += 2;
        return value * temp * temp;
    }

}