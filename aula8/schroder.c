#include <stdio.h>
#include <math.h>
int multCounter = 0;

int schroder(int n);
double effSchroder(int n);
int dynSchroder(int n);
float schroder1 (unsigned n);
double effDynSchroder(int n);


int main() {
    for(int i = 0; i <=12; i++){
        printf("O numero de Schroder para %d: %d\n",i,schroder(i));
        printf("Nr de mults quando %d: %d\n",i,multCounter);
        multCounter = 0;
    }
}


// função não eficiente recursiva
int schroder (int n){
    int resCy = 0;
    if(n == 0)
        return 1;
    else{
        for(int i = 0; i <= n-1; i++){
            multCounter += 1;
            resCy += schroder(i) * schroder(n-i-1);
        }
        return schroder(n-1) + resCy;
    }
}

// minha função nao funcional recursiva
double effSchroder(int n){
    double resCy = 0;
    double temp = 0;

    if(n == 0)
        return 1;

        for(int i = 0; i < n/2; i++){
            multCounter++;
            resCy += effSchroder(i)*effSchroder(n-i-1);
        }
        if(n%2 == 0){
            return effSchroder(n-1) + (resCy + resCy);
        }
        else {
            temp = effSchroder((n - 1)/2);
            multCounter++;
            return effSchroder(n - 1) + (temp * temp) + (resCy + resCy);
        }
}

//função eficiente do oscar
float schroder1 (unsigned n){
    float result =0;
    float temp=0;

    if(n==0){
        return 1;
    }

    for (int i = 0; i < n/2; i++) {
        multCounter++;
        result += schroder1(i)*schroder1(n-i-1);
    }
    if(n%2==0){

        return schroder1(n-1)+result+result;

    }
    temp = schroder1(n/2);


    return schroder1(n-1)+result+result+temp*temp;


}

// dynamic programming
int dynSchroder(int n){
    int s[n];
    int i;
    int resCy = 0;
    s[0] = 1;

    for(i = 1;i<=n;i++){
        resCy = 0;
        for(int j = 0; j <= i-1; j++){
            multCounter += 1;
            resCy += s[j] * s[i-j-1];
        }
        s[i] = s[i-1] + resCy;
    }
    return s[n];

}

double effDynSchroder(int n){
    double s[n];
    int i;
    double resCy = 0;
    double temp = 0;
    s[0] = 1;

    for(i = 1;i<=n;i++){
        resCy = 0;
        for(int j = 0; j <= i/2; j++){
            multCounter += 1;
            resCy += s[j] * s[i-j-1];
        }
        if(n%2 == 0){
            s[n] = s[n-1] + (resCy + resCy);
        }
        else {
            temp = s[(n - 1)/2];
            multCounter++;
            s[n] = s[n - 1] + (temp * temp) + (resCy + resCy);
        }
    }
    return s[n];
}