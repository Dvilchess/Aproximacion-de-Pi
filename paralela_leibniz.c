#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Estructura para pasar datos a los hilos
typedef struct {
    unsigned long long start;
    unsigned long long end;
    double result;
} ThreadData;

// Función que ejecutan los hilos
void *leibniz(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    unsigned long long i;
    double suma = 0.0;

    for (i = data->start; i < data->end; i++) {
        double term = (i % 2 == 0) ? 1.0 : -1.0;
        suma += term / (2 * i + 1);
    }

    data->result = suma;

    pthread_exit(NULL);
}

int main() {
    int num_hilos;
    unsigned long long iterations;

    printf("Ingrese el número de hilos: ");
    scanf("%d", &num_hilos);

    printf("Ingrese el número de iteraciones: ");
    scanf("%llu", &iterations);

    pthread_t threads[num_hilos];
    ThreadData thread_data[num_hilos];
    int i;

    double pi = 0.0;
    clock_t horainicio, horafin;
    double tiempototal;
    horainicio = clock();

    for (i = 0; i < num_hilos; i++) {
        unsigned long long start = i * (iterations / num_hilos);
        unsigned long long end = (i + 1) * (iterations / num_hilos);

        thread_data[i].start = start;
        thread_data[i].end = end;

        pthread_create(&threads[i], NULL, leibniz, (void *)&thread_data[i]);
    }

    for (i = 0; i < num_hilos; i++) {
        pthread_join(threads[i], NULL);
        pi += thread_data[i].result;
    }

    pi *= 4;

    // Calculo de tiempo
    horafin = clock();
    tiempototal = (double)(horafin - horainicio) / CLOCKS_PER_SEC;

    printf("Tiempo total: %f segundos\n", tiempototal);

    printf("El valor de PI calculado es: %.10f\n", pi);

    return 0;

}
