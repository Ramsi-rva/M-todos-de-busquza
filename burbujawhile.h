#ifndef METODOSORDENAMIENTO_H
#define METODOSORDENAMIENTO_H

int *burbuja(int arr[]) {
    int aux;
    int flag = 1;  // Iniciar en 1 para entrar al while
    
    // Continuar mientras haya intercambios
    while(flag == 1) {
        flag = 0;  // Asumir que no habrá intercambios
        int k = 0;
        
        // Recorrer el arreglo hasta el centinela
        while(arr[k + 1] != -1) {  // Verificar k+1 para evitar salirse
            if(arr[k] > arr[k + 1]) {
                // Intercambiar
                aux = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = aux;
                flag = 1;  // Hubo intercambio, necesitamos otra pasada
            }
            k++;
        }
    }
    
    return arr;
}
#endif