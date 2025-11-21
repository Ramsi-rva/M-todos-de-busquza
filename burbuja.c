#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *crearArreglo(int tamano) {
    srand(time(NULL));

    int *nuevoArreglo = (int *)malloc(tamano * sizeof(int));

    if (nuevoArreglo == NULL) {
        printf("Error: No se pudo asignar memoria para el arreglo\n");
        exit(1);
    }

    for (int i = 0; i < tamano; i++) {
        nuevoArreglo[i] = rand() % 100;  // Asignar valores aleatorios
    }
    return nuevoArreglo;
}

void burbuja(int num) {
    clock_t inicio, fin;
    int *numeros = crearArreglo(num);
    int aux;
    int todosmax;
    // //imprimir el arreglo sin ordenar
    // for(int i = 0; i < num; i++){
    //     printf("%d ", numeros[i]);
    // }
    //printf("\n");
    inicio = clock();
    printf("Ordenando numeros....");
    //Ordenar numeros
    for (int i = 0; i < num; i++){
        if (todosmax = 0){
            break;
        }
        todosmax = 0;
      
        for (int k = 0; k < num; k++) {
            if (k<num && numeros[k] > numeros[k+1]){
                aux = numeros[k];
                numeros[k] = numeros[k+1];
                numeros[k+1] = aux;
                todosmax++;
            } 
        }
        
    }
    // //imprimir ya ordenado
    // for(int i = 0; i < num; i++){
    //     printf("%d ", numeros[i]);
    // }
    fin = clock();
    printf("\n Ordenados \n");
    double tiempo_cpu = ((double)(fin-inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo %f ", tiempo_cpu);
}


int main(){
    burbuja(10);
    return 0;
}