#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    unsigned long long n; 
    int signo = 1;
    double pi = 0.0;

    printf("Ingrese el numero de términos para la aproximacion de Pi: ");
    scanf("%llu", &n);
    clock_t horainicio, horafin;
    double tiempototal;
horainicio= clock();

    for (unsigned long long i = 0; i < n; i++) {
        double termino = 1.0 / (2 * i + 1);
        pi += signo * termino;
        signo *= -1;
    }

    pi *= 4;
    horafin = clock();
    tiempototal= (double)(horafin - horainicio)/ CLOCKS_PER_SEC;

    printf("Tiempo total : %f segundos \n", tiempototal);
    printf("Aproximacion de Pi: %.10f\n", pi);


    return 0;
}
